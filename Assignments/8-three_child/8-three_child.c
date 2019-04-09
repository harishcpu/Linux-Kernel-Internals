/* ------------------------------------------------------------------------------ 
 *   Author         : HARISH
 *   Date           : Fri Apr 4
 *   File           : 8-three_child.c
 *   Title          : create three child process from same parent.
 *   Description    : This program will create three child processes form a same 
 *                    parent process. All the child processes will have the same 
 *                    ppid as that of the parent process.
 * ---------------------------------------------------------------------------- */
#include "common.h"

int main(void)
{
        pid_t pid, pid1, pid2;
        int exit_status = 0;

        /* create the first child */
        pid = fork();
        if (pid == -1)
        {
                printf("fork() failed\n");
                exit(0);
        }
        else if (pid == 0)
        {
                printf("A child1 is created with pid : %d, ppid : %d\n", getpid(), getppid());
                exit(1);
        }
        else
        {
                /* creaate the second child in the parent process */
                pid1 = fork();
                if (pid1 == 0)
                {
                        printf("A child2 is created with pid : %d, ppid : %d\n", getpid(), getppid());
                        sleep(3);
                        exit(2);
                }
                else
                {
                        /* create the third child in the parent process */
                        pid2 = fork();
                        if (pid2 == 0)
                        {
                                printf("A child3 is created with pid : %d, ppid : %d\n", getpid(), getppid());
                                sleep(5);
                                exit(3);
                        }
                        else
                        {
                                int wpid;
                                sleep(1);
                                printf("parent pid : %d\n", getpid());
                
                                for (int i = 0; i < 3; i++)
                                {
                                        /* print the exit status of child3 */
                                        wpid = wait(&exit_status);
                                        sleep(1);
                                        if (WIFEXITED(exit_status))
                                                printf("Child %d is exited normally with exit status %d\n", wpid, WEXITSTATUS(exit_status));
                                }
                        }
                }
                printf("Parent is exiting...\n");
        }
}
