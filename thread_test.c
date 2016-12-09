#include <stdio.h>
#include <tlo/test.h>
#include <tlo/thread.h>
#include "tlocposix_test.h"

#define NUM_THREADS 4
#define NUM_SECONDS_TO_SLEEP 3600
#define NUM_NSECONDS_TO_SLEEP 0
#define IGNORE_OUT_ARG NULL

static void *sleepForOneHour(void *arg) {
  (void)arg;

  // nanosleep() is a cancellation point
  const struct timespec interval = {NUM_SECONDS_TO_SLEEP,
                                    NUM_NSECONDS_TO_SLEEP};
  nanosleep(&interval, IGNORE_OUT_ARG);

  pthread_exit(TLO_NO_RETURN_VALUE);
}

static void testCreateAndCancelThreads(void) {
  pthread_t threads[NUM_THREADS];
  int error =
      tloCreateThreads(threads, NUM_THREADS, sleepForOneHour, TLO_NO_ARGUMENT);
  TLO_ASSERT(!error);
  tloCancelThreads(threads, NUM_THREADS);
}

static void *doNothing(void *arg) {
  (void)arg;
  pthread_exit(TLO_NO_RETURN_VALUE);
}

static void testCreateAndJoinThreads(void) {
  pthread_t threads[NUM_THREADS];
  int error =
      tloCreateThreads(threads, NUM_THREADS, doNothing, TLO_NO_ARGUMENT);
  TLO_ASSERT(!error);
  tloJoinThreads(threads, NUM_THREADS);
}

void testThread(void) {
  testCreateAndCancelThreads();
  testCreateAndJoinThreads();

  puts("==================");
  puts("Thread tests done.");
  puts("==================");
}
