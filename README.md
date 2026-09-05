# Rock Paper Scissors Console Game
This application allows the user to play Rock Paper Scissors against the computer. 

## Requirements

- `make`
- A C++ toolchain. The `Makefile` invokes `g++`, so a GCC installation that
  includes the C++ compiler driver is what is needed.

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
g++ src/RockPaperScissors.cpp -o RockPaperScissors
Finished compiling RockPaperScissors.cpp
```

The build output is removed with `make clean`:

```
$ make clean
---
Removing build output
rm -f RockPaperScissors GameTest
Finished removing build output
```

## Running

```
./RockPaperScissors
```

## Testing

The game's rules live in `src/Game.h` so that they can be linked into a test
binary as well as into the game. `make test` compiles and runs that binary:

```
$ make test
---
Compiling GameTest
g++ src/GameTest.cpp -o GameTest
Finished compiling GameTest.cpp
---
Running GameTest
./GameTest
All GameTest assertions passed.
Finished running GameTest
```

The assertions live in `src/GameTest.cpp` and use `<cassert>`; no third-party
test framework is required. A failing assertion aborts the binary, which fails
the `make test` target with a non-zero exit status.

These are **characterization** tests: they record what the game does today
rather than what it ought to do. `translateChoice` returns `"scissors"` for
every integer outside `1` and `2`, and the suite asserts exactly that, so a
future fix to out-of-range input has to update the assertion deliberately.

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
