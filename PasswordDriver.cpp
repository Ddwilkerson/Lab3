#include "Password.h"
//fill in includes, don't forget namespaces

#include <iostream>
using namespace std;

void addWords(Password* fh)
{
   Keyboard* kb = Keyboard::getKeyboard();
   String* file_str = kb->readString("Enter the file name containing the possible passwords: ");
   ReadFile* rf = new ReadFile(file_str->getText());
   delete file_str;

   String* num_words_str = rf->readLine();
   int num_words = num_words_str->a_to_i();
   delete num_words_str;

   for (int i = 0; i < num_words; i++)
   {
      String* word = rf->readLine();
      fh->addWord(word);
   }

   delete rf;
   fh->displayViableWords();
}

void guessWords(Password* fh)
{
   Keyboard* kb = Keyboard::getKeyboard();
   int numLeft = fh->getNumberOfPasswordsLeft();
   while (numLeft > 1)  //terminate if the password has been identified, or there is no valid password (user entry error)
   {
      int best_guess_index = fh->bestGuess();

      String* best_guess_word = fh->getOriginalWord(best_guess_index);
      cout << "You should guess \"";
      best_guess_word->displayString();
      cout << "\" at index " << best_guess_index;
      cout << endl << endl;

      String* guess_str = kb->readString("Index of word in the original word list to guess (1-based): ");
      int guess = guess_str->a_to_i();
      delete guess_str;

      String* match_str = kb->readString("Number of character matches: ");
      int match = match_str->a_to_i();
      delete match_str;
      cout << endl;

      fh->guess(guess, match);  //1-based index of the guessed word and the number of character matches
      fh->displayViableWords();

      numLeft = fh->getNumberOfPasswordsLeft();
   }
}

int main()
{
   Password* fallout = new Password();
   addWords(fallout);
   guessWords(fallout);
   delete fallout;
}
