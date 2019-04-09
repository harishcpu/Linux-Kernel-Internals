/* ------------------------------------------------------------------------------ 
 *   Author         : HARISH
 *   Date           : Tue Apr 2
 *   File           : 5-zomb_orph.c
 *   Title          : Print the status of a process (zombie, sleeping)
 *   Description    : This program creates a child process and prints the status
                      of that process using /proc/_pid_/status file.
 * ---------------------------------------------------------------------------- */
#include "common.h"
#include <stdlib.h>

#define MAX 21

void print_info(pid_t pid2);

int main(void)
{
        pid_t pid1, pid2;
        int exit_status;

        /* create a child process */
        pid1 = fork();
        /* do the error checking */
        if (pid1 == -1)
        {
                printf("fork() failed\n");
                exit(1);
        }

        /* child process */
        if (pid1 == 0)
        {
                printf("A child is created with pid : %d\n", pid2 = getpid());
                sleep(5);
        }
        else
        {
                /* parent process */
                sleep(1);
                print_info(pid1);
                sleep(5);
                putchar('\n');
                print_info(pid1);
                putchar('\n');
        }
}

void print_info(pid_t pid2)
{
                char buf[MAX];
                
                memset(buf, 0, sizeof(buf));
                sprintf(buf, "/proc/%d/status", pid2);

                /* open the status file of the child process */
                int fs = open(buf, O_RDONLY);

                if (fs == -1)
                        printf("Error opening file\n");
                else
                        printf("The file %s is opened\n", buf);

                int bytes, nl, i;
                nl = i = 0;

                /* print the status of the process */
                while ((bytes = read(fs, buf, MAX - 1)) != -1 && nl < 3)
                {
#if 1
                        buf[MAX] = '\0';
                        printf("%s", buf);
                                ++nl;
                }
}














#else
                        while (i < MAX && i < bytes)
                        {
                                if (buf[i] == '\n' || buf[i] == ':')
                                        ++nl;

                                putchar(buf[i]);
                                ++i;
                        }
                        i = 0;
                        //write(1, buf, bytes);
#endif
