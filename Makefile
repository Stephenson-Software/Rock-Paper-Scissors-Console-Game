.PHONY: all clean

all: RockPaperScissors

RockPaperScissors: src/RockPaperScissors.cpp
	@echo "---"
	@echo "Compiling RockPaperScissors"

	g++ src/RockPaperScissors.cpp -o RockPaperScissors

	@echo "Finished compiling RockPaperScissors.cpp"

clean:
	@echo "---"
	@echo "Removing RockPaperScissors"

	rm -f RockPaperScissors

	@echo "Finished removing RockPaperScissors"
