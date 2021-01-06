#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define TRUE 1

#define BUF_SIZE 255 //缓冲大小
//S_IRUSR|S_IWUSR：允许文件创建者读取|写入（感觉就是赋予权限）
#define PERM S_IRUSR|S_IWUSR
#define KEY_NUM 1000


typedef struct msgbuf msgbuf;

//消息缓冲区结构体
struct msgbuf
{
    long mtype; //消息类型
    char mtext[BUF_SIZE + 1]; //256，消息正文
};


//sem_t 信号量的数据类型，本质是个长整型的数
sem_t full;
sem_t empty;
sem_t mutex;

//pthread_t 声明线程，类似于pid_t
pthread_t write_pid; 
pthread_t read_pid;

/*
IPC对象键值，每个IPC对象都关联着一个唯一的长整型的键值，
不同进程通过相同相同的键值可访问到同一个IPC对象。
若为0，创建一个新的消息队列，若大于0（通常通过ftok()生成的）
*/
key_t key;

//messageid
int msgid;

struct msgbuf msg;

//初始化
void Init()
{
    /*
    函数：sem_init(sem_t *sem,int pshared,unsigned int value)
    参数：sem表示一个信号量，pashared（0-信号量被进程内的线程共享，非0-进程之间共享），value信号量初始值
    */
    sem_init(&full,0,0);
    sem_init(&empty,0,1);
    sem_init(&mutex,0,1);

    key = KEY_NUM;//给键值赋值

    //创建消息队列
    /*
    函数:msgget(key_t key,int smgflag)。新教材p107
    参数：key（消息队列键值，具体看上面）。msgflg（对消息队列的访问权限和控制命令的组合）
    功能：如果参数msgflag为IPC_CREATE，则semget()新创建一个消息队列并返回其标识符，
          或返回具有相同键值的已存在的消息队列的标识符
    返回值：成功返回消息队列的标识符，失败返回-1
    */
    if((msgid = msgget(key,PERM|IPC_CREAT)) == -1)
    {
        fprintf(stderr, "Create Message Queue Error %s\n",strerror(errno) );
        exit(EXIT_FAILURE);
    }   
}

//读取信息
void * ReadProcess(void *arg)
{
    msgbuf msg;
    //init msg
    msg.mtype = 1;
    while(TRUE)
    {
        //sem_wait阻塞进程，直到信号量>=0，解除阻塞后sem值-1，表示公共资源使用后减少
        sem_wait(&full);
        sem_wait(&mutex);

        //从消息队列获取内容
        /*
        函数：ssize_t msgrcv(int msqid,struct msgbuf *msgp,size_t msgsz,long msgtyp,int msgflg)
        参数：msqid（消息队列的标识符），
              msgp（用来存放接受到的消息内容的缓冲区指针）
              msgsz(消息正文的长度)，
              msgtyp(接收的消息类型，0-接受消息队列中第一个消息，>0接收第一个类型为msgtyp的消息，<0接收第一个类型小于等于msgtyp的绝对值的消息)
              msgflg（0-没有可接收的消息时，调用进程阻塞。其他略）
        返回值：接收成功，返回实际接收到的消息正文的字节数，否则返回-1
        */
        msgrcv(msgid,&msg,sizeof(msgbuf),1,0);//接收类型为1的消息（即mtype=1）

        //如果接受到"end"
        if(strcmp(msg.mtext,"end") == 0)
        {
            msg.mtype = 2;
            strncpy(msg.mtext,"over",BUF_SIZE);
            //msgsnd用于向标识符为msqid的消息队列发送一个消息（即发送over）
            msgsnd(msgid,&msg,sizeof(msgbuf),0);
            sem_post(&empty);
        sem_post(&mutex);
            break;
        }
        //print message
        printf("Receive:  %s\n\n",msg.mtext);

        //sem_post增加信号量的值，当有线程阻塞在这个信号量时，该函数会使其中一个线程不在阻塞
        sem_post(&empty);
        sem_post(&mutex);
    }
    exit(EXIT_SUCCESS);
}

void * WriteProcess(void *arg)
{   
    char input[50];
    msgbuf msg;
    msg.mtype = 1;
    while (TRUE)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        sleep(0.1);
        printf("Sent: Please Input the message you want to send.\n");
        scanf("%s",input);
        if(strcmp(input,"exit") == 0)
        {
            strncpy(msg.mtext,"end",BUF_SIZE);
            msgsnd(msgid,&msg,sizeof(msgbuf),0);
            sem_post(&full);
            sem_post(&mutex);
            break; //输出exit后，转化为end，然后跳出while循环
        }
        strncpy(msg.mtext,input,BUF_SIZE);
        msgsnd(msgid,&msg,sizeof(msgbuf),0);
        printf("Sent: %s\n",msg.mtext );
        //semaphore
        sem_post(&full);
        sem_post(&mutex);
    }



    // Clear Node
    memset(&msg,'\0',sizeof(msgbuf));
    // Block ,waiting for msg with type = 2
    msgrcv(msgid,&msg,sizeof(msgbuf),2,0);
    printf("Sent:%s\n",msg.mtext );

    //Remove Message Queue
    if( msgctl (msgid,IPC_RMID,0) == -1)
    {
        fprintf(stderr, "Remove Message Queue Error%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

int main()
{
    Init();
    pthread_create(&write_pid,NULL,WriteProcess,NULL);
    pthread_create(&read_pid,NULL,ReadProcess,NULL);
    //waiting for the thread end
    pthread_join(write_pid,NULL);
    pthread_join(read_pid,NULL);
    printf("Main Function End...\n");
    return 0;
}
