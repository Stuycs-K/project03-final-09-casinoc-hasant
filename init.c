#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>
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
  srand(time(NULL));

  int to_client; // Private
  int from_client; // WKP
  int to_server; // WKP
  int from_server; // Private
  int WKPfd;
  if (argc > 1) {
    if(strcmp(argv[1], "Player1") == 0){
      /* to_client = server_setup();
      WKPfd = to_client;
      from_client = server_handshake( &to_client ); */
      while(1){
        to_client = server_setup();
        WKPfd = to_client;
        from_client = server_handshake( &to_client );

        while(1){
          int random = (rand() % 101);
          char sent_int[20];
          sprintf(sent_int, "%d", random);
          int n = write(to_client, sent_int, sizeof(sent_int));
          if(n < 0){
            close(to_client);
            to_client = WKPfd;
            break;
          }
          sleep(1);
        }
      }
    }
    else if(strcmp(argv[1], "Player2") == 0){
      from_server = client_handshake( &to_server );
      while(1){
        char recieved_int[100];
        read(from_server, recieved_int, sizeof(recieved_int));
        printf("recieved_int %s\n", recieved_int);
        sleep(1);
      }
    }
    else {
      printf("Please enter either Player1 or Player2\n");
      return 1;
    }
  }
  else {
    printf("Please give an argument\n");
    char guess[5];
    char * returning;

    for(int i = 1; i <= 6; i++){
        printf("Enter guess: \n");
        fgets(guess, sizeof(guess), stdin);
        returning = wordle_function(guess);
        printf("returned: %s\n", returning);
        if(strcmp(returning, "TESTS") == 0){
          printf("You won in %d guesses!\n", i);
          free(returning);
          return 0;
        }
    }
    printf("Game over, you are out guesses.\n");
    free(returning);

  }
  return 0;
}
