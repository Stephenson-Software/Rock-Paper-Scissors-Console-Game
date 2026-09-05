#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>

#include "Game.h"

using namespace std;

// Characterization tests. These assert what the game does today, not what it
// ought to do. translateChoice_outOfRangeIsScissors in particular locks in a
// known bug so that changing it is a deliberate, visible act.

#ifdef NDEBUG
#error "GameTest must be compiled with assertions enabled (NDEBUG must not be defined)."
#endif

void translateChoice_oneIsRock() {
	assert(translateChoice(1) == "rock");
}

void translateChoice_twoIsPaper() {
	assert(translateChoice(2) == "paper");
}

void translateChoice_threeIsScissors() {
	assert(translateChoice(3) == "scissors");
}

void translateChoice_outOfRangeIsScissors() {
	// Documents current behavior, not desired behavior: every integer outside
	// 1 and 2 falls through to scissors, including the value cin leaves behind
	// after a failed extraction.
	assert(translateChoice(0) == "scissors");
	assert(translateChoice(4) == "scissors");
	assert(translateChoice(99) == "scissors");
	assert(translateChoice(-1) == "scissors");
}

// Named <playerMove>Vs<computerMove>_<outcome>, since several pairs share a
// rule ("paper beats rock") and differ only in which side played which move.

void decideWinner_rockVsRock_isTie() {
	assert(decideWinner("rock", "rock") == "tie");
}

void decideWinner_rockVsPaper_computerWins() {
	assert(decideWinner("rock", "paper") == "computer");
}

void decideWinner_rockVsScissors_playerWins() {
	assert(decideWinner("rock", "scissors") == "player");
}

void decideWinner_paperVsRock_playerWins() {
	assert(decideWinner("paper", "rock") == "player");
}

void decideWinner_paperVsPaper_isTie() {
	assert(decideWinner("paper", "paper") == "tie");
}

void decideWinner_paperVsScissors_computerWins() {
	assert(decideWinner("paper", "scissors") == "computer");
}

void decideWinner_scissorsVsRock_computerWins() {
	assert(decideWinner("scissors", "rock") == "computer");
}

void decideWinner_scissorsVsPaper_playerWins() {
	assert(decideWinner("scissors", "paper") == "player");
}

void decideWinner_scissorsVsScissors_isTie() {
	assert(decideWinner("scissors", "scissors") == "tie");
}

void getMove_alwaysReturnsAKnownMove() {
	// getMove draws from rand(), so the specific move is not asserted — only
	// that every draw is one the rest of the game knows how to score.
	for (size_t i = 0; i < 1000; i++) {
		string move = getMove();
		assert(move == "rock" || move == "paper" || move == "scissors");
	}
}

int main() {
	translateChoice_oneIsRock();
	translateChoice_twoIsPaper();
	translateChoice_threeIsScissors();
	translateChoice_outOfRangeIsScissors();

	decideWinner_rockVsRock_isTie();
	decideWinner_rockVsPaper_computerWins();
	decideWinner_rockVsScissors_playerWins();
	decideWinner_paperVsRock_playerWins();
	decideWinner_paperVsPaper_isTie();
	decideWinner_paperVsScissors_computerWins();
	decideWinner_scissorsVsRock_computerWins();
	decideWinner_scissorsVsPaper_playerWins();
	decideWinner_scissorsVsScissors_isTie();

	getMove_alwaysReturnsAKnownMove();

	cout << "All GameTest assertions passed.\n";
	return 0;
}
