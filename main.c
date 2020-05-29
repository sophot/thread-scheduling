#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include "Queue.c"

#define MAX_THREAD 4

Queue *firstQueue;
Queue *secondQueue;
Queue *thirdQueue;

int balance;
sem_t mutex;

void *func1();
void *func2();

void *schedule(){
    //while first queue is not empty -> choose the first thread in the queue to schedule
    while(!isEmpty(firstQueue))
    {
        myThread *th = getFirstElement(firstQueue);
        removeFirst(firstQueue);
        pthread_create(th, NULL, func1, NULL);
        printf("%d ", th->pid);
    }

    //while second queue is not empty -> scan queue for highest priority and schedule it (non preemptive)
    while(!isEmpty(secondQueue))
    {

    }

    //while third queue is not empty -> scan queue for smallest burst time and schedule it (non preemptive)
    while(!isEmpty(thirdQueue))
    {

    }
}



int main(int argc, char *argv[]){
    firstQueue = createList();
    secondQueue = createList();
    thirdQueue = createList();

    int class_num, pid, priority, burstTime;
    for(int i = 0; i < MAX_THREAD; i++){
        
        scanf("%d %d %d %d", &class_num, &pid, &priority, &burstTime);
        myThread *mythread = (myThread *) malloc(sizeof(myThread));
        mythread->classNumber = class_num;
        mythread->pid = pid;
        mythread->priority = priority;
        mythread->burstTime = burstTime;
        QueueNode *node = (QueueNode *) malloc(sizeof(QueueNode));
        node->my_thread = mythread;

        switch (class_num)
        {
        case 1:
            insertLast(firstQueue, node);
            break;
        case 2:
            insertLast(secondQueue, node);
            break;
        case 3:
            insertLast(thirdQueue, node);
            break;
        default:
            break;
        }
    }

    pthread_t thread1;
    // pthread_attr_t attr;
    pthread_create(&thread1, NULL, schedule, NULL);
    // pthread_t pid[MAX_THREAD];

    // printf("Starting Thread Program\n");

    // //DECLARE THREADS
    // pthread_t thread1;
    // pthread_t thread2;
    // pthread_attr_t attr;
    // //INTIALIZE SEMAPHORE
    // sem_init(&mutex, 0, 1);

    // //CREATE THREADS
    // printf("Balance before %d\n\n", balance);
    // pthread_create(&thread1, &attr, func1, NULL);
    // pthread_create(&thread2, &attr, func2, NULL);

    // //WAITING FOR THEADS TO FINISH
    // pthread_join(thread1, NULL);
    // pthread_join(thread2, NULL);


    // printf("\nBalance after %d\n", balance);
    // printf("Thread Ended\n");

    // sem_destroy(&mutex);

	return 0;
}

void *func1(){
    printf("run\n");
    // for(int i = 0; i < 100; i++){
    //     sem_wait(&mutex);
    //     balance += 1000;
    //     printf("Withdraw %d\n", balance);
    //     sem_post(&mutex);
    // }
    pthread_exit(0);
}

void *func2(){
    for(int i = 0; i < 100; i++){
        sem_wait(&mutex);
        balance -= 500;
        printf("Deposit %d\n", balance);
        sem_post(&mutex);
    }
    pthread_exit(0);
}