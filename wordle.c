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

void guess_function(){
  FILE *fd;
  int *data;
  int semd;
  int shmd;
}

void answer_function(){
  struct sembuf sb;
  FILE *fd;
  int semd;
  int shmd;
  int *bytes_wrote;
  int bytes_writing;
  int seeking;
  char input[200];
  char last_line[200];

  printf("Waiting for Guesser to make a guess...\n");
  semd = semget(SEMKEY, 1, 0);
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;
  semop(semd, &sb, 1);
  shmd = shmget(SHMKEY, 0, 0);
  bytes_wrote = shmat(shmd, 0, 0);
}
