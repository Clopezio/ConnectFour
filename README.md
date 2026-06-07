# Connect Four

A Connect Four game implementation written in C for a school project.

## Overview

This is a classic Connect Four game built entirely in C, featuring a command-line interface where two players take turns dropping pieces into a grid, aiming to connect four pieces in a row (horizontally, vertically, or diagonally).

## Getting Started

### Prerequisites

- A C compiler (gcc, clang, or similar)
- Make (optional, if a Makefile is included)

### Building

To compile the project:

```bash
gcc -o connect_four *.c
```

Or if a Makefile is available:

```bash
make
```

### Running

Execute the compiled program:

```bash
./connect_four
```

Follow the on-screen prompts to play the game.

## How to Play

1. Two players alternate turns
2. Each player drops a piece into one of the columns
3. The piece falls to the lowest available row
4. First player to connect four pieces in a row wins
5. The game ends in a draw if the board fills up

## Project Structure

- Game logic and board management
- Player input handling
- Win condition detection
- Command-line interface

## License

This project was created for educational purposes.
