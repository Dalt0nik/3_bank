#include <stdio.h>
#include <stdlib.h>
#include "priorityQueue.h"

// be argumentu, grazina sukurtos eiles rodykle
priorityQueue* createQ()
{
    priorityQueue* newPQ;
    newPQ = malloc(sizeof(priorityQueue));
    newPQ->front = NULL;
    return newPQ;
}
// arg1 - eiles rodykle
// grazina: 1 - yra tuscia, 0 - nera tuscia
int isEmpty(priorityQueue* pq)
{
    if(pq->front == NULL)
        return 1;
    else
        return 0;
}
// arg1 - eiles rodykle
// grazina: 1 - yra pilna, 0 - nera pilna
int isFull(priorityQueue* pq)
{
    priorityQueue* temp = NULL;
    temp = malloc(sizeof(priorityQueue));
    
    if(temp != NULL)
    {
        free(temp);
        return 0;
    }  
    else
        return 1;  
}
// arg1 - eiles rodykle, arg2 - naujo elemento reiksme, arg3 - naujo elemento pr.
// grazina: 1 - sekmingai idetas, 0 - neidetas, si eile yra pilna
int insert(priorityQueue* pq, double newValue, int newPriority)
{
    if(isFull(pq) == 1)
        return 0;


    if(pq->front == NULL || pq->front->priority < newPriority)
    {
        node* temp = pq->front;
        pq->front = (node*)malloc(sizeof(node));
        pq->front->next = temp;
        pq->front->priority = newPriority;
        pq->front->value = newValue;
        return 1;
    }

    node* current;
    current = pq->front;

    while(current->next != NULL && current->next->priority >= newPriority)
    {
        current = current->next;
    }

    node *newNode = malloc(sizeof(node));
    newNode->next = current->next;
    newNode->priority = newPriority;
    newNode->value = newValue;

    current->next = newNode;
    return 1;
}
// arg1 - eiles rodykle, arg2 - rodykle i kintamaji, i kuri bus patalpinama virs. elemento reiksme
// grazina: 1 - sekmingai pasalintas, 0 - nepasalintas, eile tuscia
int pop(priorityQueue* pq, double* poppedValue)
{
    if(isEmpty(pq) == 1)
        return 0;

    node* temp;
    *poppedValue = pq->front->value;
    temp = pq->front;
    pq->front = pq->front->next;
    free(temp);
    return 1;
}
// arg1 - eiles rodykle, arg2 - rodykle i reiksmes kint., arg3 - rodykle i prioriteto kint.
// grazina: 1 - sekmingai ivyko, 0 - eile tuscia
int peek(priorityQueue* pq, double* topValue, int* topPriority)
{
    if(isEmpty(pq) == 1)
        return 0;
    
    *topValue = pq->front->value;
    *topPriority = pq->front->priority;

    return 1;
}
// arg1 - eiles rodykle
int deleteQ(priorityQueue* pq)
{
    if(isEmpty(pq) == 1)
        return 0;

    node* current, *prev;
    
    current = pq->front;

    while(current != NULL)
    {
        prev = current;
        current = current->next;
        free(prev);
    }
    pq->front = NULL;

    return 1;
}
