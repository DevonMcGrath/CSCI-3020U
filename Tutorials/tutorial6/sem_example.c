#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREADS 10

sem_t can_buy_milk;
int milk = 0;

void* buyer(void *arg)
{
    // P()
    sem_wait(&can_buy_milk);
    if(!milk)
    {
        // Buy some milk
        ++milk;
        sleep((rand() % 5) / 10.0);
    } else {
        --milk;
        sleep((rand() % 5) / 10.0);
    }
    // V()
    sem_post(&can_buy_milk);

    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t threads[THREADS];

    milk = 0;

    // Initialize the semaphore with a value of 1.
    // Note the second argument: passing zero denotes
    // that the semaphore is shared between threads (and
    // not processes).
    if(sem_init(&can_buy_milk, 0, 1))
    {
        printf("Could not initialize a semaphore\n");
        return -1;
    }

    for(int i = 0; i < THREADS; ++i)
    {
        if(pthread_create(&threads[i], NULL, &buyer, NULL))
        {
            printf("Could not create thread %d\n", i);
            return -1;
        }
    }

    for(int i = 0; i < THREADS; ++i)
    {
        if(pthread_join(threads[i], NULL))
        {
            printf("Could not join thread %d\n", i);
            return -1;
        }
    }

    sem_destroy(&can_buy_milk);

    // Make sure we don't have too much milk.
    printf("Total milk: %d\n", milk);

    return 0;
}