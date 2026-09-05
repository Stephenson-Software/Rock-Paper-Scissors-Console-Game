#ifndef GAME_H
#define GAME_H

#include <string>
#include <cstdlib>

using namespace std;

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
