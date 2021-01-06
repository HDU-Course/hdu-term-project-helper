#include "common.h"


//key
key_t key;

//shared memory
int shmid;
char * shmptr;
char result[SHM_SIZE];

//semaphore 
sem_t * full;
sem_t * mutex;
                            //semaphore


void Init()
{
    key = KEY_NUM;                  //init key
    shmid  = GetShmId(key);         // init shared memory
    shmptr = shmat(shmid,NULL,0);       // attach segement to vitural ...?
    //semaphore init
    full = sem_open(FULL_NAME,O_CREAT);
    mutex = sem_open(MUTEX_NAME,O_CREAT);
}

void ReadMessage()
{
    P(full);
    P(mutex);                       
    strcpy(result,shmptr);
    V(mutex);
}

int main(int argc, char const *argv[])
{


    Init();

    /*waiting for user to input message*/
    ReadMessage();

    printf("Receiver : message is %s\n",result);
    SemDestroy();
    printf("Receiver :  Process End \n");
    return 0;
}
