// client socket practice based on https://beej.us/guide/bgnet/html/multi/syscalls.html#getaddrinfo
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
#define MESSAGE_LENGTH 256
int main () {
  int status, network_socket, connection_status;
  struct addrinfo hints, *clientinfo, *p;
  char server_message[MESSAGE_LENGTH], user_input[MESSAGE_LENGTH], echo[MESSAGE_LENGTH];

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  status = getaddrinfo(NULL, "3490", &hints, &clientinfo);

  if (status != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }

  for (p = clientinfo; p != NULL; p = p->ai_next) {
    network_socket = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

    if (network_socket == -1) {
      perror("client: socket");
      continue;
    }

    connection_status = connect(network_socket, p->ai_addr, p->ai_addrlen);

    if (connection_status == -1) {
      close(network_socket);
      perror("client: connection");
      continue;
    }

    break;
  }
  
  freeaddrinfo(clientinfo);

  strcpy(echo, "Echo Server");

  send(network_socket, echo, sizeof(echo), 0);

  while(recv(network_socket, &server_message, sizeof(server_message), 0) > 0) {
    printf("The server said: %s\n", server_message);
    printf("Input your message: ");
    fgets(user_input, sizeof(user_input), stdin);
    printf("\n");
    send(network_socket, user_input, sizeof(user_input), 0);
  }

  close(network_socket);

  return 0;
}
