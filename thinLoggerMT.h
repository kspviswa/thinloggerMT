/*
 * thinLoggerMT.h
 *
 *  Created on: Jul 20, 2014
 *      Author: viswa
 */

#ifndef THINLOGGERMT_H_
#define THINLOGGERMT_H_

#define MAX_CHAR 48
#define MAX_BUFFERS_PER_THREAD 5
#define MAX_THREADS_PER_PROCESS 1000

struct thinLogBuffer
{
	unsigned long nTestLong;
	int nTestInt;
	float nTestFloat;
	char szTestChar[MAX_CHAR];
};

typedef struct thinLogBuffer THINLOGBUFFER;

struct thinLogThreadContainer
{
	unsigned long nLookupId;
	THINLOGBUFFER theRingBuffers[MAX_BUFFERS_PER_THREAD];
};

typedef struct thinLogThreadContainer THINLOGTHREADCONTAINER;

int init();
int doInstrumentation(unsigned long nThreadId, THINLOGBUFFER *pSrc);

#endif /* THINLOGGERMT_H_ */
