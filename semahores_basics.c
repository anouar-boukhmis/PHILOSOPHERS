#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdatomic.h>

void labor(sem_t *write, int id, atomic_int *add)
{
    while(1)
    {
        sem_wait(write);
        printf("hello this is me process %d talking !\n", id);
        atomic_fetch_add(add, 1);
        sem_post(write);
        sleep(5);
        if (*add == 10)
            exit(0);
    }
}

int main()
{
    int i;
    atomic_int limit;
    pid_t process[2];
    sem_t *write;

    i = 0;
    limit = 0;
    sem_unlink("/write");
    write = sem_open("/write", O_CREAT, 0644, 1);
    while(i < 2)
    {
        process[i] = fork();
        if (!process[i])
            labor(write, i + 1, &limit);
        i++;
    }
    i = -1;
    while(i++ < 2)
        waitpid(process[i], 0, 0);
}