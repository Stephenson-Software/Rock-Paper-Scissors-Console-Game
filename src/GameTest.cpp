#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <cstdlib>

#include "Game.h"

using namespace std;

// Characterization tests. These assert what the game does today, not what it
// ought to do. translateChoice_outOfRangeIsScissors in particular locks in the
// fallback for integers that are not one of the three moves so that changing
// it is a deliberate, visible act.

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
	// Every integer outside 1 and 2 falls through to scissors, not just 3. No
	// caller passes anything but 1, 2 or 3 today — readChoice rejects other
	// entries and getMove only draws 1 through 3 — but translateChoice stays
	// total so that a future caller cannot trip undefined behavior.
	assert(translateChoice(0) == "scissors");
	assert(translateChoice(4) == "scissors");
	assert(translateChoice(99) == "scissors");
	assert(translateChoice(-1) == "scissors");
}

void isValidChoice_acceptsTheFourMenuNumbers() {
	assert(isValidChoice(1));
	assert(isValidChoice(2));
	assert(isValidChoice(3));
	assert(isValidChoice(4));
}

void isValidChoice_rejectsEverythingElse() {
	assert(!isValidChoice(0));
	assert(!isValidChoice(5));
	assert(!isValidChoice(99));
	assert(!isValidChoice(-1));
}

void choiceSentinels_areDistinctAndNeverAValidChoice() {
	// main re-prompts while readChoice returns CHOICE_INVALID and exits on
	// CHOICE_END_OF_INPUT. Were the two equal, running out of input would
	// re-prompt forever; were either a valid choice, it would be played or
	// taken as Quit.
	assert(CHOICE_INVALID != CHOICE_END_OF_INPUT);
	assert(!isValidChoice(CHOICE_INVALID));
	assert(!isValidChoice(CHOICE_END_OF_INPUT));
	assert(isValidChoice(CHOICE_QUIT));
}

void readChoice_returnsTheMenuNumberEntered() {
	istringstream in("1\n2\n3\n");
	assert(readChoice(in) == 1);
	assert(readChoice(in) == 2);
	assert(readChoice(in) == 3);
}

void readChoice_returnsQuitForTheQuitEntry() {
	// 4 is the menu's quit entry, so it must come back as CHOICE_QUIT rather
	// than being rejected — and CHOICE_QUIT must not collide with a move.
	istringstream in("4\n");
	assert(readChoice(in) == CHOICE_QUIT);
	assert(CHOICE_QUIT != 1 && CHOICE_QUIT != 2 && CHOICE_QUIT != 3);
}

void readChoice_rejectsOutOfRangeNumbers() {
	// Before validation existed these were played as scissors, silently.
	istringstream in("0\n5\n99\n-1\n");
	assert(readChoice(in) == CHOICE_INVALID);
	assert(readChoice(in) == CHOICE_INVALID);
	assert(readChoice(in) == CHOICE_INVALID);
	assert(readChoice(in) == CHOICE_INVALID);
}

void readChoice_rejectsNonNumericInputAndDiscardsIt() {
	// The second read is what proves the rejected entry was discarded: were it
	// left in the stream, the read would fail forever on the same "abc".
	istringstream in("abc\n2\n");
	assert(readChoice(in) == CHOICE_INVALID);
	assert(readChoice(in) == 2);
}

void readChoice_rejectsANumberFollowedByOtherCharacters() {
	// Each entry is rejected once, at its own read, and nothing it contained
	// carries over: the read after it returns the next line's entry.
	istringstream in("1abc\n3\n2.5\n3\n1 2\n3\n");
	assert(readChoice(in) == CHOICE_INVALID);
	assert(readChoice(in) == 3);
	assert(readChoice(in) == CHOICE_INVALID);
	assert(readChoice(in) == 3);
	assert(readChoice(in) == CHOICE_INVALID);
	assert(readChoice(in) == 3);
	assert(readChoice(in) == CHOICE_END_OF_INPUT);
}

