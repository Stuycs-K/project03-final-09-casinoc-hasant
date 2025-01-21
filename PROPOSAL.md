# Final Project Proposal

## Group Members:

Christophe Casino and Tanzeem Hasan

# Intentions:

The purpose of this program is to create a two player wordle game.

# Intended usage:
Each player should run the answer and guess commands with make init. So player 1 will run "make init ARGS="Answer Player1"" followed by "make init ARGS="Guess Player1". Player2 will run "make init ARGS="Answer Player2"" followed by "make init ARGS="Guess Player2". Four terminals are required for both players to play simultaneously. A player can only send the word to another player if that other player has opened their guess terminal. If a player has typed "exit" or "quit" on their guess terminal, their game will be terminated early. 

Both players will send each other a word. Each player plays simultaneously. Each player attempts to guess the target word within six attempts. The program will return a modified version of the player's string. If a letter is correct and is in the right position, it will be capitalized. If a letter is correct and in the wrong position, it will be unmodified. If a letter is incorrect it will be replaced with a "-". If a player guesses the word correctly, the game ends, and they will be told how many guesses they succeeded within. Each guess that a player makes will be sent to the other player's answer terminal.

# Technical Details:

Topics covered:
- Allocating memory
- Signals
- Processes
- Pipes
We will be implementing a client-server design, with the answer terminal functioning as the server and the guess terminal functioning as the client.
The server will be waiting for a client to connect. Upon connecting, the answer giver will be asked for a five letter word. That five letter word will be sent through the pipe to the client, the guesser. Every time the client makes a guess, it will be shown to the answer giver through a pipe. Additionally, the client will fork to create a child process, allowing it to run cowsay with execvp. The cowsay message will contain the modified string, which previously had memory allocated to contain it. Should a player decide they want to quit the game early, they can type "exit" or "quit" to send a SIGINT to both the server and client in a pair, ending that specific game. As two games would be run at the same time, ending one game will not affect the other.

How you are breaking down the project and who is responsible for which parts.
1. Signals and Processes (Tanzeem Hasan)
2. Client-Server Implementation (Christophe Casino)
3. Wordle Function (Both)



# Intended pacing:
By January 7 we intend to have a fully fleshed out concept.
By the end of January 10, we intend to have a working wordle function.
By the end of January 17, we expect to have the pipes section of our project.
Over the weekend, we would work on a video presentation.
