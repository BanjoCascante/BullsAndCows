/*This class contains all the logic for the bulls and cows game. It doesn't have a direct interaction with the user*/

#include "FBullCowGame.h"

/*Constructor*/
FBullCowGame::FBullCowGame()
{
	reset();
}


/*Return the maximun number of tries, based on the word length
@return An int with the number of tries for the current word
*/
int32 FBullCowGame::getMaxTries() const
{
	TMap <int32, int32> wordLenghtAndTries = { {3,4} , { 4,5 },{ 5,10 },{ 6,15 },{ 7,20 }};
	return wordLenghtAndTries[getHiddenWordLength()];
}
/*Return the current try of the game
@return An int with the current try of the game
*/
int32 FBullCowGame::getCurrentTry() const
{
	return myCurrentTry;
}

/*Return the current status of the game (if won or not)
@return A bool indicating if the game is won or not.
*/
bool FBullCowGame::isGameWon() const
{
	return bIsGameWon;
}

/*Returns the lenght of the current hidden word
@return An int with the the number of letter of the hidden word*/
int32 FBullCowGame::getHiddenWordLength() const
{
	return 	hiddenWord.length();
}

/*Reset the game to it's initial status. Sets the following variables
	-myCurrentTry to 1
	-Pick a new hidden word from a list of isograms
	-myMaxTries based on the hidden word length
	-bGameWon to false
*/
void FBullCowGame::reset()
{
	myMaxTries = getMaxTries();
	myCurrentTry = 1;

	const FString HIDDEN_WORD = "and";
	hiddenWord = HIDDEN_WORD;
	
	bIsGameWon = false;

}

/*Perform certain validations over an specific word. The validations are:
	-Is the entered word too short (compared to the hidden word length)
	-Is the entered word too long (compared to the hidden word length)
	-Is the word all lowercase
	-Is the word an isogram
@param[in] string containing a word
@return An EGuessStatus enum with the return status of the validation
*/
EGuessStatus FBullCowGame::checkGuessValidity(FString guess)
{
	if (guess.length() < getHiddenWordLength()) {
		return EGuessStatus::Word_Too_Short;
	}
	if (guess.length() > getHiddenWordLength()) {
		return EGuessStatus::Word_Too_Long;
	}
	if (!isLowerCase(guess)) {
		return EGuessStatus::Not_All_Lowercase;
	}
	if (!isIsogram(guess)) {
		return EGuessStatus::Not_Isogram;
	}
	return EGuessStatus::OK;
}


/*Check the submitted word and counts the bulls and cows included in it. It also increases the current try
@param[in] A string with the guess word
@return A FBullCowCount struct with the number of cows and bulls in the word*/
FBullCowCount FBullCowGame::submitValidGuess(FString guess)
{
	myCurrentTry++;
	FBullCowCount bullCowCount;
	int32 hiddenWordLength = hiddenWord.length();
	for (int32 i = 0; i < hiddenWordLength; i++) {
		if (hiddenWord[i] == guess[i]) {
			bullCowCount.bulls++;
		}
		else {
			for (int32 j = 0; j < hiddenWordLength; j++) {

				if (guess[i] == hiddenWord[j]) {
					bullCowCount.cows++;
					break;
				}
			}
		}
		
	}
	if (bullCowCount.bulls == hiddenWordLength) {
		bIsGameWon = true;
	}
	return bullCowCount;
}

/*Checks if the entered word is an isogram
@param[in] A string containing the word we want to analize
@return A bool indicating if the word is an isogram*/
bool FBullCowGame::isIsogram(FString word) const
{
	TMap <char,bool> myMap;
	if (word.length() <= 1) {
		return true;
	}
	for (char letter : word) {
		letter = tolower(letter);
		if (myMap[letter]) {//The letter is on the map
			return false;
		}
		else {
			myMap[letter] = true;
		}
	}
	return true;
}

/*Checks if the entered word is in lower case
@param[in] A string containing the word we want to analize
@return A bool indicating if the word is in lower case*/
bool FBullCowGame::isLowerCase(FString word) const
{
	for (auto letter : word) {
		if (!islower(letter)){
			return false;
		}
	}
	return true;
}


