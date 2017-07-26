#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>



int main(int argc, char* argv[])
{
    int fd[2];
    pid_t childPid;
    pipe(fd);
    char msg []= "Hello World\n";
    char input[256];
    char arg0[] = "ls";
    char *argV[] = {arg0, NULL};

    if ( (childPid = fork()) == -1 )    //create child, if it fails tell the user
    {
        perror("Failed to fork\n");
        exit(-1);
    }
    else if (childPid == 0)         //check if process is in the child
    {
        if(execvp(argV[0], argV))
        {
            perror("exec");
            exit(-1);
        }
    }
    else        //if parent close the read fd
    {

    }


    return 0;
}
