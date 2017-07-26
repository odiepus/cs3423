#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(void){
    struct{
        int pid;
        int other;
    }my, theirs;

    int num = 5;
    int fd[num][2];
    int parent;
    int i = 0;
    for(; i < num; i++){
        pipe(fd[i]);
    }

    int k = 0;
    for(; k < num; k++){
        switch( (parent = fork()) ){
            case 0:
                break;

        }
        if(parent)break;
    }

    my.pid = getpid();

    int l = 0;
    for(; l < num; l++){
        if(k == l){
            close(fd[l][1]);
        }
        else
        {
            close(fd[l][0]);
        }
    }

    if(k == 0){
        int m = 1;
        for(; m < num; m++){
            write(fd[m][1], &my, sizeof(my));
            close(fd[m][1]);
        }

        int n = 0;
        while( (n = read(fd[0][0], &theirs, sizeof(theirs))) == sizeof(theirs) ){
            printf("%d:::%d\n", theirs.pid, theirs.other);
        }
        close(fd[0][0]);

    }
    else
    {
        int x = 0;
        while( (x = read(fd[k][0], &theirs, sizeof(theirs))) == sizeof(theirs) ){
            close(fd[k][0]);
            my.other = theirs.pid;
            write(fd[0][1], &my, sizeof(my));
            close(fd[0][1]);
        }
    }



}
