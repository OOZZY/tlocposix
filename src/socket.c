#include "tlo/socket.h"
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

struct addrinfo *tloGetBindableWildcardAddress(const char *portOrService) {
  assert(portOrService);

  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  struct addrinfo *localAddressInfo;

  int errco = getaddrinfo(NULL, portOrService, &hints, &localAddressInfo);
  if (errco) {
    errno = errco;
    return NULL;
  }

  return localAddressInfo;
}

int tloGetSocketBoundToReusableAddress(struct addrinfo *addresses) {
  assert(addresses);

  int socketfd = -1;
  int errco = errno;
  bool succeeded = false;

  for (struct addrinfo *address = addresses; address != NULL;
       address = address->ai_next) {
    socketfd =
        socket(address->ai_family, address->ai_socktype, address->ai_protocol);
    if (socketfd == -1) {
      errco = errno;
      continue;
    }

    int value = 1;
    int error =
        setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
    if (error) {
      errco = errno;
      close(socketfd);
      continue;
    }

    error = bind(socketfd, address->ai_addr, address->ai_addrlen);
    if (error) {
      errco = errno;
      close(socketfd);
      continue;
    }

    succeeded = true;
    break;
  }

  if (succeeded) {
    return socketfd;
  } else {
    errno = errco;
    return TLO_SOCKET_ERROR;
  }
}

void *tloGetAddress(struct sockaddr *socket) {
  assert(socket);

  if (socket->sa_family == AF_INET) {
    return &(((struct sockaddr_in *)socket)->sin_addr);
  }

  if (socket->sa_family == AF_INET6) {
    return &(((struct sockaddr_in6 *)socket)->sin6_addr);
  }

  assert(false);
  return NULL;
}

in_port_t tloGetPort(struct sockaddr *socket) {
  assert(socket);

  if (socket->sa_family == AF_INET) {
    return ntohs(((struct sockaddr_in *)socket)->sin_port);
  }

  if (socket->sa_family == AF_INET6) {
    return ntohs(((struct sockaddr_in6 *)socket)->sin6_port);
  }

  assert(false);
  return 0;
}

void tloFPrintAddressInformation(FILE *file, struct addrinfo *addresses) {
  assert(file);
  assert(addresses);

  for (struct addrinfo *address = addresses; address != NULL;
       address = address->ai_next) {
    char addressString[INET6_ADDRSTRLEN];
    const char *result =
        inet_ntop(address->ai_family, tloGetAddress(address->ai_addr),
                  addressString, INET6_ADDRSTRLEN);
    assert(result);
    (void)result;

    in_port_t port = tloGetPort(address->ai_addr);

    fprintf(file, "%s|%u\n", addressString, port);
  }
}

void tloPrintAddressInformation(struct addrinfo *addresses) {
  assert(addresses);

  tloFPrintAddressInformation(stdout, addresses);
}
