#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// all values intialised to 0
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Lenth,
	Not_Lowercase
};


class FBullCowGame
{
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const;

	void Reset(); // TODO a more rich return value

	//provide a  method for counting bulls&cows and increasing try
	// assumin valid guess
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	//bool IsIsogram(FString);
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};
