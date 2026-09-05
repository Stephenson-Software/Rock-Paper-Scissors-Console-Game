.PHONY: all clean test

all: RockPaperScissors

RockPaperScissors: src/RockPaperScissors.cpp src/Game.h
	@echo "---"
	@echo "Compiling RockPaperScissors"

	g++ src/RockPaperScissors.cpp -o RockPaperScissors

	@echo "Finished compiling RockPaperScissors.cpp"

GameTest: src/GameTest.cpp src/Game.h
	@echo "---"
	@echo "Compiling GameTest"

	g++ src/GameTest.cpp -o GameTest

	@echo "Finished compiling GameTest.cpp"

test: GameTest
	@echo "---"
	@echo "Running GameTest"

	./GameTest

	@echo "Finished running GameTest"

clean:
	@echo "---"
	@echo "Removing build output"

	rm -f RockPaperScissors GameTest

	@echo "Finished removing build output"
