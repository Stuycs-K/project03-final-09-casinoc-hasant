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

void guess_function1(){
  int ans = open("answer1.txt", O_RDONLY);
  char guess[6];
  read(ans, guess, sizeof(char)*6);

  int fd = open("guess1.txt", O_WRONLY);
  char buffer[6];

  printf("Enter a five letter guess: ");
  fgets(buffer, sizeof(buffer), stdin);
  printf("\n");

  for (int i = 0; i < strlen(buffer); i++) {
    if (buffer[i] != guess[i]){
      //2 cases: 1 where it is in wrong location and other where it is not present
      
    }
    else {
      //no change
    }
  }
  write(fd, buffer, strlen(buffer));
  close(fd);


}
void guess_function2(){
  open("guess2.txt", O_WRONLY);

}
