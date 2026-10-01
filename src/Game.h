#ifndef GAME_H
#define GAME_H

#include <string>
#include <cstdlib>
#include <istream>
#include <ostream>
#include <sstream>

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
// nothing left to read. Each entry is one whole line, and it is accepted only
// when the entire line (ignoring surrounding whitespace) is the number, so an
// entry such as "1abc" or "1 2" is rejected rather than being played with its
// remainder left over for the next round. The number must be a single digit,
// so a signed or zero-padded entry such as "+3" or "03" is rejected too.
// Blank lines are skipped.
inline int readChoice(istream& in) {
	string line;
	while (getline(in, line)) {
		istringstream entry(line);
		entry >> ws;
		if (entry.eof()) {
			continue;
		}
		string token;
		entry >> token;
		entry >> ws;
		if (!entry.eof() || token.size() != 1) {
			return CHOICE_INVALID;
		}
		int choice = token[0] - '0';
		if (!isValidChoice(choice)) {
			return CHOICE_INVALID;
		}
		return choice;
	}
	return CHOICE_END_OF_INPUT;
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
