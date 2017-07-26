#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t child_pid;

    printf("this process id is %d\n", (int)getpid());

    child_pid = fork();

    if (child_pid != 0)
    {
        printf("this is parent ID %d\n", (int) getpid());
        printf("child pid is %d\n", (int)child_pid);
    }else
    {
        printf("this is child ID %d\n", (int) getppid());
    }

    return 0;
}
