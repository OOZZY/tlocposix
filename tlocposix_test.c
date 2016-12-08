#include "tlocposix_test.h"
#include <stdio.h>

int main(void) {
  testSocket();
  testThread();
  puts("=================");
  puts("All tests passed.");
  puts("=================");
}
