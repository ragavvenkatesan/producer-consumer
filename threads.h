#ifndef THREADS_H
#define THREADS_H


#include "q.h"


struct TCB_t *ReadyQ;
int exitCounter=0;

// If the ReadyQ is empty this function will reintialize and exit.
void exit_fn()
{	
	InitQueue(&ReadyQ);
	printf("							Queue Re-initialized... \n");
	printf("							Queue is now empty ... \n");
}


void start_thread(void (*function)(void))
{
	int *stack;	
	stack=(int *) malloc(8192);
	printf("							Starting a new thread .. \n");
	struct TCB_t *tcb;
	tcb=NewItem();	
	//tcb=(struct TCB_t*) malloc(sizeof(tcb));
	init_TCB(tcb,function,stack,8192);
	AddQueue(&ReadyQ,tcb);
}

void run()
{   // real code
    ucontext_t parent;     
    getcontext(&parent);   // magic sauce
    swapcontext(&parent, &(ReadyQ->context));  
}

void yield() // similar to run
{
   printf("							Oh no !! CONTEXT SWITCH .. !!\n");
   RotateQ(&ReadyQ);
	if(ReadyQ==NULL)
	{	
		exitCounter++;
		start_thread(exit_fn);
		run();

	}	
   struct TCB_t *temp;
   temp=NewItem();
   temp=ReadyQ->prev;
   swapcontext(&(temp->context),&(ReadyQ->context));   
}



#endif
