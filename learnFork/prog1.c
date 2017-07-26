#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int funct1(int n);


int main(int argc, char*argv[])
{

    int x = funct1(4);


    return 0;
}



int funct1(int n)
{

    pid_t childPid;
    int i = 0;
    unsigned int sec = 10;
    char arg0[] = "ps";
    char *argV[] = {arg0, NULL};

    for(; i < n - 1;i++){
        if ( (childPid = fork()) == -1)
        {
            perror("fork fail\n");
            exit(-1);
        }
        else if (childPid == 0)
        {
            sleep(sec);
        }
        else
        {
            break;
        }
    }
    printf("index: %d   pid: %d\n", i, (int)getpid());
    if(execvp(argV[0], argV)){
        perror("exec error\n");
    }
    return 0;
}
