#ifndef WORDLE_H
#define WORDLE_H
#define SEMKEY 2195
#define SHMKEY 2196
int server_setup(char * player);
int server_handshake(int *to_client, char * player);
int client_handshake(int *to_server, char * player);
int * letter_counter(char * word);
char* wordle_function(char* guess, char* answer);
#endif
