#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

int main () {

//  char server_message[256] = "You have reached the server";

  // create the server socket
  int server_socket;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9002);
  server_address.sin_addr.s_addr = INADDR_ANY;

  // bind the socket to our specified IP and Port
  int bind_status = bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

  if (bind_status == -1) {
    printf("couldn't bind, try again");
    return 1;
  }

  // second arg is the amount of connections can be waiting at any point in time for the socket
  listen(server_socket, 5);

  printf("server started, listening for requests....\n\n\n");
  // create the client socket that will be returned from the client
  int client_socket;
  char client_message[256];

  // null for last 2 params, they are structs that contain the address of the client connection
  client_socket = accept(server_socket, NULL, NULL);

  while(recv(client_socket, client_message, sizeof(client_message), 0) > 0) {
    printf("request received...\n\n");
    write(client_socket, client_message, sizeof(client_message));
  }
/*
  printf("request received...\n\n");
  // send data to client socket
  send(client_socket, server_message, sizeof(server_message), 0);

  char client_message[256];
  recv(client_socket, client_message, sizeof(client_message), 0);

  printf("request received...\n\n");
  write(client_socket, client_message, sizeof(client_message));

  printf("response sent...\n\n");
*/
  close(server_socket);

  return 0;
}
