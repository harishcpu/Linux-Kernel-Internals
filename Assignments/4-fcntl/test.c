#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv)
{
	int fd; 
	struct flock lock;
	pid_t pid;
	int status;

	/* Do arg count check */
    	if (argc < 2)
    	{
        	printf("Insufficient arguments\n");
		printf("Usage:- ./my_fcntl_lock <file> \n");
        	return 1;
    	}	

	printf ("opening.....\n");
	/* open the file on which synchronization is performed */
	if ( (fd = open(argv[1], O_APPEND|O_WRONLY)) == -1 )
	{
		perror("open");
		return -1;	
	}

	/* Initialize the flock structure. */
	memset (&lock, 0, sizeof(lock));

	/* to set write lock */
	lock.l_type = F_WRLCK;
	/* Place a write lock on the file. */
	fcntl (fd, F_SETLKW, &lock);

	/* Create a new process */
	pid = fork();
    	if(pid < 0)
	{
	        perror("fork");
	        return 1;
	}

	if(pid == 0)
	{
           	//pause();
           	/* I'm the child */
           	printf("Child's turn!\n");
		sleep(2);
		//if lock is present wait for release
		 if ( 0 == fcntl(fd, F_SETLK, &lock) )
		 {
			printf ("in child locked; hit Enter to unlock... ");
 			/* Wait for the user to hit Enter. */
 			getchar ();

			printf ("child unlocking\n");
			/* Release the lock. */
 			lock.l_type = F_UNLCK;
			fcntl (fd, F_SETLKW, &lock);
			
		 }	
		 else
		{
			printf ("child locking.....\n");
			/* Initialize the flock structure. */
 			memset (&lock, 0, sizeof(lock));
 			/* to set write lock */
			lock.l_type = F_WRLCK;
			/* Place a write lock on the file. */
 			fcntl (fd, F_SETLKW, &lock);
			
		}
         	exit(1);
		//close (fd);	

	}
	else
	{
		sleep(5);
		/* I'm the parent */
	        printf("Parent's turn!\n");
		int wpid = waitpid(&status);
			
		//if lock is present wait for release
		 if ( 0 == fcntl(fd, F_SETLK, &lock) )
		 {
			printf ("parent locked; hit Enter to unlock... ");
 			/* Wait for the user to hit Enter. */
 			getchar ();

			printf ("parent unlocking\n");
			/* Release the lock. */
 			lock.l_type = F_UNLCK;
			fcntl (fd, F_SETLKW, &lock);
		 }	
		 else
		{
			printf ("parent locking.....\n");
			/* Initialize the flock structure. */
 			memset (&lock, 0, sizeof(lock));
 			/* to set write lock */
			lock.l_type = F_WRLCK;
			/* Place a write lock on the file. */
 			fcntl (fd, F_SETLKW, &lock);
		
		}
          
		close (fd);

	}		

	
	
 	return 0;
}
