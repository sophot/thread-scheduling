
#include <stdlib.h>
#include <pthread.h>

typedef struct myThread
{
    pthread_t myThread;
    int burstTime;
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

Queue *createList()
{
    Queue *newLL = (Queue *)malloc(sizeof(Queue));
    /*points both head and tail to null*/
    newLL->head = NULL;
    newLL->tail = NULL;
    return newLL;
};

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

void removeFirst(Queue *lL)
{
    QueueNode *tempPtr = lL->head;
    /*checks to see if list is empty*/
    if (tempPtr == NULL)
        ;
    else if (tempPtr == lL->tail)
    {
        // free(tempPtr->element);
        free(tempPtr);
        lL->head = NULL;
        lL->tail = NULL;
    }
    else
    {
        lL->head = tempPtr->next;
        // free(tempPtr->element);
        free(tempPtr);
    }
}

void *getFirstElement(Queue *lL)
{
    myThread *tempI;
    if (lL->head == NULL)
        tempI = NULL;
    else
        tempI = lL->head->my_thread;
    return tempI;
}

void freeQueue(Queue *lL)
{
    QueueNode *tempPtr;
    tempPtr = lL->head;
    while (tempPtr != NULL)
        ;
    {
        removeFirst(lL);
        tempPtr = lL->head;
    }
    free(lL); /*finally deallocates the list*/
}