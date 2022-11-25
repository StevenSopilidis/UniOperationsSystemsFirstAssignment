#include "semaphore.h"
#include "stdio.h"
#include "pthread.h"

sem_t sem1;
sem_t sem2;
sem_t sem3;
sem_t sem4;

void* func1(void* args) {
    while(1) {
        sem_wait(&sem1);
        printf("Hallo ");
        sem_post(&sem2);
    }
}
void* func2(void* args) {
    while(1) {
        sem_wait(&sem2);
        printf("there ");
        sem_post(&sem3);
    }
}
void* func3(void* args) {
    while(1) {
        sem_wait(&sem3);
        printf("wonderful ");
        sem_post(&sem4);
    }
}
void* func4(void* args) {
    while(1) {
        sem_wait(&sem4);
        printf("world\n");
        sem_post(&sem1);
    }
}

int main() {
    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 0);
    sem_init(&sem3, 0, 0);
    sem_init(&sem4, 0, 0);

    pthread_t t1,t2,t3,t4;
    pthread_create(&t1, NULL, func1, NULL);
    pthread_create(&t2, NULL, func2, NULL);
    pthread_create(&t3, NULL, func3, NULL);
    pthread_create(&t4, NULL, func4, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    sem_destroy(&sem1);
    sem_destroy(&sem2);
    sem_destroy(&sem3);
    sem_destroy(&sem4);
}