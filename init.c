#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "wordle.h"

static void sighandler(int signo){
  if(signo == SIGINT){
    char path[] = "/tmp/mario";
    remove(path);
    exit(0);
  }
  if(signo == SIGPIPE){
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  signal(SIGINT, sighandler);
  signal(SIGPIPE, sighandler);

  int to_client; // Private
  int from_client; // WKP
  int WKPfd;
  if (argc > 1) {
    printf("%s", argv[1]);
    if(strcmp(argv[1], "Player_1") == 0){
      to_client = server_setup();
      WKPfd = to_client;
      from_client = server_handshake( &to_client );
      int random = (rand() % 101);
      char sent_int[20];
      sprintf(sent_int, "%d", random);
      int n = write(to_client, sent_int, sizeof(sent_int));
      if(n < 0){
        close(to_client);
        to_client = WKPfd;
      }
    }
    else if(strcmp(argv[1], "Player_2") == 0){
      int to_server;
      int from_server;
      from_server = client_handshake( &to_server );
      char received_int[100];
      read(from_server, received_int, sizeof(received_int));
      printf("Received_int %s\n", received_int);
    }
    else {
      printf("Please enter either Player_1 or Player_2\n");
      return 1;
    }
  }
  else {
    printf("Please give an argument\n");
  }


  return 0;
}