void readChoice_rejectsSignedAndZeroPaddedNumbers() {
	// Integer extraction parses each of these as a number, and all but "-0"
	// land on a menu number; only a single digit is a menu entry.
	istringstream in("+3\n03\n-0\n+1\n001\n2\n");
	assert(readChoice(in) == CHOICE_INVALID);
	assert(readChoice(in) == CHOICE_INVALID);
	assert(readChoice(in) == CHOICE_INVALID);
	assert(readChoice(in) == CHOICE_INVALID);
	assert(readChoice(in) == CHOICE_INVALID);
	assert(readChoice(in) == 2);
}

void readChoice_rejectsASingleNonDigitCharacter() {
	// A one-character entry is converted by subtracting '0', so a character
	// just below '0' lands on a negative number: "/" on -1, which is
	// CHOICE_END_OF_INPUT, and "." on -2. Only the range check stops "/" from
	// ending the game as though the input had run out.
	istringstream in("/\n.\na\n:\n2\n");
	assert(readChoice(in) == CHOICE_INVALID);
	assert(readChoice(in) == CHOICE_INVALID);
	assert(readChoice(in) == CHOICE_INVALID);
	assert(readChoice(in) == CHOICE_INVALID);
	assert(readChoice(in) == 2);
}

void readChoice_acceptsANumberWithSurroundingWhitespace() {
	istringstream in(" 3 \n\t2\t\n");
	assert(readChoice(in) == 3);
	assert(readChoice(in) == 2);
}

void readChoice_acceptsWindowsLineEndings() {
	// getline leaves the "\r" of a "\r\n" ending on the line. It counts as
	// trailing whitespace, so input typed or piped on Windows reads the same,
	// a "\r"-only line is a blank line, and a malformed entry is still rejected.
	istringstream in("1\r\n\r\n4\r\n1abc\r\n2\r\n");
	assert(readChoice(in) == 1);
	assert(readChoice(in) == CHOICE_QUIT);
	assert(readChoice(in) == CHOICE_INVALID);
	assert(readChoice(in) == 2);
	assert(readChoice(in) == CHOICE_END_OF_INPUT);
}

void readChoice_skipsBlankLines() {
	istringstream in("\n   \n\t\n1\n\n");
	assert(readChoice(in) == 1);
	assert(readChoice(in) == CHOICE_END_OF_INPUT);
}

void readChoice_acceptsAFinalEntryWithNoNewline() {
	istringstream in("2");
	assert(readChoice(in) == 2);
	assert(readChoice(in) == CHOICE_END_OF_INPUT);
}

void readChoice_reportsEndOfInput() {
	istringstream empty("");
	assert(readChoice(empty) == CHOICE_END_OF_INPUT);

	istringstream consumed("1\n");
	assert(readChoice(consumed) == 1);
	assert(readChoice(consumed) == CHOICE_END_OF_INPUT);
}

void readChoice_reportsEndOfInputAfterUnparseableTrailingInput() {
	// "abc" with no newline after it is rejected like any other malformed
	// entry; discarding it is what exhausts the stream, so the read after it
	// is the one that reports end of input.
	istringstream in("abc");
	assert(readChoice(in) == CHOICE_INVALID);
	assert(readChoice(in) == CHOICE_END_OF_INPUT);
}

void printScoreboard_printsEachCounterOnItsOwnLine() {
	ostringstream out;
	printScoreboard(out, 3, 1, 2);
	assert(out.str() == "Player: 3\nComputer: 1\nTies: 2\n\n");
}

