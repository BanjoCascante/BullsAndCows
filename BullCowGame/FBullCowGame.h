#pragma once
#include <string>
#include <map>
#define TMap std::map
#include <iostream>

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 bulls = 0;
	int32 cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Word_Too_Long,
	Word_Too_Short,
	Not_All_Lowercase

};

class FBullCowGame {
public:

	FBullCowGame();
	int32 getMaxTries() const;
	int32 getCurrentTry() const;
	bool isGameWon() const;
	int32 getHiddenWordLength() const;

	void reset(); //ToDo
	EGuessStatus checkGuessValidity(FString);
	FBullCowCount submitValidGuess(FString);

private:
	bool isIsogram(FString) const;
	bool isLowerCase(FString) const;

	int32 myCurrentTry = 1;
	int32 myMaxTries = 5;
	FString hiddenWord;
	bool bIsGameWon;

};