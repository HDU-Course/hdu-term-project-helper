#ifndef   _COMMON_H_
#define   _COMMON_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>  
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

static const char * MUTEX_NAME = "mutex_shm";
static const char * FULL_NAME  = "full_shm";
//static const char * PATH_NAME = "tmp/shmtemp";

//constant define
#define SHM_SIZE 1024 //输入的最大长度

#define KEY_NUM 1000

//返回共享内存的标识符
int GetShmId(key_t key);
void SemInit();
void SemDestroy();
void  P(sem_t *sem);
void  V(sem_t *sem);
#endif
