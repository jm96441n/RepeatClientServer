// server socket practice based on https://beej.us/guide/bgnet/html/multi/syscalls.html#getaddrinfo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define MAXBACKLOG 1

int main () {
  int status, bind_status, sock_opt, server_socket, client_socket;
  int yes = 1;
  // servinfo holds the results for getaddrinfo, p is used as the iterator for the linked list that will be
  // stored in servinfo
  struct addrinfo hints, *servinfo, *p;
  char client_message[256];

  // make sure struct is empty
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC; // doesn't matter if IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
  hints.ai_flags = AI_PASSIVE; // fill in my IP for me

  status = getaddrinfo(NULL, "3490", &hints, &servinfo);

  if (status != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }

  for (p = servinfo; p != NULL; p = p->ai_next) {
    server_socket = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (server_socket == -1) {
      perror("server: socket");
      exit(1);
    }
    sock_opt = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    if (sock_opt == -1) {
      perror("setsockopt");
      exit(1);
    }

    bind_status = bind(server_socket, p->ai_addr, p->ai_addrlen);

    if (bind_status == -1) {
      close(server_socket);
      perror("server: bind");
      exit(1);
    }
  }

  freeaddrinfo(servinfo);

  listen(server_socket, MAXBACKLOG);

  client_socket = accept(server_socket, NULL, NULL);

  while(recv(client_socket, client_message, sizeof(client_message), 0) > 0) {
    printf("Client said: %s\n", client_message);
    write(client_socket, client_message, sizeof(client_message));
  }

  close(server_socket);

  return 0;
}
