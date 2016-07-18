#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LINE_LENGTH 50

int main(void)
{
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in server_address;
  char text[LINE_LENGTH];
  
  if (client_socket == -1) {
    perror("Can't create socket");
    return -1;
  }

  server_address.sin_family = AF_INET;
  server_address.sin_port = 10000;
  server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (connect(client_socket, (struct sockaddr*) &server_address,
              sizeof(struct sockaddr_in)) == -1) {
    perror("Can't connect to server");
    return -1;
  }

  printf("Enter the text\n");
  scanf("%s", text);

  if (write(client_socket, text, LINE_LENGTH) > 0) {
    if (read(client_socket, text, LINE_LENGTH) > 0) {
      printf("Answer: %s\n", text);
    }
    else {
      perror("Server is down");
      return -1;
    }
  }
  else {
    perror("Can't write to socket");
    return -1;
  }
  
  close(client_socket);

  return 0;
}
