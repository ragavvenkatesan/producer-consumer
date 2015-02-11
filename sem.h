#ifndef SEM_H
#define SEM_H

#include "threads.h"

struct semaphore
{
	int sem;
	struct TCB_t *q;
};

void InitSem(struct semaphore *semA, int value)
{
	semA->sem=value;
	InitQueue(&(semA->q));	
}

void P(struct semaphore *semA) // similar to run
{
	struct TCB_t *temp;
	temp=NewItem();
	semA->sem = semA->sem- 1;
   	if(semA->sem < 0)
	{	
		printf("							BLOCKING \n");	
		struct TCB_t *temp;	
		temp=DelQueue(&ReadyQ); // Deletes a thread
		AddQueue(&(semA->q),temp);
		swapcontext(&(temp->context),&(ReadyQ->context));
		
	}
}

void V(struct semaphore *semA)
{
	struct TCB_t *temp;
	temp=NewItem();
	
	(semA->sem)++;
	if(semA->sem < 1)
	{	
		temp=DelQueue(&(semA->q)); // Deletes a thread
		if(temp!=NULL)
		{
			printf("							UNBLOCKING \n");
			AddQueue(&ReadyQ,temp);
			//RotateQ(&ReadyQ);
		}
	}
	yield();
}

#endif
