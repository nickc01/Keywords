/*
	Nicholas Cullen
	11/22/19
	Keywords: A game where the player guesses three scrambled code words to win
*/

#include <string> //Used to gain access to std::string
#include <iostream> //Used to gain access to std::cout and std::cin
#include <cstdlib> //Used to gain access to rand() and srand()
#include <ctime> //Used to gain access to time()
#include <algorithm> //Used to gain access to random_suffle()


//Prevents me from having to use "std::" for anything in the std namespace
using namespace std;

//Used to keep track of the amount of code words that have been cracked through the game
int codeWordCounter = 1;

//Represents the amount of times the player plays the Code Word Puzzle before they win
//For example, if the totalPlayTimes is 3, then the player plays 3 puzzles before they win
int totalPlayTimes = 3;

//The total score for the player
int score = 0;

//Whether the player wants to play again or not
bool PlayAgain = false;

//Whether the player has won a round or not
bool WonRounds = false;


//Takes in a string, scrambles it, and returns the scrambled form
string Scramble(string str);

//Takes in a string and makes it lower case
string ToLowerCase(string input);

//Initiates a code word puzzle
bool DoCodeWord();

//The definition for a code word
struct CodeWord
{
	//The word itself
	string word;
	//The hint for cracking the code word
	string hint;
};

//A list of all the code words that could appear in the game, along with their hints
CodeWord codeWords[] = 
{
	{"Telephone", "Used to talk to other people from very far away"},
	{"Minecraft", "A popular survival video game"},
	{"Firefox", "The name of a well-known web browser"},
	{"Spaghetti", "The name of an italian food"},
	{"Zucchini", "A type of vegetable"},
	{"Playstation", "A video game console"},
	{"Supermarket", "A place where you buy groceries"},
	{"Facebook", "A popular social media website"},
	{"Motherboard", "The name of an important computer component"},
	{"Violet", "The name of a color"},
	{"Baseball","A popular sport"},
	{"Kangaroo","An australian animal"},
	{"Mexico", "The name of a middle american country"},
	{"Factorial", "A mathmatical term : { !n }"}
};

int main()
{
	//Set the seed of the randomizer
	srand(time(0));

	//Print the greeting message
	cout << "Welcome to Nick's Codebreaker Game!\n\n\n";
	cout << "You will be give three scrambled code words, and it is your job to unscramble them.\nWhen you figure out what they are, type in your answer to see if you are right.\nIf you are, then you move on to the next word.\n\n";
	cout << "Press the Enter key to start";

	//Wait for the "Enter" key to be pressed
	cin.get();

	do
	{
		WonRounds = true;
		//Run the puzzles "totalPlayTimes" amount of times
		for (codeWordCounter = 1; codeWordCounter <= totalPlayTimes; codeWordCounter++)
		{
			//Do a code word puzzle
			if (DoCodeWord() == false)
			{
				//If the player didn't complete it, then break out of the loop
				WonRounds = false;
				break;
			}
		}

		//Clear the screen
		system("cls");

		//If the player has won all the rounds
		if (WonRounds)
		{
			//Print the congrats message
			cout << "Congrats!!! You guessed all 3 code words!\n";
			cout << "Thank you for playing!\n\n";
		}

		cout << "Your current score is " << score << "\n\n";

		cout << "Want to play again? [Y/N]\n";

		//Get the player's input
		string input;
		getline(cin, input);

		//If the player said "Y", then PlayAgain will be true, and false otherwise
		PlayAgain = (ToLowerCase(input).find("y") < string::npos);

	//Repeat until PlayAgain is false
	} while (PlayAgain);

	//Wait for a key press
	system("pause");

	//Exit the application
	return 0;
}


//Takes in a string, scrambles it, and returns the scrambled form
string Scramble(string str)
{
	//Run the random shuffle algorithm
	random_shuffle(str.begin(), str.end());
	//Return the result
	return str;
}

//Takes in a string and makes it lower case
string ToLowerCase(string input)
{
	//Iterate over all the characters, grabbing them by reference
	for (char& c : input)
	{
		//Make the character lower case
		c = tolower(c);
	}
	//Return the result
	return input;
}

//Initiates a code word puzzle
bool DoCodeWord()
{
	//Clear the screen
	system("cls");

	/*
	Get a random index between 0 - (size of array);

	sizeof(codeWords) gets the amount of elements in the array TIMES the size of the CodeWord struct.
	But if we divide that by the size of the CodeWord struct, we are left with the amount of elements in the array
	*/
	int randIndex = rand() % (sizeof(codeWords) / sizeof(CodeWord));

	//Get a random code word from the list
	CodeWord selectedCodeWord = codeWords[randIndex];

	//Make a lower case version of the word
	string codeWordLowerCase = ToLowerCase(selectedCodeWord.word);

	//Make a scrambled version of the word
	string scrambledWord = Scramble(selectedCodeWord.word);


	//Print the code word number
	cout << "Here is code word number " << codeWordCounter << " of " << totalPlayTimes;

	while (true)
	{

		//Print the code word and possible commands
		cout << "\n\n\n";
		cout << scrambledWord << "\n\n\n";
		cout << "Type in the unscrambled word to win\n";
		cout << "If you need a hint, in \"hint\"\n";
		cout << "If you want to quit the game, type \"quit\"\n\n";


		//Get the input
		string input;
		getline(cin, input);
		//Make it lower case
		input = ToLowerCase(input);

		//Clear the screen
		system("cls");

		//If the player typed in the word "hint"
		if (input.find("hint") < string::npos)
		{
			//Print the hint
			cout << "~~~Hint: " << selectedCodeWord.hint << " ~~~";
			//Go back to the top of the loop
			continue;
		}
		else if (input.find("quit") < string::npos)
		{
			//Print a closing message
			cout << "Thanks for playing!\n\n";

			//Return false, since the player did not complete the puzzle
			return false;
		}
		//If the input matches the code word
		else if (input.find(codeWordLowerCase) < string::npos)
		{
			//Tell the player that they got the correct word
			cout << "Correct!\n\n";
			cout << "Press Enter to continue\n";

			//Wait for the "Enter" key to be pressed
			cin.get();

			//Increase the player's score
			score++;

			//Return true, signifying that the player completed the puzzle
			return true;
		}
		//If an incorrect guess is made
		else
		{
			//Tell the player that they got it wrong
			cout << "~~~ Incorrect!   Try Again ~~~";
			//Go back to the top of the loop and try again
			continue;
		}
	}

}