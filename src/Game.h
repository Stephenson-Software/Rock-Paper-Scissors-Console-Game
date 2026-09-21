#ifndef GAME_H
#define GAME_H

#include <string>
#include <cstdlib>
#include <istream>
#include <ostream>
#include <limits>

using namespace std;

// The menu's quit entry. It sits after the three moves so that 1, 2 and 3
// still map straight onto translateChoice.
const int CHOICE_QUIT = 4;

// Sentinel results from readChoice. A valid selection is 1 through 4, so both
// sentinels sit outside that range.
const int CHOICE_INVALID = 0;
const int CHOICE_END_OF_INPUT = -1;

inline bool isValidChoice(int i) {
	return i >= 1 && i <= CHOICE_QUIT;
}

// Reads one menu selection. Returns 1, 2 or 3 for a move the menu offers,
// CHOICE_QUIT for the quit entry, CHOICE_INVALID when the entry should be
// rejected and the prompt repeated, or CHOICE_END_OF_INPUT when the stream has
// nothing left to read. A malformed entry is discarded up to the end of its
// line so the next read starts clean, which is what keeps a failed extraction
// from being retried forever.
inline int readChoice(istream& in) {
	int choice = 0;
	in >> choice;
	if (in.fail()) {
		if (in.eof()) {
			return CHOICE_END_OF_INPUT;
		}
		in.clear();
		in.ignore(numeric_limits<streamsize>::max(), '\n');
		return CHOICE_INVALID;
	}
	if (!isValidChoice(choice)) {
		return CHOICE_INVALID;
	}
	return choice;
}

// Prints the running score in the layout the top of every round uses. The
// same layout is printed as the final score on the way out, so the two can
// never drift apart.
inline void printScoreboard(ostream& out, int pscore, int cscore, int ties) {
	out << "Player: " << pscore << "\n"
		<< "Computer: " << cscore << "\n"
		<< "Ties: " << ties << "\n\n";
}

inline string translateChoice(int i) {
	if (i == 1) {
		return "rock";
	} else if (i == 2) {
		return "paper";
	} else {
		return "scissors";
	}
}

inline string getMove() {
	return translateChoice(rand() % 3 + 1);
}

inline string decideWinner(string p, string c) {
	if (p == "rock" && c == "paper") {
		return "computer";
	}
	else if (p == "rock" && c == "scissors") {
		return "player";
	}
	else if (p == "paper" && c == "rock") {
		return "player";
	}
	else if (p == "paper" && c == "scissors") {
		return "computer";
	}
	else if (p == "scissors" && c == "rock") {
		return "computer";
	}
	else if (p == "scissors" && c == "paper") {
		return "player";
	}
	else {
		return "tie";
	}
}

#endif
