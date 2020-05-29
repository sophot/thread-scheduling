#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include "Queue.c"

FILE *fileWrite;
Queue *FCFSQueue; //FCFSQueue
Queue *PriorityQueue;
Queue *SJFQueue;

void *workerFunc(void *);
void *schedule();

int main(int argc, char *argv[])
{
    // printf("START\n");
    FILE *fileRead = fopen("input.txt", "r");
    fileWrite = fopen("output.txt", "a");

    if (fileRead == NULL)
    {
        printf("ERROR! File cannot be opened to read");
        return 0;
    }

    FCFSQueue = createList();
    PriorityQueue = createList();
    SJFQueue = createList();
    int class_num, pid, priority, burstTime;

    // for (int i = 0; i < MAX_THREAD; i++)
    while (fscanf(fileRead, "%d %d %d %d", &class_num, &pid, &priority, &burstTime) != EOF)
    {
        // scanf("%d %d %d %d", &class_num, &pid, &priority, &burstTime);
        myThread *mythread = (myThread *)malloc(sizeof(myThread));
        mythread->classNumber = class_num;
        mythread->pid = pid;
        mythread->priority = priority;
        mythread->burstTime = burstTime;
        QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
        node->my_thread = mythread;

        switch (class_num)
        {
        case 1:
            insertLast(FCFSQueue, node);
            break;
        case 2:
            insertLast(PriorityQueue, node);
            break;
        case 3:
            insertLast(SJFQueue, node);
            break;
        default:
            break;
        }
    }
    fclose(fileRead);
    fclose(fileWrite);

    pthread_t thread1;
    pthread_create(&thread1, NULL, schedule, NULL);
    pthread_join(thread1, NULL);

    // printf("END\n");

    return 0;
}

void *workerFunc(void *thread)
{
    fileWrite = fopen("output.txt", "a");
    myThread *th = (myThread *)thread;
    for (int i = 0; i < th->burstTime; i++)
    {
        fprintf(fileWrite, "%d ", th->pid);
        printf("%d ", th->pid);
    }
    fprintf(fileWrite, "\n");
    printf("\n");
    fclose(fileWrite);
    pthread_exit(0);
}

void *schedule()
{
    printf("SCEDULING PROCESSES...\n");
    //while first queue is not empty -> choose the first thread in the queue to schedule
    while (!isEmpty(FCFSQueue))
    {
        myThread th = getFirst(FCFSQueue);
        deleteNode(FCFSQueue, &th);
        pthread_create(&(th.myThread), NULL, workerFunc, &(th.myThread));
        pthread_join(th.myThread, NULL);
    }

    //while second queue is not empty -> scan queue for highest priority and schedule it (non preemptive)
    while (!isEmpty(PriorityQueue))
    {
        myThread th = getHighestPriority(PriorityQueue);
        deleteNode(PriorityQueue, &th);
        pthread_create(&(th.myThread), NULL, workerFunc, &(th.myThread));
        pthread_join(th.myThread, NULL);
    }

    //while third queue is not empty -> scan queue for smallest burst time and schedule it (non preemptive)
    while (!isEmpty(SJFQueue))
    {
        myThread th = getSmallestBurstTime(SJFQueue);
        deleteNode(SJFQueue, &th);
        pthread_create(&(th.myThread), NULL, workerFunc, &(th.myThread));
        pthread_join(th.myThread, NULL);
    }

    printf("ALL PROCESS HAS BEEN SCHEDULED\n");
    pthread_exit(0);
}
