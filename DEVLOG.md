# Dev Log:

This document must be updated daily by EACH group member.

### Group ID Number is 3

## Christophe Casino

### 2024-01-06 - Added skeleton files
- Created the files that were needed for the project
- Added the includes in the header file and added the header include to all other files
- (40 min)

### 2024-01-07 - Formatted makefile and renamed files in accordance to game
- Put in all the necessary processes for the makefile that we need currently
- Renamed the files to match how the game works
- Added the main argument processor in game file for the guess and answer
- (40 min)

### 2024-01-08 - Added skeleton files
- Created the files that were needed for the project
- Added the includes in the header file and added the header include to all other files
- (40 min)

### 2024-01-09 - Changed idea of game so had to redo some stuff
- Came up with new idea for wordle game
- Deleted all unnecessary components from previous version of game
- (40 min)

### 2024-01-10 - Reconfigured project slightly and make changes accordingly
- Added args functionality for init file
- Deleted unecessary functions in wordle file
- (40 min)

### 2024-01-13 - Readjusted our initialization idea for the beginning of the game
- Discussed in great detail how the server/client relationship works and how it would be useful for our wordle game
- Removed all semaphore stuff in previous draft of the project
- (50 min)

### 2024-01-14 - Added crude functions for pipe networking
- Put in server and client functions for handshake in wordle and header file
- Added multiple argument functionality for main function in init file for Player 1 and Player 2 relating to the server and client
- (40 min)

### 2024-01-15 - Discussed how the functions should work conceptually
- Deleted unecessary variables in init file
- (20 min (spent a chunk of the period trying to fix lab 11))

### 2024-01-16 - Revised how the pipes are used for the game
- Finally fixed the server and client connection using the wordle words instead of a random number
- Created the answer and guess files for each of the players and wrote and read from them during the game
- (40 min)
- Revised handshake to be just normal and not using the answer as part of the communication
- Added the wordle game processing function but not fully done for each part of the game
- Used pipe communication as the guessing process instead of having the guesses be written to a text file
- Keeps answer word to the same server/client instead of communicating it to the other person
- (2 hours)

### 2024-01-18 - Finished base game operations
- Added ability to run game with two players simultaneously
- Fixed wordle function to allow for niche cases like letters being in the word multiple times
- (3 hours)

### 2024-01-20 - Finished
- Revised how cowsay and dragon speaking are implemented into game
- Recorded video and uploaded
- (1 hours)

## Tanzeem Hasan

### 2024-01-06 - Project Proposal
- Wrote intended usage of project proposal (30 minutes)
- Wrote topics covered and data structures used section of project proposal (10 minutes)

### 2024-01-07 - Project Proposal and Readme
- Completed project proposal details and timeline (25 minutes)
- Completed readme (5 min)

### 2024-01-08 - Work in init.c
- Creation of initial guess and answer files (15 minutes)
- Creation of semaphore and shared memory segment (15 minutes)
- Added process to remove files, shared memory, semaphore (5 minutes)
- Removed compilation errors (5 minutes)

### 2024-01-09 - Additional modifications to Proposal
- Made additional modifications to the proposal after feedback from Mr. K
- Determined what components are necessary for new wordle game
(40 mins)

### 2024-01-10 - Modified initial file Creation
- Modified creation of initial files, introduced two file structure, managed confusions (40 mins)

### 2024-01-13 - Introducing Client-Server Functionality
- Introducing idea of client-server functionality in project
- Beginning to implement client-server functionality
(40 mins)

### 2024-01-14 - Guess function work
- Wrote guess functions 1 and 2 (40 minutes)

### 2024-01-15 - Guess function work
- Cleaned up errors in compilation
- Modified guess functions
- Found new errors in compilation
(40 mins)

### 2024-01-16 - Client, server work
- Resolved segmentation fault
- Modified user input
- Verified client server handshake with words to guess
(40 mins)

### 2024-01-19 - Added Cowsay Functionality
- Added cowsay functionality for guesser (100 mins)

### 2024-01-20 - Added Cowsay Functionality
- Added cowsay dragon, knocked out cow options for guesser (30 mins)
- Added exit, quit commands for signaling (30 mins)
