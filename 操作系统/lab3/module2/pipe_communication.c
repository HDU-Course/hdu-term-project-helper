#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define READ 0 //filedes[0]用于读

#define WRITE 1 //filedes[1]用于写

int main() {

    /*
    函数原型：pipe(int filedes[2])
    参数含义:filedes[0]对应管道读端，filedes[1]对应管道写端
    功能：pipe在内存缓冲区中创建一个管道，并将读写该管道的一对文件描述符保存在filedes所指数组中
    返回值:成功返回0，失败返回-1
    */
    int filedes[2];

    pid_t pid1,pid2,pid3;//pid_t本质就是int

    char buf[256]; //用作read的缓冲区，保存读取的字符

    pipe(filedes);  //创建无名管道

    if((pid1 = fork()) == -1) { //创建子进程
        printf("fork error(pid1)!\n");
        exit(1);
    }
    if(pid1 == 0) {
        sleep(1); //挂起一秒
        printf("正在产生子进程pid1:%d\n",getpid());
        //子进程向父进程写数据，关闭管道的读端
        close(filedes[READ]);
        write(filedes[WRITE], "pid111111\n", strlen("pid111111\n"));
        exit(0);
    }



    if ((pid2 = fork()) == -1) {
        printf("fork error(pid2)\n");
        exit(1);
    }
    if (pid2 == 0) {
        sleep(1);
        printf("正在产生子进程pid2:%d\n",getpid());
        close(filedes[READ]);
        write(filedes[WRITE], "pid222222\n", strlen("pid222222\n"));
        exit(0);
    }


    if ((pid3 = fork()) == -1) {
        printf("fork error(pid3)\n");
        exit(1);
    }
    if (pid3 == 0) {
        sleep(1);
        printf("正在产生子进程pid3:%d\n",getpid());

        close(filedes[READ]);
        write(filedes[WRITE], "pid333333\n", strlen("pid333333\n"));

        exit(0);
    }
    else {
        //waitpid()会暂时停止目前进程的执行，直到有信号来或者子进程结束
        pid1 = waitpid(pid1, NULL, WUNTRACED);
        pid2 = waitpid(pid2, NULL, WUNTRACED);
        pid3 = waitpid(pid3, NULL, WUNTRACED);
        printf("main pid: %d\n",getpid());
        printf("wait pid: %d %d %d 返回信息\n",pid1,pid2,pid3);
        /*父进程从管道读取子进程写的数据，关闭管道的写端*/
        close(filedes[WRITE]);
        //read()：读取的数据保存在缓冲区buf
        read(filedes[READ], buf, sizeof(buf));
        printf("3个子进程传输的数据为：\n%s\n", buf);
    }
    return 0;
}
