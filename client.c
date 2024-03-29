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
  /* SETTING UP */

  int list_s;
  int conn_s;
  struct sockaddr_in servaddr;
  struct sockaddr_in cli_addr;
  char buffer[MAX_LINE];
  char temp_buffer[MAX_LINE] = "CAP\\n";
  int n;

  // create and check listening Socket
  list_s = socket(AF_INET, SOCK_STREAM, 0);
  if(list_s < 0){
    fprintf(stderr, "ECHOSERV: Error creating listening socket\n");
    exit(EXIT_FAILURE);
  }
  else
    printf("Socket was successfully created! \n");

    //set byes in socket address to 0, assign IP and PORT
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect client socket to sever socket
    if( connect(list_s,(struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
      fprintf(stderr, "ECHOCLI: Error connecting with server \n");
      exit(EXIT_FAILURE);
    }
    else
      printf("Connected to server... \n");

      /* CONNECTED */

      while (1){
        memset(buffer, 0, sizeof(buffer));
        printf("Enter a s,f, or q: ");
        n = 0;
        while ((buffer[n++] = getchar()) != '\n')
            ;

        /* CAP\nxxx\n */
        if( *buffer =='s'){
          memset(buffer, 0, sizeof(buffer));
          printf("Enter a string:");
          n = 0;
          while ((buffer[n++] = getchar()) != '\n')
              ;
          strcat(temp_buffer, buffer);
          printf("Sending server: %s... \n", temp_buffer);
          write(list_s, temp_buffer, sizeof(temp_buffer));
          read(list_s, buffer, sizeof(buffer));
          printf("%s", buffer);
        }

        /* FILE\nxxx\n */
        if( *buffer == 'f'){
          memset(buffer, 0, sizeof(buffer));
          printf("Enter a string:");
          n = 0;
          while ((buffer[n++] = getchar()) != '\n')
              ;
          strcpy(temp_buffer, "FILE\\n");
          strcat(temp_buffer, buffer);
          printf("Sending server: %s... \n", temp_buffer);
          write(list_s, temp_buffer, sizeof(temp_buffer));

        }

        //exit chat
        if( *buffer == 'q'){
          write(list_s, buffer, sizeof(buffer));
          break;
        }
      }

      close(list_s);

}
