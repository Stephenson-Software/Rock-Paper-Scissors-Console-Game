#include <iostream>
#include <string>
#include <cstdlib>

#include "Game.h"

using namespace std;

int main() {
	int pscore = 0;
	int cscore = 0;
	int ties = 0;
	while (true) {
		cout << "\n\n\n\n\n\n\n\n\n\n";
		cout << "Player: " << pscore << "\n" 
			 << "Computer: " << cscore << "\n"
			 << "Ties: " << ties << "\n\n";
		cout << "Rock, Paper, Scissors\n"
			 << "\n"
			 << "[1] Rock\n"
			 << "[2] Paper\n"
			 << "[3] Scissors\n"
			 << "\n"
			 << "What will you choose?\n";
		int choice;
		cin >> choice;
		cout << "\n\n";
		string playerMove = translateChoice(choice);
		string computerMove = getMove();

		// TODO: sleep for 1 second

		for (size_t i = 3; i > 0; i--) {
			cout << i << "!\n";
			// TODO: sleep for half a second
		}
		cout << "\nShoot!\n\n";
		cout << "Player Move: " << playerMove << "\n";
		cout << "Computer Move: " << computerMove << "\n";
		
		// TODO: sleep for 2 seconds

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
		// TODO: sleep for 4 seconds
	}
}