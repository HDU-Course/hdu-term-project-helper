#include "common.h"


//key
key_t key;

//shared memory
int shmid;
char * shmptr;
char input[SHM_SIZE];

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

void SaveMessage()
{

    P(mutex);                       
    strcpy(shmptr,input);
    V(mutex);

    V(full);
}

int main(int argc, char const *argv[])
{


    Init();

    /*waiting for user to input message*/
    scanf("%s",input);                  //input message from shell 
                                        // TODO input a whole line
    SaveMessage();

    printf("Sender:  Process End\n");
    return 0;
}
