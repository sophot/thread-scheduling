
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct
{
    pthread_t myThread;
    int pid;
    int burstTime;
    int priority;
    int classNumber;
} myThread;

typedef struct QueueNode
{
    myThread *my_thread;
    struct QueueNode *next;
} QueueNode;

typedef struct
{
    QueueNode *head;
    QueueNode *tail;
} Queue;

//API
Queue *createList();
void insertLast(Queue *, QueueNode *);
myThread getFirst(Queue *);
myThread getHighestPriority(Queue *);
myThread getSmallestBurstTime(Queue *);
void deleteNode(Queue *, myThread *);
bool isEmpty(Queue *);

//API CODE
Queue *createList()
{
    Queue *newLL = (Queue *)malloc(sizeof(Queue));
    /*points both head and tail to null*/
    newLL->head = NULL;
    newLL->tail = NULL;
    return newLL;
}

void insertLast(Queue *lL, QueueNode *inElement)
{
    /*allocates a new node*/
    QueueNode *newLLN = (QueueNode *)malloc(sizeof(QueueNode));
    newLLN->my_thread = inElement->my_thread;

    /*only when the list is empty*/
    if (lL->head == NULL)
    {
        lL->head = newLLN;
        lL->tail = newLLN;
        newLLN->next = NULL;
    }
    /*when the list has one or more element*/
    else
    {
        QueueNode *tempPtr = lL->tail;
        newLLN->next = NULL;
        lL->tail = newLLN;
        tempPtr->next = lL->tail;
    }
}

myThread getFirst(Queue *lL)
{
    myThread *tempI;
    if (lL->head == NULL)
        tempI = NULL;
    else
        tempI = lL->head->my_thread;
    return *tempI;
}

myThread getHighestPriority(Queue *lL)
{
    QueueNode *tempI = lL->head;
    myThread *highest = tempI->my_thread;

    while (tempI != NULL)
    {
        if (tempI->my_thread->priority < highest->priority)
        {
            highest = tempI->my_thread;
        }
        tempI = tempI->next;
    }
    return *highest;
}

myThread getSmallestBurstTime(Queue *lL)
{
    QueueNode *tempI = lL->head;
    myThread *smallest = tempI->my_thread;

    while (tempI != NULL)
    {
        if (tempI->my_thread->burstTime < smallest->burstTime)
        {
            smallest = tempI->my_thread;
        }
        tempI = tempI->next;
    }
    return *smallest;
}

void deleteNode(Queue *lL, myThread *th)
{
    QueueNode *tempI = lL->head, *prev;

    // If head node itself holds the key to be deleted
    if (tempI != NULL && tempI->my_thread->pid == th->pid)
    {
        lL->head = tempI->next; // Changed head
        free(tempI);            // free old head
        return;
    }

    while (tempI != NULL && tempI->my_thread->pid != th->pid)
    {
        prev = tempI;
        tempI = tempI->next;
    }

    // If key was not present in linked list
    if (tempI == NULL)
        return;

    // Unlink the node from linked list
    prev->next = tempI->next;

    free(tempI); // Free memory
}

bool isEmpty(Queue *lL)
{
    return (lL->head == NULL);
}
