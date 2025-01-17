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
  int to_server; // WKP
  int from_server; // Private
  int WKPfd;
  if (argc > 1) {
    if(strcmp(argv[1], "Player1") == 0){
      to_client = server_setup();
      WKPfd = to_client;
      from_client = server_handshake( &to_client );
      //open("answer1.txt", O_RDWR | O_CREAT, 0644);
      //open("guess1.txt", O_RDWR | O_CREAT, 0644);
      
    }
    else if(strcmp(argv[1], "Player2") == 0){
      from_server = client_handshake( &to_server );
      //open("answer2.txt", O_RDWR | O_CREAT, 0644);
      //open("guess2.txt", O_RDWR | O_CREAT, 0644);
    }
    else {
      printf("Please enter either Player1 or Player2\n");
      return 1;
    }
  }
  else {
    printf("Please give an argument\n");
  }
  return 0;
}
