[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Vh67aNdh)
# PROJECT NAME HERE

WordleInC

### GROUP NAME HERE

Christopher Casino and Tanzeem Hasan

### Project Description:

The player attempts to guess the target word within six attempts. The program will return a modified version of the player's string. If a letter is correct and is in the right position, it will be unmodified. If a letter is correct and in the wrong position, it will be replaced with a ".". If a letter is incorrect it will be replaced with a "-". If the user guesses the word correctly, the game ends.

### Instructions:

How does the user install/compile/run the program.
The person who gives hints and first makes the word will use "make init" to initialize the program.

How does the user interact with this program?
The guesser will use "make game ARGS="guess"" to make guesses. The hinter will use "make game ARGS="answer"" to provide hints. Each user will follow after the other, up to a maximum of 6 guesses.
