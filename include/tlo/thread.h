#ifndef TLO_THREAD_H
#define TLO_THREAD_H

#include <pthread.h>

#define TLO_NO_RETURN_VALUE NULL

void tloCancelThreads(pthread_t *threads, int numThreads);

#define TLO_THREAD_ERROR -1
#define TLO_THREAD_SUCCESS 0
#define TLO_NO_ARGUMENT NULL

/*
 * - returns TLO_THREAD_ERROR on failure
 */
int tloCreateThreads(pthread_t *threads, int numThreads,
                     void *(*routine)(void *), void *arg);

void tloJoinThreads(pthread_t *threads, int numThreads);

#endif  // TLO_THREAD_H
