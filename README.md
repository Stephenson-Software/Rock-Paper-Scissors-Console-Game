# Rock Paper Scissors Console Game
This application allows the user to play Rock Paper Scissors against the computer. 

## Requirements

- `make`
- A C++ toolchain. The `Makefile` invokes `gcc` and links against `-lstdc++`, so
  a `gcc` installation that includes the C++ standard library is what is needed.

## Building

Run `make` from the root of the repository:

```
make
```

The compiled program is written to `RockPaperScissors` in the repository root:

```
$ make
---
Compiling RockPaperScissors
gcc src/RockPaperScissors.cpp -lstdc++ -o RockPaperScissors
Finished compiling RockPaperScissors.cpp
```

There is no `clean` target; the binary is removed by deleting it directly.

## Running

```
./RockPaperScissors
```

Note that `src/RockPaperScissors` is a separate, checked-in binary that is not
produced by the build. The program to run is the one in the repository root.

## How to Play

The running score is shown at the top of each round, followed by the menu:

```
Player: 0
Computer: 0
Ties: 0

Rock, Paper, Scissors

[1] Rock
[2] Paper
[3] Scissors

What will you choose?
```

Enter `1`, `2`, or `3` and press Enter. A countdown is printed, both moves are
revealed, and the winner of the round is announced:

```
3!
2!
1!

Shoot!

Player Move: rock
Computer Move: paper
The computer won!
```

The score is then updated and the next round begins. Rock beats scissors, paper
beats rock, and scissors beats paper; matching moves are counted as a tie.

## Quitting

The game has no quit option and loops until the process is stopped, so Ctrl+C is
what ends a session.
