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

char answer1[5];
char answer2[5];

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

  // Send ack to server on WKP with pid+1.
  int change_num;
  sscanf(syn_ack, "%d", &change_num);
  change_num++;
  char ack[100];
  sprintf(ack, "%d", change_num);
  write(fd, ack, sizeof(ack));

  *to_server = fd;
  from_server = df;
  return from_server;
}

int * letter_counter(char * word){
  int* counter = (int*)malloc(26 * sizeof(int));
  for(int i = 0; i < 5; i++){
    word[i] = toupper(word[i]);
  }
  for(int i = 0; i < 5; i++){
    counter[word[i]-65]++;
  }
  return counter;
}

char* wordle_function(char* guess, char* answer){
  char* result = (char*)malloc(5 * sizeof(char));
  int* counter = (int*)malloc(26 * sizeof(int));
  counter = letter_counter(answer);
  for(int i = 0; i < 5; i++){
    guess[i] = toupper(guess[i]);
  }
  for(int i = 0; i < 5; i++){
    answer[i] = toupper(answer[i]);
  }
  for(int i = 0; i < 5; i++){
    result[i] = '-';
  }

  // Check if letter is in the correct place.
  for(int i = 0; i < 5; i++){
    if(answer[i] == guess[i]){
      result[i] = toupper(guess[i]);
      counter[guess[i] - 65]--;
    }
  }

  // Check if letter is present in answer but is not in the right place.
  for(int i = 0; i < 5; i++){
    if((counter[guess[i] - 65] > 0) && (result[i] == '-') && (strchr(answer, guess[i]) != NULL)){
      result[i] = tolower(guess[i]);
      counter[guess[i] - 65]--;
    }
  }
  
  return result;
}
