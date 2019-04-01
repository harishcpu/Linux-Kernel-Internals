/* ------------------------------------------------------------------------------ 
 *   Author         : HARISH
 *   Date           : Mon Mar 26
 *   File           : my_copy.c
 *   Title          : my_copy functon using SystemCalls
 *   Description    : This program copies the contents of one file 
 *                    into another using SystemCall libraries and functions.
 * ---------------------------------------------------------------------------- */
#include "common.h"

int my_copy(int fs, int fd);

int main(int argc, char **argv)
{
        if (argc == 1)
        {
                printf("Insufficient arguments\n");
                printf("Usage: ./my_copy [option] <source file> <destination file>\n");
                exit(0);
        }

        /* Declare all the variables */
        struct stat permissions;
        int fs, fd;

        /* check if option -p is mentioned a command line argument */
        if (strcmp(argv[1], "-p") == 0)
        {
                /* open src file in read only mode */
                fs = open(argv[2], O_RDONLY);
                /* do te error check */
                if (fd == -1)
                { 
                        perror(argv[2]);
                        printf("errno: %d\n", errno);
                        exit(2);
                }

                /* store the file status */
                fstat(fs, &permissions);

                fd = open(argv[3], O_WRONLY | O_CREAT | O_EXCL, permissions.st_mode);
                
//                printf("\t\t%o\n", permissions.st_mode);
                
                //Handle the error
                if (fd == -1)
                {
                        /* if file already exists */
                        printf("File already exists. Do you want to overwrite: ");
                        char c = getchar();
                        if (c == 'y')
                        {
                                /* if user agreed to overwrite */
                                close(fd);
                                /* open again in write only mode */
                                fd = open(argv[3], O_WRONLY | O_TRUNC, permissions.st_mode);
                                /* do the error check */
                                if (fd == -1)
                                {
                                        perror(argv[3]);
                                        printf("errno: %d\n", errno);
                                        exit(2);
                                }
                        }
                        /* copy the contents of src to dest */
                        my_copy(fs, fd);
                        //fchmod(fd, permissions.st_mode);

                        //5. close the files
                        close(fs);
                        close(fd);
                        return 0;
                }
               
        /*
                //fs = open(argv[2], O_RDWR);
                //Handle the error
                //if (fs == -1)
                //{
                //        perror(argv[1]);
                //        printf("errno: %d\n", errno);
                //        exit(2);
                //}   
        */
                
                /* copy the src file contents to dest file */
                my_copy(fs, fd);

                /* close the files */
                close(fs);
                close(fd);
                return 0;
        }

        /* if the option -p is not mentioned */
        /* Open the src.txt file in read mode */
        fs = open(argv[1], O_RDONLY);

        /* Handle the error */
        if (fs == -1)
        {
                perror(argv[1]);
                printf("errno: %d\n", errno);
                exit(1);
        }

        /* set the umask to zero */
        umask(0);

        /* open dest.txt file in write mode */
        fd = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, 0666);

        /* Handle the error */
        if (fd == -1)
        {
                        /* if the file is already present */
                printf("File already exists. Do you want to overwrite: ");
                char c = getchar();
                if (c == 'y')
                {
                        /* if the user agreed to overwrite */
                        close(fd);
                        fd = open(argv[2], O_WRONLY);
                        if (fd == -1)
                        {               
                                perror(argv[2]);
                                printf("errno: %d\n", errno);
                                exit(2);
                        }
                }
        }

        /* copy the src file contents into dest file */
        my_copy(fs, fd);

        /* close the files */
        close(fs);
        close(fd);
        return 0;
}

/* copy the contents of file descriptor fs to fd */
int my_copy(int fs, int fd)
{
        char buf[8] = {'\0'};
        ssize_t count;

        /* Read the info and write */
        while ((count = read(fs, buf, 8)) > 0)
        {
                write(fd, buf, count);
                memset(buf, 0, 8);
        }

        return 0;
}
