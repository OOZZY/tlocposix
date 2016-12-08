#include <assert.h>
#include <netdb.h>
#include <stdio.h>
#include <tlo/socket.h>
#include "tlocposix_test.h"

#define SOME_PORT_STR "12345"
#define SOME_PORT_INT 12345

static void testGetBindableWildcardAddress(void) {
  struct addrinfo *addresses = tloGetBindableWildcardAddress(SOME_PORT_STR);
  assert(addresses);
  tloPrintAddressInformation(addresses);
  freeaddrinfo(addresses);
}

static void testGetSocketBoundToReusableAddress(void) {
  struct addrinfo *addresses = tloGetBindableWildcardAddress(SOME_PORT_STR);
  int socketfd = tloGetSocketBoundToReusableAddress(addresses);
  assert(socketfd != TLO_SOCKET_ERROR);
  freeaddrinfo(addresses);
}

void testSocket(void) {
  testGetBindableWildcardAddress();
  testGetSocketBoundToReusableAddress();

  puts("====================");
  puts("Socket tests passed.");
  puts("====================");
}