void printScoreboard_printsZerosForANewGame() {
	ostringstream out;
	printScoreboard(out, 0, 0, 0);
	assert(out.str() == "Player: 0\nComputer: 0\nTies: 0\n\n");
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

void decideWinner_unrecognizedMove_isTie() {
	// Only translateChoice's three names are ever passed in, but any pair that
	// is not one of the six winning pairs falls through to a tie.
	assert(decideWinner("lizard", "rock") == "tie");
	assert(decideWinner("rock", "") == "tie");
	assert(decideWinner("Rock", "scissors") == "tie");
}

// Each counter starts at a different value so that crediting the wrong side
// cannot go unnoticed.

void recordResult_playerWin_creditsThePlayer() {
	int pscore = 5;
	int cscore = 7;
	int ties = 9;
	assert(recordResult("player", pscore, cscore, ties) == "You win!");
	assert(pscore == 6 && cscore == 7 && ties == 9);
}

void recordResult_computerWin_creditsTheComputer() {
	int pscore = 5;
	int cscore = 7;
	int ties = 9;
	assert(recordResult("computer", pscore, cscore, ties) == "The computer won!");
	assert(pscore == 5 && cscore == 8 && ties == 9);
}

void recordResult_tie_countsATie() {
	int pscore = 5;
	int cscore = 7;
	int ties = 9;
	assert(recordResult("tie", pscore, cscore, ties) == "It was a tie!");
	assert(pscore == 5 && cscore == 7 && ties == 10);
}

void recordResult_unknownResult_countsATie() {
	// decideWinner only returns "player", "computer" or "tie", but anything
	// else falls through to the tie branch, as it did when this lived in main.
	int pscore = 5;
	int cscore = 7;
	int ties = 9;
	assert(recordResult("", pscore, cscore, ties) == "It was a tie!");
	assert(pscore == 5 && cscore == 7 && ties == 10);
}

void getMove_alwaysReturnsAKnownMove() {
	// getMove draws from rand(), so the specific move is not asserted — only
	// that every draw is one the rest of the game knows how to score.
	for (size_t i = 0; i < 1000; i++) {
		string move = getMove();
		assert(move == "rock" || move == "paper" || move == "scissors");
	}
}

void getMove_drawsEveryMove() {
	// A fixed seed keeps this deterministic. Over 1000 draws each move should
	// turn up many times; one that never does means the computer can no longer
	// play it, which getMove_alwaysReturnsAKnownMove alone would not notice.
	srand(1);
	bool sawRock = false;
	bool sawPaper = false;
	bool sawScissors = false;
	for (size_t i = 0; i < 1000; i++) {
		string move = getMove();
		if (move == "rock") {
			sawRock = true;
		} else if (move == "paper") {
			sawPaper = true;
		} else if (move == "scissors") {
			sawScissors = true;
		}
	}
	assert(sawRock);
	assert(sawPaper);
	assert(sawScissors);
}

int main() {
	translateChoice_oneIsRock();
	translateChoice_twoIsPaper();
	translateChoice_threeIsScissors();
	translateChoice_outOfRangeIsScissors();

	isValidChoice_acceptsTheFourMenuNumbers();
	isValidChoice_rejectsEverythingElse();
	choiceSentinels_areDistinctAndNeverAValidChoice();
	readChoice_returnsTheMenuNumberEntered();
	readChoice_returnsQuitForTheQuitEntry();
	readChoice_rejectsOutOfRangeNumbers();
	readChoice_rejectsNonNumericInputAndDiscardsIt();
	readChoice_rejectsANumberFollowedByOtherCharacters();
	readChoice_rejectsSignedAndZeroPaddedNumbers();
	readChoice_rejectsASingleNonDigitCharacter();
	readChoice_acceptsANumberWithSurroundingWhitespace();
	readChoice_acceptsWindowsLineEndings();
	readChoice_skipsBlankLines();
	readChoice_acceptsAFinalEntryWithNoNewline();
	readChoice_reportsEndOfInput();
	readChoice_reportsEndOfInputAfterUnparseableTrailingInput();

	printScoreboard_printsEachCounterOnItsOwnLine();
	printScoreboard_printsZerosForANewGame();

	decideWinner_rockVsRock_isTie();
	decideWinner_rockVsPaper_computerWins();
	decideWinner_rockVsScissors_playerWins();
	decideWinner_paperVsRock_playerWins();
	decideWinner_paperVsPaper_isTie();
	decideWinner_paperVsScissors_computerWins();
	decideWinner_scissorsVsRock_computerWins();
	decideWinner_scissorsVsPaper_playerWins();
	decideWinner_scissorsVsScissors_isTie();
	decideWinner_unrecognizedMove_isTie();

	recordResult_playerWin_creditsThePlayer();
	recordResult_computerWin_creditsTheComputer();
	recordResult_tie_countsATie();
	recordResult_unknownResult_countsATie();

	getMove_alwaysReturnsAKnownMove();
	getMove_drawsEveryMove();

	cout << "All GameTest assertions passed.\n";
	return 0;
}
