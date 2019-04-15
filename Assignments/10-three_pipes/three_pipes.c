/* ------------------------------------------------------------------------------ 
 *   Author         : HARISH
 *   Date           : Mon Apr 8
 *   File           : pipe.c
 *   Title          : pipe system call
 *   Description    : This program executes a command in one process and pipes 
 *                    it to another process and prints the output.
 * ---------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{

        /* if no arguments passed */
        if (argc == 1)
        {
                printf("Error: No arguments passed\n");
                printf("Usage: ./pipe  <command 1> | <command 2>\n");
                exit(EXIT_FAILURE);
        }
        else if (argc == 2)
        {
                printf("Error: Insufficient arguments passed\n");
                printf("Usage: ./pipe  <command 1> | <command 2>\n");
                exit(EXIT_FAILURE);
        }


        int i = 0;
        while (1)
        {
                if (argv[i] != NULL)
                {
                        if (!strcmp(argv[i], "|"))
                        {
                                //printf("%s   ", argv[i]);
                                argv[i] = NULL;
                                break;
                        }
                }
                ++i;
        }
        
        int j = i + 1;
        while (1) {
                if (argv[j] != NULL) {
                        if (!strcmp(argv[j], "|")) {
                                //printf("%s   ", argv[i]);
                                argv[j] = NULL;
                                break;
                        }
                }
                ++j;
        }

	//Declare an array
	int p1[2], p2[2];

	//Create the pipe
	pipe(p1);

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
			//Close the read end for the parent
			close(p1[0]);
			dup2(p1[1], 1);
			//execlp(argv[1], argv[1], (char *)0);
			execvp(argv[1], &argv[1]);
                        exit(1);
                }
                else
                {
                        sleep(1);
                        /* create the second child in the parent process */
	                pipe(p2);
			close(p1[1]);
			dup2(p1[0], 0);
                        
                        pid1 = fork();
                        if (pid1 == 0)
                        {
			        //Close the write end from the child
                                close(p2[0]);
			        dup2(p2[1], 1);
			        execvp(argv[i+1], &argv[i+1]);
                                exit(2);
                        }
                        else
                        {
                                /* create the third child in the parent process */
                                sleep(2);
                                pid2 = fork();
                                if (pid2 == 0)
                                {
                                        sleep(5);
			                close(p2[1]);
			                dup2(p2[0], 0);
			                execvp(argv[j+1], &argv[j+1]);
                                        exit(3);
                                }
                        }
                }
}
