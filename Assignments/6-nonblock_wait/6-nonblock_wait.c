/* ------------------------------------------------------------------------------ 
 *   Author         : HARISH
 *   Date           : Fri Apr 4
 *   File           : 6-nonblock_wait.c
 *   Title          : avoid child becoming zombie without blocking the parent.
 *   Description    : This program will create three child processes form a same 
 *                    parent process. All the child processes will have the same 
 *                    ppid as that of the parent process.
 * --------------------------------------------------------------------------------
 */
#include "common.h"

int main(void)
{
        pid_t pid1, pid2;
        int exit_status = 0;

        pid1 = fork();
        if (pid1 == -1)
        {
                printf("fork() failed\n");
                exit(1);
        }

        if (pid1 == 0)
        {
                printf("A child is created with pid : %d\n", pid2 = getpid());
                sleep(5);
        }
        else
        {
                sleep(1);
                while (waitpid(pid1, &exit_status, WNOHANG) == 0)
                {
                        printf("Parent is running...\n");
                        sleep(1);
                }

                if (WIFEXITED(exit_status))
                        printf("Child is exited normally with exit status %d\n", exit_status);
                printf("Parent is exiting...\n");
        }
}

