#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

/* Global constants */
#define PORT 2002
#define MAX_LINE 1000
#define LISTENQ 1024

int main(){
  int list_s;
  int conn_s;
  struct sockaddr_in servaddr;
  char buffer[MAX_LINE];

  // create and check listening Socket
  list_s = socket(AF_INET, SOCK_STREAM, 0);
  if(list_s < 0){
    printf("Failure with socket creation \n");
    exit(0);
  }
  else
    printf("Succesful socket creation \n");
}