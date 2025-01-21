[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Vh67aNdh)
# PROJECT NAME HERE

WordleIncorporated

### GROUP NAME HERE
CowsRUs

### Group Members

Christophe Casino and Tanzeem Hasan

### Project Description:

The player attempts to guess the target word within six attempts. The program will return a modified version of the player's string. If a letter is correct and is in the right position, it will be unmodified. If a letter is correct and in the wrong position, it will be replaced with a ".". If a letter is incorrect it will be replaced with a "-". If the user guesses the word correctly, the game ends.

### Video Link:

https://drive.google.com/file/d/1wOlUFhtTciZ_0tnm-FfhI31k9NXAOkus/view?usp=sharing


### Instructions:

How does the user install/compile/run the program.
First run "make compile". Each player should run the answer and guess commands with make init. So player 1 will run "make init ARGS="Answer Player1"" followed by "make init ARGS="Guess Player1". Player2 will run "make init ARGS="Answer Player2"" followed by "make init ARGS="Guess Player2". 
Four terminals are required for both players to play simultaneously. A player can only send the word to another player if that other player has opened their guess terminal. If a player has typed "exit" or "quit" on their guess terminal, their game will be terminated early. 
If the user does not have cowsay installed, the hints will not be displayed. If cowsay is not installed, you can run "sudo apt install cowsay" to try to obtain the relevant function.
