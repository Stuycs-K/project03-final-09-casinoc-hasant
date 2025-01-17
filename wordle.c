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
#include <ctype.h>
#include <time.h>
#include "wordle.h"

int server_setup() {
  int from_client = 0;
  char path[] = "/tmp/mario";
  remove(path);
  int n = mkfifo(path, 0777);
  if(n == -1) {
    printf("%s\n",strerror(errno));
    exit(1);
  }
  int fd = open(path, O_RDONLY);
  if(fd == -1) {
    printf("%s\n",strerror(errno));
    exit(1);
  }
  from_client = fd;
  return from_client;
}

int server_handshake(int *to_client) {
  int from_client;
  srand(time(NULL));

  // Get client pid.
  char private[100];
  int private_pipe_PID;
  read(*to_client, private, sizeof(private));
  sscanf(private, "%d", &private_pipe_PID);

  // Open Private Pipe to client.
  char path_prefix[100] = "/tmp/";
  char private_path[100];
  sprintf(private_path, "%s%d", path_prefix, private_pipe_PID);
  int fd = open(private_path, O_WRONLY);
  if(fd == -1) {
    printf("%s\n",strerror(errno));
    exit(1);
  }
  *to_client = fd;

  // Send acknowledgement of connection through Private Pipe.
  char answer[6];
  printf("Enter a 5 letter word: ");
  fgets(answer, sizeof(answer), stdin);
  for (int i = 0; i < strlen(answer); i++) {
    answer[i] = toupper(answer[i]);
  }
  //write(fd, syn_ack, sizeof(syn_ack));
  int random = (rand() % 100000);
  char syn_ack[20];
  sprintf(syn_ack, "%d", random);
  write(fd, syn_ack, sizeof(syn_ack));

  // Get second acknowlegdment.
  char ack[100];
  char path[] = "/tmp/mario";
  int df = open(path, O_RDONLY);
  if(df == -1) {
    printf("%s\n",strerror(errno));
    exit(1);
  }
  read(df, ack, sizeof(ack));
  printf("ack %s\n", ack);

  from_client = df;
  return from_client;
}

int client_handshake(int *to_server) {
  int from_server;
  char WKP_path[] = "/tmp/mario";

  // Open Well Known Pipe to server.
  int fd = open(WKP_path, O_WRONLY);
  if(fd == -1) {
    printf("%s\n",strerror(errno));
    exit(1);
  }

  // Create a Private Pipe.
  int pid = getpid();
  char path_prefix[100] = "/tmp/";
  char private_path[100];
  char private_pid[100];
  sprintf(private_pid, "%d", pid);
  sprintf(private_path, "%s%d", path_prefix, pid);
  remove(private_path);
  int n = mkfifo(private_path, 0777);
  if(n == -1) {
    printf("%s\n",strerror(errno));
    exit(1);
  }

  // Send file descriptor of Private Pipe to the server via WKP.
  write(fd, private_pid, sizeof(private_pid));

  // Wait for syn_ack from server on Private Pipe.
  int df = open(private_path, O_RDONLY);
  if(df == -1) {
    printf("%s\n",strerror(errno));
    exit(1);
  }
  remove(private_path);
  char syn_ack[100];
  read(df, syn_ack, sizeof(syn_ack));
  printf("syn_ack %s\n", syn_ack);

  // Send ack to server on WKP with pid+1.
  char answer[6];
  printf("Enter a five letter word: ");
  fgets(answer, sizeof(answer), stdin);
  for (int i = 0; i < strlen(answer); i++) {
    answer[i] = toupper(answer[i]);
  }
  //write(fd, ack, sizeof(ack));
  int change_num;
  sscanf(syn_ack, "%d", &change_num);
  change_num++;
  char ack[100];
  sprintf(ack, "%d", change_num);
  write(fd, ack, sizeof(ack));

  from_server = df;
  return from_server;
}

void guess_function1(){
  int ans = open("answer1.txt", O_RDONLY);
  char guess[6];
  for (int i = 0; i < strlen(guess); i++) {
    guess[i] = toupper(guess[i]);
  }
  read(ans, guess, sizeof(char)*6);

  int fd = open("guess1.txt", O_WRONLY);
  char buffer[6];

  printf("Enter a five letter guess: ");
  fgets(buffer, sizeof(buffer), stdin);
  for (int i = 0; i < strlen(buffer); i++) {
    buffer[i] = toupper(buffer[i]);
  }
  printf("\n");
  /*
  - If same letter in same pos: toUpper
  - If same letter in wrong pos: set to .
      - This seems like it would need me to compare each character of buffer against each
  - If wrong letter: set to -
  */
  for (int i = 0; i < strlen(buffer); i++) {
    for (int j = 0; j < strlen(guess); j++) {
      if (buffer[i] == guess[j] && j == i) {
        buffer[i] = tolower(buffer[i]);
        break;
      }
      else if (buffer[i] == guess[j]) {
        buffer[i] = '.';
        guess[j] = ' ';
        break;
      }
    }
    if (isupper(buffer[i])) {
      buffer[i] = '-';
    }
  }

  write(fd, buffer, strlen(buffer));
  close(fd);
  }

void guess_function2(){
  int ans = open("answer2.txt", O_RDONLY);
  char guess[6];
  for (int i = 0; i < strlen(guess); i++) {
    guess[i] = toupper(guess[i]);
  }
  read(ans, guess, sizeof(char)*6);

  int fd = open("guess2.txt", O_WRONLY);
  char buffer[6];

  printf("Enter a five letter guess: ");
  fgets(buffer, sizeof(buffer), stdin);
  for (int i = 0; i < strlen(buffer); i++) {
    buffer[i] = toupper(buffer[i]);
  }
  printf("\n");
  /*
  - If same letter in same pos: toUpper
  - If same letter in wrong pos: set to .
      - This seems like it would need me to compare each character of buffer against each
  - If wrong letter: set to -
  */
  for (int i = 0; i < strlen(buffer); i++) {
    for (int j = 0; j < strlen(guess); j++) {
      if (buffer[i] == guess[j] && j == i) {
        buffer[i] = tolower(buffer[i]);
        break;
      }
      else if (buffer[i] == guess[j]) {
        buffer[i] = '.';
        guess[j] = ' ';
        break;
      }
    }
    if (isupper(buffer[i])) {
      buffer[i] = '-';
    }
  }

  write(fd, buffer, strlen(buffer));
  close(fd);
}
