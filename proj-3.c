/*
			Project -3 CSE 430- Operating Systems - SPRING 2013
				Professor: Dr. Partha Dasgupta



Author:- Ragav Venkatesan 

Activating Functions:-
	
	method1()  - starts threads for mutex problems of function 1 and function 2
		     uses mutex1 and 'i'
	method2()  - starts threads of one set of producers and consumers producing on the same buffer
		     uses mutex2 and buffer1
	intense1() - starts a whole bunch of functions 1, 2 and two sets of producers and consumers on different mutexes and buffers on 		     the same ReadyQ. 

Main:-
	Calls one of the activating functions. ( Could also run any activation functions in a thread if you want, we didn't do it as it 	will become more confusing to track the progress )

Yields:-

	There are a whole bunches of yields randomly put in place to simulate a very nasty scheduler.





Running instructions:-

	Please run on a full screen terminal to observe the scheduler notices properly aligned. 
	uncomment call to one of the activating functions ( if you do many, only the first will run )

		compile and run as follows:-
			
			gcc proj-3.c
			./a.out 


Let the magic begin !! 

*/


// Include Files //
#include<stdio.h>
#include<unistd.h>
#include "sem.h"
#include <math.h>


// Declare Buffer structure and global buffers and other global variables //

struct BUFF
{
	int slot[20];
	int out;
	int in;
} buffer1, buffer2;

int i=1;
int N=20;
int item1=0;
int item2=0;


struct semaphore mutex1;
struct semaphore mutex2;
struct semaphore mutex3;
struct semaphore full;
struct semaphore empty;










//<=================================================>//
/* Mutual Exclusion Codes - Function 1 & 2 */

void f1()
{
	int j=1;
	while(i>0)
	{				
		P(&mutex1);	
		printf("Function 1 says - Entering Critical Section\n");	
		printf("Function 1 says i=%d\n",i);
		yield();
		printf("Function 1 says j=%d\n",j);
		i++;
		j++;
		sleep(1);
		yield();
		printf("Function 1 says - Exiting Critical Section\n");
		V(&mutex1);
		printf("Function 1 says - Outside Critical Section\n");
		sleep(1);
	}
	
}

void f2()
{
	int j=1;
	while(i>0)
	{		
		P(&mutex1);	
		printf("Function 2 says - Entering Critical Section\n");	
		printf("Function 2 says i=%d\n",i);
		yield();
		printf("Function 2 says j=%d\n",j);
		i++;
		j++;
		sleep(1);
		yield();
		printf("Function 2 says - Exiting Critical Section\n");
		V(&mutex1);
		printf("Function 2 says - Outside Critical Section\n");
		sleep(1);
	}
	
}













//<=================================================>//
/* Producer - Consumer Solution*/

// First set of producers and consumers
void producer1()
{
	while(1)
	{				
		//printf("P(full=%d) by producer \n",full.sem);
		P(&full);
		//printf("P(mutex=%d) by producer \n",mutex2.sem);
		P(&mutex2);
		item1++;
		printf("1- Produced item number %d ..\n",item1);
		buffer1.slot[buffer1.in]=item1;
		yield();
		yield();
		buffer1.in=(buffer1.in+1)%N;
		sleep(1);
	        //printf("V(mutex=%d) by producer \n",mutex2.sem);		
		V(&mutex2);
		//printf("V(empty=%d) by producer \n",empty.sem);
		V(&empty);
	}
}
		

void consumer1()
{
	int item1=0;
	while(1)
	{		
		//printf("P(empty=%d) by consumer \n",empty.sem);
		P(&empty);
		//printf("P(mutex=%d) by consumer \n",mutex2.sem);
		P(&mutex2);
		item1=buffer1.slot[buffer1.out];
		yield();
		buffer1.out=(buffer1.out+1)%N;
		printf("1- Consumed item number %d .. \n", item1);
		sleep(1);
		//printf("V(mutex=%d) by consumer \n",mutex2.sem);
		V(&mutex2);
		//printf("V(full=%d) by consumer \n",full.sem);
		V(&full);
	}
}






// Another set of producers and consumers 

void producer2()
{
	while(1)
	{				
		//printf("P(full=%d) by producer \n",full.sem);
		P(&full);
		//printf("P(mutex=%d) by producer \n",mutex2.sem);
		P(&mutex3);
		item2++;
		printf("2- Produced item number %d ..\n",item2);
		buffer2.slot[buffer2.in]=item2;
		yield();
		yield();
		buffer2.in=(buffer2.in+1)%N;
		sleep(1);
	        //printf("V(mutex=%d) by producer \n",mutex2.sem);		
		V(&mutex3);
		//printf("V(empty=%d) by producer \n",empty.sem);
		V(&empty);
	}
}
		

void consumer2()
{
	int item1=0;
	while(1)
	{		
		//printf("P(empty=%d) by consumer \n",empty.sem);
		P(&empty);
		//printf("P(mutex=%d) by consumer \n",mutex2.sem);
		P(&mutex3);
		item2=buffer2.slot[buffer2.out];
		yield();
		buffer2.out=(buffer2.out+1)%N;
		printf("2- Consumed item number %d .. \n", item2);
		sleep(1);
		//printf("V(mutex=%d) by consumer \n",mutex2.sem);
		V(&mutex3);
		//printf("V(full=%d) by consumer \n",full.sem);
		V(&full);
	}
}













// Activating Functions
void method1()
{	
	InitQueue(&ReadyQ);
	InitSem(&mutex1,1);
	
	// Method 1
	start_thread(f1);
        start_thread(f2);
	run();
}

void method2()
{	
	InitQueue(&ReadyQ);
	InitSem(&mutex2,1);
	

	// Method 2
	InitSem(&full,N);
	InitSem(&empty,0);
	buffer1.in=0;
	buffer1.out=0;
	start_thread(producer1);
	start_thread(consumer1);
	start_thread(producer1);
	start_thread(consumer1);	
	run();
}



void intense1()
{	
	InitQueue(&ReadyQ);
	InitSem(&mutex1,1);
	InitSem(&mutex2,1);
	InitSem(&mutex3,1);

	// Method 1
	start_thread(f1);
    start_thread(f2);
	start_thread(f1);
	start_thread(f1);
	start_thread(f2);


	// Method 2
	InitSem(&full,N);
	InitSem(&empty,0);
	buffer1.in=0;
	buffer1.out=0;
	buffer2.in=0;
	buffer2.out=0;
	start_thread(consumer2);
	start_thread(consumer1);
	start_thread(producer2);
	start_thread(consumer1);
	start_thread(producer1);
	start_thread(consumer1);
	start_thread(producer2);
	start_thread(producer2);
	start_thread(producer2);
	start_thread(producer1);
	start_thread(consumer2);
	start_thread(producer1);
	start_thread(producer1);
	start_thread(producer1);
	start_thread(producer2);
	start_thread(producer2);
	start_thread(producer2);
	start_thread(producer1);
	start_thread(consumer2);
	start_thread(consumer1);
	start_thread(consumer2);
	run();
}


int main()
{
	//method1();
	//method2();
	intense1();
}


