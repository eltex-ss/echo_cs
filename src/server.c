#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LINE_LENGTH 50

int main(void)
{
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
  
  server_address.sin_family = AF_INET;
  server_address.sin_port = 10000;
  server_address.sin_addr.s_addr = INADDR_ANY;
  if (bind(server_socket, (struct sockaddr*) &server_address,
           sizeof(struct sockaddr_in)) != 0) {
    perror("Can't bind socket");
    return -1;
  }

  if (listen(server_socket, 10) == -1) {
    perror("Can't listen 10 clients");
    return -1;
  }

  while (1) {
    char line[50];
    unsigned int client_size = sizeof(struct sockaddr_in);
    int client_socket = accept(server_socket, (struct sockaddr*)
                               &client_address, &client_size);
    if (client_socket == -1) {
      perror("Can't create client socket");
      return -1;
    }
    if (read(client_socket, line, LINE_LENGTH) > 0) {
      printf("Get: %s\n", line);
      if (write(client_socket, line, LINE_LENGTH) > 0) {
        continue;
      }
      else {
        perror("Can't write to client socket");
        return -1;
      }
    }
    else {
      printf("User disconnected\n");
      close(client_socket);
    }
  }

  return 0;
}
