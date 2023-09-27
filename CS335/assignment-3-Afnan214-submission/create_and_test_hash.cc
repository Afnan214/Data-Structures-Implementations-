//Afnan Ebrahim
#include <fstream>
#include <iostream>
#include <string>

// Uncomment when you implemented linear probing & double hashing
 #include "linear_probing.h"
#include "double_hashing.h"

#include "quadratic_probing.h"

using namespace std;


// You can add more functions here
template <typename HashTableType>
void part_a(HashTableType &hash_table)
{
    size_t N = hash_table.get_num_elem();               
    size_t T = hash_table.get_table_size();
    float l_factor = float(N)/float(T);                 //type cast N and T to type float to get propper float value
    size_t C = hash_table.get_num_collisions();
    float avg_coll = float(C)/float(N);                 //type cast N and T to type float to get propper float value
    cout<< "number_of_elements: "<< N<< endl;
    cout<< "size_of_table: "<< T<< endl;
    cout<< "load_factor: "<< l_factor<< endl;
    cout<< "collisions: "<< C<< endl;
    cout<< "avg_collisions: "<< avg_coll<< endl<<"\n";
}
// @hash_table: a hash table (can be linear, quadratic, or double)
// @words_filename: a filename of input words to construct the hash table
// @query_filename: a filename of input words to test the hash table
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table,
			      const string &words_filename,
			      const string &query_filename) {
    hash_table.MakeEmpty();
    //..Insert your own code
    ifstream word_file(words_filename);            
    string word;
    while(getline(word_file, word))             //string word <- word from "word_file"
    {
        hash_table.Insert(word);                //word is inserted into the hashtable
    }
    part_a(hash_table);                         // calls part_a
    ifstream query_file(query_filename);        
    string query;
    int probes;     // declare int probes for when passed as a parameter when attempting to return number of probes.
    while (getline(query_file, query))
    {
        if(hash_table.Contains(query))
        {
            //if hash_table contains the word, type found and return the number of probes
            cout<< query << " found "<< hash_table.get_probes(query, probes)<<endl;
            probes = 0;
        }
        else
        {
            //if hash_table contains the word, type not_found and return the number of probes
            cout<< query<< " not_found "<< hash_table.get_probes(query, probes)<<endl;
            probes=0;
        }
        
    }




}

// @argument_count: argc as provided in main
// @argument_list: argv as provided in imain
// Calls the specific testing function for hash table (linear, quadratic, or double).
int testHashingWrapper(int argument_count, char **argument_list) {
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 89;
    if (argument_count == 5) {
	const string rvalue(argument_list[4]);
	R = stoi(rvalue);
    }

    if (param_flag == "linear") {
      // Uncomment below when you have implemented linear probing.
       HashTableLinear<string> linear_probing_table;
       TestFunctionForHashTable(linear_probing_table, words_filename,
       			 query_filename);
    } else if (param_flag == "quadratic") {
	HashTable<string> quadratic_probing_table;
	TestFunctionForHashTable(quadratic_probing_table, words_filename,
				 query_filename);
    } else if (param_flag == "double") {
	cout << "r_value: " << R << endl;
        // Uncomment below when you have implemented double hashing.
	 HashTableDouble<string> double_probing_table;
     double_probing_table.set_R(R);
	 TestFunctionForHashTable(double_probing_table, words_filename,
	 			 query_filename);
    } else {
	cout << "Unknown tree type " << param_flag
	     << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}








// Sample main for program create_and_test_hash. DO NOT CHANGE IT.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv) {
    if (argc != 4 && argc != 5) {
	cout << "Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag>" << endl;
	cout << "or Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
	return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}
