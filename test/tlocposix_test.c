#include "tlocposix_test.h"
#include <stdio.h>
#include <tlo/test.h>

int main(void) {
  testSocket();
  testThread();
  puts("===============");
  puts("All tests done.");
  puts("===============");
  tloTestPrintReport();
  tloTestExit();
}
