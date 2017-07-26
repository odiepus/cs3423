#include "apue.h"

int globVar = 6;
char buf[] = "a write to stdout\n";

int main ()
{
    int var;

    pid_t pid;

    var = 88;

    if(write(STDOUT_FILENO, buf, sizeof(buf - 1)) != sizeof(buf -1))
    {
        printf("write error1\n");
        exit(-1);
    }

    printf("Before Fork\n\n");

    if( (pid = fork()) < 0)
    {
        printf("Fork error\n");
        exit(-1);
    }
    else if (pid == 0)
    {
        printf("hello from child %d\n", (int) getpid());
        globVar++;
        var++;
    }
    else
    {
        sleep(2);
    }

    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globVar, var);
    exit(0);
}
