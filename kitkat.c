#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024

void writeFromSTDIN();
void writeFromARGV(char* argV);
void writeFromSTDINToF3(int fdOut);
void writeFromFileToF3(char* f1, int fdOut);

int main(int argc, char* argv[])
{   //check if we have minimum arguments of 3 or more else show user correct syntax
    if(argc < 3)
    {
        char x[] = "Incorrect syntax; Correct syntax follows: kitcat <fileIn1> <fileIn2> [<fileOut>]\nIf input from STDIN use '-' and only in first argument\n";
        write(STDERR_FILENO, x, strlen(x));
        exit(-1);
    }

    //if we have exactly 3 arguments then check if we have dashes '-'. then check if we have more than one dash
    //if more than one dash then state error and exit
    if (argc == 3)
    {
        if (argv[1][0] == '-' || argv[2][0] == '-')
        {
            if (argv[1][0] == '-' && argv[2][0] == '-')
            {
                write(STDERR_FILENO, "Input Error: Only one argument can be redirected in.\n", strlen("Input Error: Only one argument can be redirected in.\n"));
                exit(-1);
            }

            //if first argument is not a dash grab from argument and print out to stdout
            //then grab from redirect stdin and print to stdout
            if(argv[1][0] != '-') {
                writeFromARGV(argv[1]);
                writeFromSTDIN();
            }
            else
            {
                writeFromSTDIN();
                writeFromARGV(argv[2]);
            }
        }
        //no dashses mean our arguments are files we can open and read from to print to stdout
        else
        {
            writeFromARGV(argv[1]);
            writeFromARGV(argv[2]);
        }
    }
    //if argv has 4 arguments
    else if(argc == 4)
    {
        //open the 3rd argument for writing to
        mode_t mode = S_IROTH | S_IRUSR | S_IWGRP | S_IWUSR | S_IRGRP;
        int fdOut = open(argv[3], O_CREAT | O_WRONLY | O_APPEND | mode);
        if (fdOut < 0)
        {
            perror(argv[3]);
            close(fdOut);
            exit (-1);
        }

        //check if at least one of the first 2 arguments has a dash
        if (argv[1][0] == '-' || argv[2][0] == '-')
        {

            //if more than one dash then state error and exit
            if (argv[1][0] == '-' && argv[2][0] == '-')
            {
                write(STDERR_FILENO, "Input Error: Only one argument can be redirected in.\n", strlen("Input Error: Only one argument can be redirected in.\n"));
                close(fdOut);
                exit(-1);
            }

            //if first argument is not a dash grab from argument and print out to stdout
            //then grab from redirect stdin and print to stdout
            if(argv[1][0] != '-')
            {
                writeFromFileToF3(argv[1], fdOut);
                writeFromSTDINToF3(fdOut);
                close(fdOut);
            }
            else
            {
                writeFromSTDINToF3(fdOut);
                writeFromFileToF3(argv[2], fdOut);
                close(fdOut);
            }
        }
            //no dashses mean our arguments are files we can open and read from to print to stdout
        else
        {
            writeFromFileToF3(argv[1], fdOut);
            writeFromFileToF3(argv[2], fdOut);
            close(fdOut);
        }
    }
    return 0;
}

//this function creates file descriptor and writes to 3rd argument
void writeFromFileToF3(char* f1, int fdOut)
{
    int bufRead = 1;
    char buf[BUFSIZE];

    int fd = open(f1, O_RDONLY);
    if (fd < 0)
    {
        perror(f1);
        close(fd);
        close(fdOut);
        exit (-1);
    }
    while(bufRead)
    {
        bufRead = read(fd, buf, BUFSIZE);

        if(bufRead < BUFSIZE && bufRead > 0)
        {
            if(write(fdOut, buf, bufRead) < 0)
            {
                perror(f1);
            }
        }
        else if(bufRead == BUFSIZE)
        {
            if(write(fdOut, buf, BUFSIZE) < 0)
            {
                perror(f1);
            }
        }
        else if(bufRead < 0)
        {
            perror(f1);
            close(fd);
            close(fdOut);
            exit (-1);
        }
    }
    close(fd);
}

//read from STDIN_LINENO and print to 3rd argument from cli
void writeFromSTDINToF3(int fdOut)
{
    char buf[BUFSIZE];
    ssize_t written = 0;
    ssize_t bufRead = 1;


    while(bufRead > 0)
    {
        bufRead = read(STDIN_FILENO, buf, BUFSIZE);
        if(bufRead < 1024 && bufRead > 0)
        {
            written = write(fdOut, buf, bufRead);
            if (written < 0)
            {
                perror("Failed to write");
            }
        }
        else if(bufRead == BUFSIZE)
        {
            written = write(fdOut, buf, BUFSIZE);
            if (written < 0)
            {
                perror("Failed to write");
            }
        }
        else if(bufRead < 0)
        {
            perror("Failed to read from redirected file");
            exit (-1);
        }
    }
}

//create file descriptor from passed in argument and print to STDOUT_FILENO
void writeFromARGV(char* argV)
{
    char buf[BUFSIZE];
    int written;
    ssize_t bufRead1 = 1;
    int fdOpen = open(argV, O_RDONLY);
    if(fdOpen < 0)
    {
        perror(argV);
        close(fdOpen);
        exit(-1);
    }
    while (bufRead1 > 0) {
        bufRead1 = read(fdOpen, buf, BUFSIZE);
        if (bufRead1 < 1024 && bufRead1 > 0) {
            written = write(STDOUT_FILENO, buf, bufRead1);
            if (written < 0) {
                perror(argV);
            }
        } else if (bufRead1 == BUFSIZE) {
            written = write(STDOUT_FILENO, buf, BUFSIZE);
            if (written < 0) {
                perror(argV);
            }
        } else if (bufRead1 < 0) {
            perror(argV);
            close(fdOpen);
            exit(-1);
        }
    }
    close(fdOpen);
}

//read from STDIN_FILENO to STDOUT_FILENO
void writeFromSTDIN()
{
    char buf[BUFSIZE];
    ssize_t written;
    ssize_t bufRead = 1;

    while(bufRead > 0)
    {
        bufRead = read(STDIN_FILENO, buf, BUFSIZE);
        if(bufRead < 1024 && bufRead > 0)
        {
            written = write(STDOUT_FILENO, buf, bufRead);
            if (written < 0)
            {
                perror("Failed to write3");
            }
        }
        else if(bufRead == BUFSIZE)
        {
            written = write(STDOUT_FILENO, buf, BUFSIZE);
            if (written < 0)
            {
                perror("Failed to write4");
            }
        }
        else if(bufRead < 0)
        {
            perror("Failed to read from file");
            exit (-1);
        }
    }
}
