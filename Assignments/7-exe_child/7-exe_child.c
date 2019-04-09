/* ------------------------------------------------------------------------------ 
 *   Author         : HARISH
 *   Date           : Mon Apr 8
 *   File           : 7-exec_child.c
 *   Title          : A child process which executes a command passed through 
 *                    command line.
 *   Description    : This program creates a child process using fork and executes 
 *                    a LS command which is passed through command line.
 * ---------------------------------------------------------------------------- */
#include "common.h"

int main(int argc, char **argv)
{
        if (argc < 2)
        {
                printf("Usage:    ./a.out    <command with/without path>    <options>\n");
                exit(EXIT_FAILURE);
        }

        int pid, exit_status = 0;
        /* create the child process */
        switch(pid = fork())
        {
                case -1:
                        /* if fork has failed */
                        perror("FORK()");
                        break;
                case 0:
                        /* if child process is successfully created */
                        printf("This is the CHILD process with ID %d\n", getpid());
                        if (execvp(argv[1], &argv[1]))
                                printf("Invalid command\n");
                        exit(0);
                        break;
                default:
                        /* parent process */
                        if (waitpid(pid, &exit_status, WCONTINUED))
                                printf("CHILD exited with status %d\n", exit_status);
        }
}
