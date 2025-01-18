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
      to_client = server_setup();
      WKPfd = to_client;
      from_client = server_handshake( &to_client );

      char guess[7]; // Needs to be size 7 because of new line and null byte characters.
      char * hint;

      for(int i = 1; i <= 6; i++){
        write(to_client, "Enter guess: ", 15); // Sent on private pipe to client.
        read(from_client, guess, sizeof(guess)); // Read guess from WKP.
        printf("guess: %s", guess);
        hint = wordle_function(guess);
        if(strcmp(hint, "TESTS") == 0){
          char win[100];
          sprintf(win, "You won in %d guesses!\n", i);
          write(to_client, win, sizeof(win));
          free(hint);
          return 0;
        }
        write(to_client, hint, sizeof(hint)); // Sent on private pipe to client
        sleep(1);
      }
      write(to_client, "Game over, you are out of guesses.\n", 35);
      free(hint);
    }
    else if(strcmp(argv[1], "Player2") == 0){
      char guess[7]; // Needs to be size 7 because of new line and null byte characters.
      
      from_server = client_handshake( &to_server );

      while(1){
        char prompt[100];
        read(from_server, prompt, sizeof(prompt));
        printf("%s", prompt);
        if(strstr(prompt, "Game over") != 0){
          exit(0);
        }
        fgets(guess, sizeof(guess), stdin);
        write(to_server, guess, sizeof(guess));
        char hint[100];
        read(from_server, hint, sizeof(hint));
        printf("hint: %s\n", hint);
        if(strstr(hint, "You won") != 0){
          break;
        }
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
  }
  return 0;
}
