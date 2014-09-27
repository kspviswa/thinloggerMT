/*
 * example.c
 *
 *  Created on: 27-Sep-2014
 *      Author: kspviswa
 */

#include <stdio.h>
#include "thinLoggerMT.h" // thin-logger implementation
#include <sys/time.h>
#include <pthread.h>
#include <string.h>
#include <syscall.h> // note down the integer representation of thread id

/**
 *  Function that will utilize the library
 */

void *doWork(void *dummy)
{
	//int nThreadID = syscall(SYS_gettid);
	//int nThreadID = gettid();
	int nThreadID = syscall(__NR_gettid);
	printf("\n Thread %d doing work", nThreadID);
	THINLOGBUFFER myBuffer;

	struct timeval tp;
	gettimeofday(&tp, NULL);
	unsigned long ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

	myBuffer.nClockTicks = ms;
	myBuffer.nTestFloat = (676.56 + rand());
	myBuffer.nTestInt = rand();
	myBuffer.nTestLong = rand() + myBuffer.nTestFloat;
	strcpy(myBuffer.szTestChar, "Viswaaaaaa");

	int nRet = doInstrumentation(nThreadID, &myBuffer);

	if(nRet < 0)
	{
		printf("Instrumentation failed");
	}
}

void main()
{
	printf("\n Initializing the thin logger library");
	int nRet = init();

	if(nRet < 0)
	{
		// probably some problem
		printf("\n Unable to init the library");
		return;
	}

	// Lets play with 5 threads
	pthread_t threads[5];
	int i;
	for(i=0; i < 5; i++)
	{
		pthread_create(&threads[i], NULL, doWork, (void*)&nRet);
	}

	// i will sleep so that, threads start to log. Inbetween I may go down :-)
	sleep(2);

	// now lets create a core.
	int *p = NULL;
	printf("I should be coring now %d", *p);
}




