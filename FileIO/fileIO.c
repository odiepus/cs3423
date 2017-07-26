#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char*argv[]){



    unsigned char buffer[1024];
    int bytesRead = 1;

    int fd1 = open(path, O_RDONLY );
    if (fd1 == -1)
    {
        perror("could not open file");
    }

    for(int i = 0; i < sizeof(argv - 1); i++)
    {
        char* path = argv[i+1];
        while (bytesRead > 0){
            bytesRead = read (fd1, buffer, sizeof(buffer));
            if (bytesRead < 1024)
            {
               if (bytesRead > 0){
                   int diff = buffer - (buffer - bytesRead);
                   write(STDOUT_FILENO, buffer, diff);
                }
            }
            else
            {
                write(STDOUT_FILENO, buffer, sizeof(buffer));
            }
        }
    }


    close(fd1);

    return 0;
}
