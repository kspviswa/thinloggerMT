/*
 * thinLoggerMT.c
 *
 *  Created on: Jul 20, 2014
 *      Author: viswa
 */

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "thinLoggerMT.h"

THINLOGTHREADCONTAINER gGLobalBuffers[MAX_THREADS_PER_PROCESS] = {0};

pthread_mutex_t threadZeroMutex;

int init()
{
	if (pthread_mutex_init(&threadZeroMutex, NULL) != 0)
	{
		return -1;
	}
	return 1;
}

int doInstrumentation(unsigned long nThreadId, THINLOGBUFFER *pSrc)
{
	if(nThreadId < 0)
	{
		return -1;
	}

	int bUseLock = 0;

	if(nThreadId > (MAX_THREADS_PER_PROCESS - 1))
	{
		nThreadId = 0;
		bUseLock = 1;
	}

	if(bUseLock)
	{
		pthread_mutex_lock(&threadZeroMutex);
	}
	THINLOGTHREADCONTAINER *pRingBuffer = &gGLobalBuffers[nThreadId];

	if(!pRingBuffer)
	{
		if(bUseLock)
		{
			pthread_mutex_unlock(&threadZeroMutex);
		}
		
		return -1;
	}

	THINLOGBUFFER *pRingBufferNode = &pRingBuffer->theRingBuffers[pRingBuffer->nLookupId];

	if(!pRingBufferNode)
	{
		if(bUseLock)
		{
			pthread_mutex_unlock(&threadZeroMutex);
		}
		
		return -1;
	}

	memcpy(pRingBufferNode, pSrc, sizeof(THINLOGBUFFER));

	if(bUseLock)
	{
		pthread_mutex_unlock(&threadZeroMutex);
	}

	return 1;
}




