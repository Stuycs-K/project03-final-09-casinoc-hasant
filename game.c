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

int main(int argc, char *argv[]){

  if(strcmp(argv[1], "guess") == 0){
    guess_function();
  } else if(strcmp(argv[1], "answer") == 0){
    answer_function();
  } else {
    printf("Error, none of the arguments are valid\n");
    return 1;
  }

  return 0;
}
