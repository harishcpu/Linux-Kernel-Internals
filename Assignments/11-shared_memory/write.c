#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>

#define SHM_SIZE 1024

int main(void)
{
        key_t key = 'A';
        int shmid;
        char *ptr;

        if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1)
        {
                perror("shmget()");
                exit(1);
        }

        if ((ptr = shmat(shmid, 0, 0)) == (void *)(-1))
        {
                perror("shmat()");
                exit(2);
        }

        printf("Enter data: ");
        scanf("%[^\n]s", ptr);

        int i = 0;
        while (ptr[i] != '\0')
        {
                ptr[i] = toupper(ptr[i]);
                ++i;
        }

        if (shmdt(ptr) == -1)
        {
                perror("shmdt()");
                exit(3);
        }
}
