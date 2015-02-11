# semaphores
Class Project for Operating Systems Class. I created a semaphore system that runs a lot of asynchronous and synchronous threads simultaneously using user threads.


/*
			Project -3 CSE 430- Operating Systems - SPRING 2013
				Professor: Dr. Partha Dasgupta



Authors:- Ragav Venkatesan (1202757889)
	  Dharav Shah	   (1204160836)

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
