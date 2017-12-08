/*This is the console executable that makes use of the BullsandCows class
It acts like the view in a MVC patter, and is responsible for all user
interaction. For game logic see the FBullaCowGame class.
*/


#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;


void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

void main()
{
	bool bPlayAgain = false;
	do {

		PrintIntro();

		PlayGame();

		bPlayAgain = AskToPlayAgain();

	}
	while (bPlayAgain);
	return;
}	

//loop for the number of turns
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is not won
	// and there are tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
}

//introduce the game
void PrintIntro() {

	//constexpr int32 WORLD_LENGTH = 5;
	std::cout << "\n\n Welcome to Bulls and Cows v1.0" << std::endl;
   	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I am thinking of?\n";
}

//loop continually until the user gives a valid Guess
FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout <<". Enter your guess : ";

		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Lenth:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			//return Guess;
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until a valid input
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you wanna play again? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN\n";
	}
	else
		std::cout << "Better Luck next time!\n";
}
