#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CMD_COLLECTION_LEN 4 //命令数组的长度（有哪几个命令）

//command index
#define INVALID_COMMAND -1 //无效命令返回-1
#define EXIT    0
#define CMD_1 1
#define CMD_2 2
#define CMD_3 3

//bool
#define TRUE 1

char *cmdStr [CMD_COLLECTION_LEN ]= {"exit","cmd1","cmd2","cmd3"};


//对比所有命令参数，如果有一样的，就返回对应数字，用于后面执行
int getCmdIndex(char *cmd)
{
    int i;

    for(i=0;i<CMD_COLLECTION_LEN;i++)
    {
        if (strcmp(cmd,cmdStr[i])==0)
        {
            return i;
        }
    }

    return -1;
}


/*
创建子进程，这里使用了execl，后面的l表示list，即参数列表。
第一参数为path（要执行的文件路径），最后一个参数必须是NULL，
中间的为要传送的参数
*/
void myFork(int cmdIndex)
{
    pid_t pid;

    if((pid = fork())<0)
    {
        printf("创建子进程错误\n");
        exit(0);
    }
    else if (pid == 0)
    {
        int execl_status = -1;

        printf("子进程正在运行\n");

        switch(cmdIndex)
        {
            case CMD_1:
                execl_status = execl("./cmd1","cmd1",NULL);
                break;
            case CMD_2:
                execl_status = execl("./cmd2","cmd2",NULL);
                break;
            case CMD_3:
                execl_status = execl("./cmd3","cmd3",NULL);
                break;
            default:
                printf("无此命令！！！\n");
                break;
        }

        if(execl_status<0)
        {
            printf("创建错误\n");
            exit(0);
        }

        printf("运行完毕！\n");
        exit(0);
    }
    else{
        return;
    }

}

//运行cmd
void runCMD(int cmdIndex)
{
    switch(cmdIndex)
    {
        case INVALID_COMMAND:
            printf("Command Not Found \n"); //没有找到该命令
            break;
        case EXIT: //exit命令返回0
            exit(0);
            break;
        default:
            myFork(cmdIndex); //创建子进程运行
            break;
    }
}

int main()
{
    pid_t pid;

    char cmdStr[30]; //命令数组（最长30）

    int cmdIndex; //用于显示运行哪个数据
    while(TRUE)
    {
        printf("\n输入命令\n>>:");
        scanf("%s",cmdStr);
        cmdIndex = getCmdIndex(cmdStr);
        runCMD(cmdIndex); //根据数字运行不同的cmd
        wait(0);
    }
}
