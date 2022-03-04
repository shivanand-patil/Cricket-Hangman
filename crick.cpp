#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
const int MAX_TRIES = 5;
using namespace std;
const int n=25;

class names
{
protected:
   string name;
   string word;
   char letter;
   int num_of_wrong_guesses;
   string words[n];

public:
   void na()
   {
      num_of_wrong_guesses = 0;
   }
   void getnames();
   void randomasi();
};

void names::getnames()
{
  
    ifstream name("cricket");
   for (int i = 0; i <n; i++)
   {
      name >> words[i];
   }
}

void names::randomasi()
{
   // choose and copy a word from array of words randomly
   srand(time(NULL));
   int n = rand() % 31;
   word = words[n];
}

class game : public names
{
public:
   void exe();
   int letterFill(char guess, string secretword, string &guessword);
};

void game::exe()
{

   // Initialize the secret word with the * character
   string unknown(word.length(), '*');
   cout<<unknown;
   // welcome the user
   cout << "\n\nWelcome to CRICKET HANGMAN... Guess a cricketer's name";
   cout << "\n\nEach letter in a cricketer's name is represented by a star";
   cout << "\n\nPlayer has to type only one letter in one try";
   cout << "\n\nYou have " << MAX_TRIES << " tries to try and guess the word.";
   cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

   // Loop until the guesses are used up
   while (num_of_wrong_guesses < MAX_TRIES)
   {
      cout << "\n\n"
           << unknown;
      cout << "\n\nGuess a letter: ";
      cin >> letter;
      // Fill secret word with letter if the guess is correct,
      // otherwise increment the number of wrong guesses.
      if (letterFill(letter, word, unknown) == 0)
      {
         cout << endl
              << "Whoops, SWING AND A MISS!! That letter isn't in there!" << endl;
         num_of_wrong_guesses++;
      }
      else
      {
         cout << endl
              << "SHOTT!! You found a letter in the word, GOOD GOING" << endl;
      }
      // Tell user how many guesses has left.
      cout << "You have " << MAX_TRIES - num_of_wrong_guesses;
      cout << " balls left." << endl;
      // Check if user guessed the word.
      if (word == unknown)
      {
         cout << word << endl;
         cout << "cheeks! You got it!";
         break;
      }
   }
   if (num_of_wrong_guesses == MAX_TRIES)
   {
      cout << "\n CLEAN BOWLED... You are out, back to the pavilion" << endl;
      cout << "The cricketer's name was : " << word << endl;
   }
   cin.ignore();
   cin.get();
   return;
}

int game::letterFill(char guess, string secretword, string &guessword)
{
   int i;
   int matches = 0;
   int len = secretword.length();
   for (i = 0; i < len; i++)
   {
      // Did we already match this letter in a previous guess?
      if (guess == guessword[i])
         return 0;

      // Is the guess in the secret word?
      if (guess == secretword[i])
      {
         guessword[i] = guess;
         matches++;
      }
   }
   return matches;
}

int main()
{

   game g;
   g.na();
   g.getnames();
   g.randomasi();
   g.exe();
}