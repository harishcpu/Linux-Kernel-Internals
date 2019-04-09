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

int main(int argc, char **argv)
{

        /* if no arguments passed */
        if (argc == 1)
        {
                printf("Error: No arguments passed\n");
                printf("Usage: ./pipe  <command 1> | <command 2>\n");
                exit(EXIT_FAILURE);
        }
        else if(argc == 2)
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
                                printf("%s   ", argv[i]);
                                argv[i] = NULL;
                                break;
                        }
                }
                ++i;
        }

	//Declare an array
	int p[2];

	//Create the pipe
	pipe(p);

	switch (fork())
	{
		case -1:
			perror("fork()");
			exit(EXIT_FAILURE);
		case 0:
			//Close the write end from the child
			close(p[1]);
			dup2(p[0], 0);
			execvp(argv[i+1], &argv[i+1]);
			break;
		default:
			//Close the read end for the parent
			close(p[0]);
			dup2(p[1], 1);
			//execlp(argv[1], argv[1], (char *)0);
			execvp(argv[1], &argv[1]);
	}
}
