#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define SHM_SIZE 1024

int main(void)
{
        key_t key = 'A';
        int shmid;
        char *ptr;

        if ((shmid = shmget(key, SHM_SIZE, 0644)) == -1)
        {
                perror("shmget()");
                exit(1);
        }

        if ((ptr = shmat(shmid, 0, 0)) == (void *)(-1))
        {
                perror("shmat()");
                exit(2);
        }

        char temp;
        for (int i = 0, j = strlen(ptr)-1; i < j; ++i, --j)
        {
                temp = ptr[i];
                ptr[i] = ptr[j];
                ptr[j] = temp;
        }
        printf("Data: %s\n", ptr);

        if (shmdt(ptr) == -1)
        {
                perror("shmdt()");
                exit(3);
        }

        if ((shmctl(shmid, IPC_RMID, NULL)) == -1)
        {
                perror("shmctl()");
                exit(4);
        }
}
