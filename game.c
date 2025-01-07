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