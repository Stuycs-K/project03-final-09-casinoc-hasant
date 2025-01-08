#include "wordle.h"

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO */
};                         /* (Linux-specific) */

int main() {
  int semd;
  int shmd;
  semctl(semd, 0, IPC_RMID); // Clean up semaphore
  shmctl(shmd, IPC_RMID, NULL); // Clean up shared memory
  int *data;

  //create initial files
  char input[6];
  printf("Give a five letter word to initialize the game: ");
  fgets(input, sizeof(input), stdin);
  int answer = open("answer.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  write(answer, input, strlen(input)); //write the word to answer file
  close(answer);
  int guess = open("guess.txt", O_CREAT | O_TRUNC, 0644); //create empty guess file
  close(guess);

  //semaphore and shared memory
  semd = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  if (semd == -1) {
    perror("Could not open semaphore");
    exit(1);
  }
  union semun us;
  us.val = 1;
  if (semctl(semd, 0, SETVAL, us) == -1) { //Set semaphore value
    perror("Error setting semaphore value");
    semctl(semd, 0, IPC_RMID); //Clean up semaphore
    exit(1);
  }
  shmd = shmget(KEY, sizeof(int), IPC_CREAT, 0600);
  if (shmd == -1) {
    perror("Error creating shared memory");
    semctl(semd, 0, IPC_RMID); //Clean up semaphore
    exit(1);
  }
  data = shmat(shmd, 0, 0);
  if (data == (void *)-1) {
    perror("Error attaching shared memory");
    semctl(semd, 0, IPC_RMID); // Clean up semaphore
    shmctl(shmd, IPC_RMID, NULL); // Clean up shared memory
    exit(1);
  }
  *data = 0;
  shmdt(data);
  return 0l
}
