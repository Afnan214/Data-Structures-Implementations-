// Afnan Ebrahim
// spell_check.cc: A simple spell checker.

#include <fstream>
#include <iostream>
#include <string>

// You can change to quadratic probing if you
// haven't implemented double hashing.
#include "quadratic_probing.h"
using namespace std;

// You can add more functions here.

// Creates and fills double hashing hash table with all words from
// dictionary_file
HashTable<string> MakeDictionary(const string &dictionary_file) {
  HashTable<string> dictionary_hash;
  // Fill dictionary_hash.
  ifstream dict_file(dictionary_file);
  string word;
  while(getline(dict_file, word))
  {
    dictionary_hash.Insert(word);
  }
  return dictionary_hash;
}
// strips all punctuation at beginning or end of a word
// changes the characters in word from upper case to lower case
void fix_word(string & word)
{
  string temp = word;
    if(!isalpha(word[0]) && !isdigit(word[0]))
    {
      word.erase(0,1);

    }
    if(!isalpha(word[word.size()-1])&& !isdigit(word[word.size()-1]))
    {
      word.erase(word.size()-1,1);

    }
  for(size_t i = 0; i< word.size(); i++)
  {
    if(isalpha(word[i])&& !islower(word[i]))
    {
      word[i] = tolower(word[i]);
    }
  }
 
}
// case_a brute force
// adds every letter in the alphabet to each position and 
// checks if each new word is found in the hash table
// probably O(N^2)
void case_a(const HashTable<string>& dictionary, const string & word)
{
  string rec=word;
  for(size_t i = 0; i <= word.size(); i++)
  {
    for(int j = 97; j< 123;j++)
    {
      char ch= (char)j;
      string temp(1,ch);
      rec.insert(i, temp);
      if(dictionary.Contains(rec))
      {
        cout<< "** "<< word<< " -> "<< rec<< " ** case A\n";
      }
      rec.erase(i, 1);

    }
  }
}
// simply delete one character at a time and check if the new word is found in the hash table.
void case_b(const HashTable<string>& dictionary, const string & word)
{
  string rec = word;
  for(size_t i = 0; i< word.size();i++)
  {
    rec.erase(i,1);
    if(dictionary.Contains(rec))
    {
      cout<< "** "<< word<< " -> "<< rec<< " ** case B\n";
    }
    char ch = word[i];
    string temp(1, ch);
    rec.insert(i, temp);
  }
}
//swaps to characters in the word using std::swap.
void case_c(const HashTable<string>& dictionary, const string & word)
{
  string rec=word;
  for(size_t i = 1; i<word.size();i++)
  {
    std::swap(rec[i],rec[i-1]);
    if(dictionary.Contains(rec))
    {
      cout<< "** "<< word<< " -> "<< rec<< " ** case C\n";
    }
    std::swap(rec[i], rec[i-1]);
  }
}
// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
void SpellChecker(const HashTable<string>& dictionary, const string &document_file) 
{
  string word;
  ifstream doc_file(document_file);
  while(doc_file >> word)
  {
    fix_word(word);
    if(!dictionary.Contains(word))
    {
      cout<<word<< " is INCORRECT\n";
      case_a(dictionary, word);
      case_b(dictionary,word);
      case_c(dictionary,word);
    }
    else
    {
      cout<<word<< " is CORRECT\n";
    }
  }
}

// @argument_count: same as argc in main
// @argument_list: save as argv in main.
// Implements
int testSpellingWrapper(int argument_count, char** argument_list) {
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Call functions implementing the assignment requirements.
    HashTable<string> dictionary = MakeDictionary(dictionary_filename);
    SpellChecker(dictionary, document_filename);

    return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
         << endl;
    return 0;
  }
  
  testSpellingWrapper(argc, argv);
  
  return 0;
}
