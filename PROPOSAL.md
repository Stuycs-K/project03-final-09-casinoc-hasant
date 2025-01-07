# Final Project Proposal

## Group Members:

Christopher Casino and Tanzeem Hasan

# Intentions:

The purpose of this program is to replicate the game wordle.

# Intended usage:

The player attempts to guess the target word within six attempts. The program will return a modified version of the player's string. If a letter is correct and is in the right position, it will be unmodified. If a letter is correct and in the wrong position, it will be replaced with a ".". If a letter is incorrect it will be replaced with a "-". If the user guesses the word correctly, the game ends.

# Technical Details:

Topics covered:
- Allocating memory
- Working with files
- Signals
- Shared memory
- Semaphores
By using shared memory and semaphores, we can have a two player wordle game. One player will create the word, which will be written to a text file. The program will read from a text file every time that the second player makes a guess and store the characters of the word in a character array. The program will read the user's input into a separate character array. If a character from the user's input is present in the array corresponding to the text file, the program will set the character in the text array to null. The program will return a modified string to the second player after each guess. If the user guesses correctly, a signal will be output to end the program.

How you are breaking down the project and who is responsible for which parts.
1. Semaphores and memory segments (make initialize)
2. File access and allocating memory (make answer, make guess)
3. Returning signals
We will be working on these steps from the perspective of a guesser and an answerer. Tanzeem will write from the perspective of the guesser, and Christopher from the perspective of the answerer.

We'll use semaphores to manage access to the game for two players. Semaphores require the union and sembuf structures to function. To manage user input and output, we will store guesses and the target in an array.


# Intended pacing:
By January 7 we intend to have a fully fleshed out concept.
By the end of January 10, we intend to have a working semaphores and shared memory segments.
By the end of January 17, we expect to have completed the make answer and make guess functionalities of the project.
Over the weekend, we would work on a video presentation.
