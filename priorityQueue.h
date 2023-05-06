#pragma once

typedef struct node node;
typedef struct priorityQueue priorityQueue;
struct node
{
    double value;
    int priority;
    node* next;
};

struct priorityQueue
{
    node* front;
};

// be argumentu, grazina sukurtos eiles rodykle
priorityQueue* createQ();

// arg1 - eiles rodykle
int deleteQ(priorityQueue* pq);

// arg1 - eiles rodykle
// grazina: 1 - yra tuscia, 0 - nera tuscia
int isEmpty(priorityQueue* pq);

// arg1 - eiles rodykle
// grazina: 1 - yra pilna, 0 - nera pilna
int isFull(priorityQueue* pq);

// arg1 - eiles rodykle, arg2 - naujo elemento reiksme, arg3 - naujo elemento pr.
// grazina: 1 - sekmingai idetas, 0 - neidetas, si eile yra pilna
int insert(priorityQueue* pq, double newValue, int newPriority);

// arg1 - eiles rodykle, arg2 - rodykle i kintamaji, i kuri bus patalpinama virs. elemento reiksme
// grazina: 1 - sekmingai pasalintas, 0 - nepasalintas, eile tuscia
int pop(priorityQueue* pq, double* poppedValue);

// arg1 - eiles rodykle, arg2 - rodykle i reiksmes kint., arg3 - rodykle i prioriteto kint.
// grazina: 1 - sekmingai ivyko, 0 - eile tuscia
int peek(priorityQueue* pq, double* topValue, int* topPriority);