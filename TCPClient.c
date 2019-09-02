#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

int main () {

  // create a socket
  int network_socket;
  network_socket = socket(AF_INET, SOCK_STREAM, 0);

  // specify an address for the socket
  struct sockaddr_in server_address;

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9002);
  server_address.sin_addr.s_addr = INADDR_ANY;

  int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

  if (connection_status == -1) {
    printf("There was a problem making a connection to the remote socket \n\n");
    return 1;
  }

  char initial_message[256] = "Server is ready to get started! \n\n";
  char user_input[256];
  char server_response[256];

  send(network_socket, initial_message, sizeof(initial_message), 0);
  while (recv(network_socket, &server_response, sizeof(server_response), 0) > 0) {
    printf("\nServer sent back: %s\n\n", server_response);
    printf("Enter your message: ");
    fgets(user_input, sizeof(user_input), stdin);

    if(strncmp(user_input,"q\n", sizeof(user_input)) == 0) {
      break;
    }

    send(network_socket, user_input, sizeof(user_input), 0);
  }
  /*
  recv(network_socket, &server_response, sizeof(server_response), 0);

  printf("The server sent the data: %s\n", server_response);

  char message[256] = "Message from client";

  printf("sending message: %s\n", message);
  send(network_socket, message, sizeof(message), 0);

  char response[256];

  recv(network_socket, response, sizeof(response), 0);

  printf("The server sent the data: %s\n", response);
  */
  // close the socket
  close(network_socket);
  return 0;
}
