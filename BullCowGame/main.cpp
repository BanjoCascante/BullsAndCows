/*Main class that is in charge of all the interactions with the user. It then passes all the inputs to the FBullCowGame, so it can analize it*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

FText getValidGuess();
void printGuess(FText guess);
void printIntro();
void playGame();
bool askToPlayAgain();
void printGameSummary();
bool keepPlaying = true;
FBullCowGame bullCowGame;


/*Main game loop*/
int main() {

	printIntro();
	do
	{
		playGame();
		keepPlaying = askToPlayAgain();
	} while (keepPlaying);

	return 0;
}

/*Called every time a game want to be played*/
void playGame()
{
	bullCowGame.reset();
	int32 maxTries = bullCowGame.getMaxTries();
	while(!bullCowGame.isGameWon()  && bullCowGame.getCurrentTry() <= maxTries){
		FText myGuess = getValidGuess();
		printGuess(myGuess);
		FBullCowCount myBullCowCount = bullCowGame.submitValidGuess(myGuess);
		std::cout << "Bulls " << myBullCowCount.bulls << " . Cows " << myBullCowCount.cows << "\n\n";
	}
	printGameSummary();
}


/*Ask the player if he want to keep playing*/
bool askToPlayAgain()
{
	std::cout << "Want to play again??? (Y/N) ";
	FText response = "";
	std::getline(std::cin, response);

	std::cout << std::endl;
	return response[0] == 'y' || response[0] == 'Y';
}
/*Print a little intro to the game*/
void printIntro() {
	constexpr int32 WORD_LENGTH = 9;

	std::cout << "Welcome to Bulls and Cows!\n";
	std::cout << "Guess the " << bullCowGame.getHiddenWordLength() << " isogram!" << std::endl;
}

/*Check the input word and based on that, print a message indicating the user the kind of error
@return A string with an already validated guess
*/
FText getValidGuess() {
	FText guess = "";
	EGuessStatus guessStatus = EGuessStatus::Invalid_Status;

	do {
		std::cout << "Try " << bullCowGame.getCurrentTry() << " of " << bullCowGame.getMaxTries() << "! " << "Enter your guess: ";
		std::getline(std::cin, guess);
		guessStatus = bullCowGame.checkGuessValidity(guess);
		switch (guessStatus)
		{
		case EGuessStatus::OK:
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Word is not an isogram! \n";
			break;
		case EGuessStatus::Word_Too_Long:
			std::cout << "Word is too long! \n";

			break;
		case EGuessStatus::Word_Too_Short:
			std::cout << "Word is too short! \n";
			break;
		case EGuessStatus::Not_All_Lowercase:
			std::cout << "Word is not in lower case! \n";
			break;
		default:
			break;
		}

		std::cout << "\n";
	} while (guessStatus != EGuessStatus::OK);


	return guess;
}

/*Print the guess
@param[in] A string containing the guess word*/
void printGuess(FText guess) {
	std::cout << "Your guessed word is: " << guess << std::endl;
}
/*Print a game summary based on the game won condition*/
void printGameSummary() {
	if (bullCowGame.isGameWon()) {
		std::cout << "Congrats! You won! \n";
	}
	else {
		std::cout << "You lose. Keep Trying! \n";
	}
}