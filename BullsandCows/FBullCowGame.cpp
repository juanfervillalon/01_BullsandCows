#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() {Reset();}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32>WordLengthMaxTries{ {3,4},{4,7},{5,10},{6,15},{7,20} };
	return WordLengthMaxTries[MyHiddenWord.length()];
}
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter word as isogram
	if (Word.length() <= 1) { return true; }
	//set up our map
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]){//loop through all letters of the word
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}

		//if the letter is in the map
			//we do NOT have an isogram
		//otherwise
			//add the letter to the map as seen
	}
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto letter: Word)
	{
		if (!islower(letter))//if not a lower case letter
			return false;
	}
	return true;
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

// receives a VALID guess, increments turn and return count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	// loop through all letters in the Hidden Word
	for (int32 i = 0; i < WordLength; i++) {
		// loop through all letters in the Guess
		for (int32 j = 0; j < WordLength; ++j) {
			// if the match then
			if (Guess[i] == MyHiddenWord[j]) {
				if (i == j){
					BullCowCount.Bulls++; //increment bulls
				}
				else{
 					BullCowCount.Cows++; //must be a cow
				}
			}
			// increment bulls
			 // increment cows if not
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
  	}
	else if (GetHiddenWordLength() != Guess.length())
	{
		return EGuessStatus::Wrong_Lenth;
	}
	else
	{
		return EGuessStatus::OK;
	}

}
