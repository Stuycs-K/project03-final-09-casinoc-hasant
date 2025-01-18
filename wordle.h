#ifndef WORDLE_H
#define WORDLE_H
#define SEMKEY 2195
#define SHMKEY 2196
int server_setup();
char* wordle_function(char* guess, char* answer);
#endif
