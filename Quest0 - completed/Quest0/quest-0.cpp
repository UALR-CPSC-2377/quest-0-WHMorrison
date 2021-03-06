/*
        HANGMAN
*/
#include <iostream>
#include <string>
#include <random>
#include <ctype.h>

using namespace std;

void fillLetters (char, string);
int chooseRandomCountry ();
void pauseConsole ();
void printGameBoard (string);
char processUserInput ();
void clearConsole ();
bool isGameDone (string, string);
void printGameOver (bool won);
bool isGameSuccessful (string currentGuess, string secretWord);
void printNumberOfTries ();

const int numCountries = 30;
int padding = 3; // number of spaces on each side of the word

// These variables are important to keep in mind
const int maxNumberGuesses = 4;
int currentGuessNumber = 0;
string currentGuessString = "";
string correctCountry = "";

string countries [] = {
    "senegal",
    "serbia",
    "seychelles",
    "singapore",
    "slovakia",
    "slovenia",
    "somalia",
    "spain",
    "sudan",
    "suriname",
    "swaziland",
    "sweden",
    "switzerland",
    "syria",
    "taiwan",
    "tajikistan",
    "tanzania",
    "thailand",
    "togo",
    "tonga",
    "tunisia",
    "turkey",
    "turkmenistan",
    "tuvalu",
    "uganda",
    "ukraine",
    "uruguay",
    "uzbekistan",
    "vanuatu",
    "venezuela",
};

int main () {
    clearConsole();

    correctCountry = countries[chooseRandomCountry()];

    // this will initialize the currentGuess String to
    // be the same length as the chosen county but contain only asterisks
	currentGuessString = std::string(correctCountry.length(), '*');

    while (isGameDone(currentGuessString,correctCountry) == false) {
        printGameBoard(currentGuessString);
        printNumberOfTries();
        char userGuess = processUserInput();
        fillLetters(userGuess, correctCountry);

        clearConsole();
    }
}

bool isGameDone (string currentGuess,string correctCountry) { // checks if the player won or lost then returns true if the game is over or false if the game is still going
	if (isGameSuccessful(currentGuess,correctCountry)) { // checks if the player has won
		printGameOver(true);
		return true;
	}
	else if (currentGuessNumber > 4) { // checks if the guess number is over 4 (which would be a loss)
		printGameOver(false);
		return true;
	}
    return false; //the game is still going
}

bool isGameSuccessful (string currentGuess,string secretWord) { // check if the player has sucessfully guessed the word
	if (currentGuess == secretWord) {
		return true;
	}
	else {
		return false;
	}
}

void printGameOver (bool won) { // prints the game over screen for either a loss or win
	if (won) {
		cout << endl << "CONGRATS" << endl;
	}
	else {
		cout << endl << "YOU LOST" << endl;
	}
	return;
}

void printGameBoard (string guess) { // print the hangman screen
	long int boxLength = guess.length() + (padding * 2);
	cout << "+";//print the top left corner

	for (int i = 0; i < boxLength; ++i) { // print the top of the box sized to hold the guess
		cout << "-";
	}

	cout << "+" << endl; // print the top right of the box and go to the next line

	cout << "|"; // print the top left wall

	for (int i = 0; i < padding; ++i) { // add padding
		cout << " ";
	}
	cout << guess;

	for (int i = 0; i < padding; ++i) { // add padding
		cout << " ";
	}

	cout << "|" << endl; // print the top right wall, go to next line

	cout << "|"; // print the bottom left wall

	for (int i = 0; i < padding; ++i) { // add padding
		cout << " ";
	}
	cout << std::string(guess.length(), '_');;

	for (int i = 0; i < padding; ++i) { // add padding
		cout << " ";
	}

	cout << "|" << endl; // print the bottom right wall, go to next line

	cout << "+";//print the bottom left corner

	for (int i = 0; i < boxLength; ++i) { // print the top of the box sized to hold the guess
		cout << "-";
	}

	cout << "+" << endl; // print the bottom right of the box and go to the next line

	return;
}

void printNumberOfTries () { // print to screen the number of incorrect guesses the player has made
	cout << "you have made " << currentGuessNumber << " guesses." << endl;
}

char processUserInput () { // get the user to input a character
	char guessLetter;
	cout << "Enter a letter to make a guess: " << endl;
	cin >> guessLetter;

    return guessLetter;
}

void fillLetters (char guessChar, string secretWord) { // check if the guess was correct and if it was correct the currentGuessString
	bool incorrectGuess = true;
	for (int i = 0; i < secretWord.length(); ++i) {
		if (secretWord[i] == guessChar) {
			incorrectGuess = false;
			currentGuessString[i] = guessChar;
		}
	}
	if (incorrectGuess) {
		currentGuessNumber++;
	}
	return;
	

}

void pauseConsole () {
    std::string temp;
    std::cout << "Enter to continue... ";
    std::getline(std::cin, temp);
}

void clearConsole () {
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    	system("cls");
    #else
        system("clear");
    #endif
}

int chooseRandomCountry () {
    random_device seed;
    default_random_engine engine(seed());
    uniform_int_distribution<int> dist(0, numCountries-1);

    return dist(engine);
}
