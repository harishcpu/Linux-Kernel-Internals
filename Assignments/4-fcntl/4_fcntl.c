/* ------------------------------------------------------------------------------
 *   Author         : HARISH
 *   Date           : Thu Mar 28
 *   File           : fork, fcntl system calls
 *   Title          : fcntl operations
 *   Description    : This program helps to understand about fork and fcntl system calls.
 * ---------------------------------------------------------------------------- */
#include "common.h"

int main(int argc, char **argv)
{
        int fd;
        struct flock lock;
        pid_t pid;
        int status;

        if (argc < 2)
        {
                printf("Insufficient arguments\n");
                printf("Usage: ./a.out <file name> \n");
                return 0;
        }

        fd = open(argv[1], O_WRONLY | O_TRUNC);
        if (fd == -1)
        {
                perror(argv[1]);
                return 0;
        }
        else
                printf("opening...\n\n");

        
        pid = fork();
        if (pid == -1) {
                perror("Error");
                return 0;
        }

        if (pid == 0)
        {
#if 1
                lock.l_type = F_WRLCK;
                fcntl(fd, F_SETLKW, &lock);
                
                if ((status = fcntl(fd, F_SETLK, &lock)) != -1)
                        printf("child: locked.\n");
                
                write(fd, "hello, ", 7);
                printf("child: writing... hello,\n");
                
                lock.l_type = F_UNLCK;
                fcntl(fd, F_SETLKW, &lock);
                printf("child: unlocking...\n\n");

#endif
        }
        else
        {
                usleep(10000);
                lock.l_type = F_WRLCK;
                fcntl(fd, F_SETLKW, &lock);
#if 1
                if ((status = fcntl(fd, F_SETLK, &lock)) == 0)
                        printf("parent: locked.\n");

                write(fd, "world!\n", 7);
                printf("parent: writing... world!\n");
                
                lock.l_type = F_UNLCK;
                fcntl(fd, F_SETLKW, &lock);
                printf("parent: unlocking...\n\n");
#endif
                close(fd);
                printf("closing...\n");
        }
}
