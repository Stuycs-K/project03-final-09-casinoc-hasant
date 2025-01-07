# Final Project Proposal

## Group Members:

Christopher Casino and Tanzeem Hasan

# Intentions:

A statement of the problem you are solving and/or a high level description of the project.

# Intended usage:

The player attempts to guess the target word within six attempts. The program will return a modified version of the player's string. If a letter is correct and is in the right position, it will be unmodified. If a letter is correct and in the wrong position, it will be replaced with a ".". If a letter is incorrect it will be replaced with a "-". If the user guesses the word correctly, the game ends.

# Technical Details:

A description of your technical design. This should include:

How you will be using the topics covered in class in the project.
Topics covered:
- Allocating memory
- Working with files
- Signals
- Shared memory
- Semaphores
By using shared memory and semaphores, we can have a two player wordle game. One player will create the word, which will be written to a text file. The program will read from a text file every time that the second player makes a guess and store the characters of the word in a character array. The program will read the user's input into a separate character array. If a character from the user's input is present in the array corresponding to the text file, the program will set the character in the text array to null. The program will return a modified string to the second player after each guess. If the user guesses correctly, a signal will be output to end the program.

How you are breaking down the project and who is responsible for which parts.



What data structures you will be using and how.

We'll use semaphores to manage access to the game for two players. Semaphores require the union and sembuf structures to function.

What algorithms and /or data structures you will be using, and how.

# Intended pacing:

A timeline with expected completion dates of parts of the project.
