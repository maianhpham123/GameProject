#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

const string WORD_LIST[] = {"dog", "cat", "human"};
const int WORD_COUNT = sizeof(WORD_LIST) / sizeof(string);
const int MAX_BAD_GUESSES = 7;

string chooseWord() {
     int randomIndex = rand() % WORD_COUNT; //3 = the number of words in array
     return WORD_LIST[randomIndex];
}

void renderGame(string guessedWord, int badGuessCount) {
     cout << guessedWord << endl;
     cout << badGuessCount << endl;
}

char readAGuess() {
     char ch;
     cout << "Enter you guess: ";
     cin >> ch;
     return ch;
}

bool contains(string word,char c) {
     return (word.find_first_of(c) != string::npos); //new!
}

string update(string guessedWord, char guess, string secretWord) { //guessedWord: tham tri
     for (int i = 0; i < guessedWord.length(); i++) {
          if (guess == secretWord[i]) guessedWord[i] = guess;
     }
     //test: cout << secretWord << " " << guess << " " << guessedWord << endl; //test to see if the update function was right
     return guessedWord; //tra ve gia tri cua guessedWord
}

void displayResult() {
     cout << "Game Over!";
}

int main()
{
     srand(time(0)); //seed rand function
     //initialise
     string secretWord = chooseWord(); //use function
     string guessedWord = string(secretWord.length(), '-'); //initialise with '-'
     int badGuessCount = 0;

     do {
          renderGame(guessedWord, badGuessCount); //draw the renderer of the game, this case guessedword
          char guess = readAGuess();
          if (contains(secretWord, guess)) {
               guessedWord = update(guessedWord, guess, secretWord); //update the guessedword
          }
          else badGuessCount ++;
     } while (badGuessCount < MAX_BAD_GUESSES && guessedWord != secretWord); //condition for endgame

     displayResult();

     return 0;
}
