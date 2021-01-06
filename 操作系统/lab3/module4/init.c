#include "common.h"

int main(int argc, char const *argv[])
{
    key_t key;
    int semid;          //semaphore id
    int shmid;          //shared memory id


    /* Create key*/
    key = KEY_NUM;

    /* Initialize Semaphore*/
    SemInit();

    /* TODO Initialize Shared Memory*/ 
    GetShmId(key);

    printf("End of initialize\n");
    return 0;
}
