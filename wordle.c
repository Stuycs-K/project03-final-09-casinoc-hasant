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
  open("guess1.txt", O_WRONLY);

}
void guess_function2(){
  open("guess2.txt", O_WRONLY);

}
