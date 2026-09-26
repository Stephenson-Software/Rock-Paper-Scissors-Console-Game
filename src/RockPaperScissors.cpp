#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

#include "Game.h"

using namespace std;

// Holds the screen still for the given number of milliseconds. Output is
// flushed first so that everything printed so far is visible during the pause.
void pauseFor(int milliseconds) {
	cout << flush;
	this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

int main() {
	srand(static_cast<unsigned int>(time(NULL)));
	int pscore = 0;
	int cscore = 0;
	int ties = 0;
	while (true) {
		cout << "\n\n\n\n\n\n\n\n\n\n";
		printScoreboard(cout, pscore, cscore, ties);
		cout << "Rock, Paper, Scissors\n"
			 << "\n"
			 << "[1] Rock\n"
			 << "[2] Paper\n"
			 << "[3] Scissors\n"
			 << "[4] Quit\n"
			 << "\n"
			 << "What will you choose?\n";
		int choice = readChoice(cin);
		while (choice == CHOICE_INVALID) {
			cout << "Please enter 1, 2, 3, or 4.\n";
			choice = readChoice(cin);
		}
		if (choice == CHOICE_QUIT || choice == CHOICE_END_OF_INPUT) {
			if (choice == CHOICE_END_OF_INPUT) {
				cout << "\nNo more input to read.\n";
			}
			cout << "\nFinal score\n";
			printScoreboard(cout, pscore, cscore, ties);
			cout << "Goodbye!\n";
			return 0;
		}
		cout << "\n\n";
		string playerMove = translateChoice(choice);
		string computerMove = getMove();

		pauseFor(1000);

		for (size_t i = 3; i > 0; i--) {
			cout << i << "!\n";
			pauseFor(500);
		}
		cout << "\nShoot!\n\n";
		cout << "Player Move: " << playerMove << "\n";
		cout << "Computer Move: " << computerMove << "\n";
		
		pauseFor(2000);

		string result = decideWinner(playerMove, computerMove);
		if (result == "player") {
			cout << "You win!\n";
			pscore++;
		}
		else if (result == "computer") {
			cout << "The computer won!\n";
			cscore++;
		}
		else {
			cout << "It was a tie!\n";
			ties++;
		}
		pauseFor(4000);
	}
}