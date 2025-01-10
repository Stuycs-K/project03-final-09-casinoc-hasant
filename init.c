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

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO */
};                         /* (Linux-specific) */

int main(int argc, char *argv[]) {
  int semd;
  int shmd;
  semctl(semd, 0, IPC_RMID); // Clean up semaphore
  shmctl(shmd, IPC_RMID, NULL); // Clean up shared memory
  int *data;


  //semaphore and shared memory
  semd = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  if (semd == -1) {
    perror("Could not open semaphore");
    exit(1);
  }
  union semun us;
  us.val = 2;
  if (semctl(semd, 0, SETVAL, us) == -1) { //Set semaphore value
    perror("Error setting semaphore value");
    semctl(semd, 0, IPC_RMID); //Clean up semaphore
    exit(1);
  }
  shmd = shmget(SHMKEY, sizeof(int), IPC_CREAT | 0600); //Set shared memory
  if (shmd == -1) {
    perror("Error creating shared memory");
    semctl(semd, 0, IPC_RMID); //Clean up semaphore
    exit(1);
  }
  data = shmat(shmd, 0, 0); //Attach shared memory to variable
  if (data == (void *)-1) {
    perror("Error attaching shared memory");
    semctl(semd, 0, IPC_RMID); // Clean up semaphore
    shmctl(shmd, IPC_RMID, NULL); // Clean up shared memory
    exit(1);
  }
  *data = 0;

  //create initial files
  char * a = malloc(sizeof(char)*12);
  char * g = malloc(sizeof(char)*11);
  if (strcmp(argv[1], "1") == 0) {
    a = "answer1.txt";
    g = "guess2.txt";
  }
  else if (strcmp(argv[1], "2") == 0) {
    a = "answer2.txt";
    g = "guess2.txt";
  }
  else {
    perror("No argument");
    exit(1);
  }
  char input[6];
  printf("Give a five letter word to initialize the game: ");
  fgets(input, sizeof(input), stdin);
  int answer = open(a, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  write(answer, input, strlen(input)); //write the word to answer file
  close(answer);
  int guess = open(g, O_CREAT | O_TRUNC, 0644); //create empty guess file
  close(guess);

  /*
  So we want both players to run make init and then play, or what?
  When one player runs make init, they write to a file, and wait for a second
  file to appear. Then, are two make inits required? Like make init player1,
  make init player2? Or does it only matter what device the make init is
  being cast from?
  Select is used to read from different sources. What is fd_set? File descriptor
  select?
  While player2 has not received a return value from player1, they cannot
  continue. Once received, the program continues automatically. This sounds
  like lab 14. Try pipes?
  How do you differentiate between player1 and player2 if they run the same command?

  */



























  shmdt(data);
  return 0;
}
