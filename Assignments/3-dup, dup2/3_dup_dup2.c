/* ------------------------------------------------------------------------------
 *   Author         : HARISH KUMAR
 *   Date           : Thu Mar 27
 *   File           : dup, dup2 system calls
 *   Title          : print contents in a file using dup, dup2 SystemCalls
 *   Description    : This program redirects the contents from stdout into a 
 *                    file.
 * ---------------------------------------------------------------------------- */
#include "common.h"

int main(int argc, char **argv)
{
        if (argc == 1)
        {
                printf("Insufficient arguments\n");
                printf("Usage: ./a.out <file name>\n");
                return 0;
        }

       int fd1;

       /* open the file in write only mode */
       fd1 = open(argv[1], O_WRONLY | O_CREAT, 0666);
       if (fd1 == -1)
       {
               /* do the error checking */
               perror(argv[1]);
               exit(2);
       }

       /* close the stdout file descriptor */
       close(1);
       /* duplicates fd1 in lowest possible ___ file descriptor */
       int n_fd = dup(fd1);

       /* print the contents */
       write(n_fd, "Hello, ", 7);
       write(fd1, "World!\n", 7);
       printf("Bye.\n");

       return 0;
}
