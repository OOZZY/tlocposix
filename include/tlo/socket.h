#ifndef TLO_SOCKET_H
#define TLO_SOCKET_H

#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

/*
 * - returns NULL on failure
 */
struct addrinfo *tloGetBindableWildcardAddress(const char *portOrService);

#define TLO_SOCKET_ERROR -1

/*
 * - returns TLO_SOCKET_ERROR on failure
 */
int tloGetSocketBoundToReusableAddress(struct addrinfo *addresses);

void *tloGetAddress(struct sockaddr *socket);
in_port_t tloGetPort(struct sockaddr *socket);
void tloFPrintAddressInformation(FILE *file, struct addrinfo *addresses);
void tloPrintAddressInformation(struct addrinfo *addresses);

#endif  // TLO_SOCKET_H
