#include "tlo/thread.h"
#include <assert.h>
#include <errno.h>

void tloCancelThreads(pthread_t *threads, int numThreads) {
  assert(threads);

  for (int i = 0; i < numThreads; ++i) {
    int errco = pthread_cancel(threads[i]);
    assert(!errco);
    void *result;
    errco = pthread_join(threads[i], &result);
    assert(!errco);
    assert(result == PTHREAD_CANCELED);
  }
}

#define DEFAULT_ATTRIBUTES NULL

int tloCreateThreads(pthread_t *threads, int numThreads,
                     void *(*routine)(void *), void *arg) {
  assert(threads);
  assert(routine);

  for (int i = 0; i < numThreads; ++i) {
    int errco = pthread_create(&threads[i], DEFAULT_ATTRIBUTES, routine, arg);
    if (errco) {
      tloCancelThreads(threads, i);
      errno = errco;
      return TLO_THREAD_ERROR;
    }
  }

  return TLO_THREAD_SUCCESS;
}

#define IGNORE_OUT_ARG NULL

void tloJoinThreads(pthread_t *threads, int numThreads) {
  assert(threads);

  for (int i = 0; i < numThreads; ++i) {
    int errco = pthread_join(threads[i], IGNORE_OUT_ARG);
    assert(!errco);
  }
}
