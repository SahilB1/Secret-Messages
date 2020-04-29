#include "redact.h"

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm> 
#include <numeric>
#include <map>
#include <set>

using std::sort;
using std::make_pair;
using std::set;
using std::pair;
using std::map;
using std::reverse;
using std::pair;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::boolalpha;
using std::accumulate;
using std::find;

// Here we simply iterate through the input given and redact each character and return the result

string redact_all_chars(string input) {
   string str = input; 
   for (size_t i = 0; i < str.length(); i++) {
       str[i] = '#';
   }
   return str;
}

// We use the ASCII values of the chracters we want to redact here and only redact a character if it matches any of the three sets conditions to be 
// either a letter or digit

string redact_alphabet_digits(string input) {
    string str = input; 
    for (size_t i = 0; i < str.length(); i++) {
       if((str[i] <= 90 && str[i] >= 65) || (str[i] <= 122 && str[i] >= 97) || (str[i] <= 57 && str[i] >= 48)) {
           str[i] = '#';
       }
   }
   return str;
}

// To redact the words we use a vector of pairs that stores the relevant indicies and length of the words we wish to redact 
// and we use the index to start the redact process and the length of the word to know when to stop redacting characters

string redact_words(string input, vector<string> vec) {
    string str = input;
    string temp = "";
    vector<pair<size_t, int>> indicies;

   for(auto elem: vec) {
        size_t found = input.find(elem, 0);
        while(found != string::npos) {
            indicies.push_back(make_pair(found, elem.length()));
            found = input.find(elem, found+1);
        }   
   }
   for(auto elem: indicies) {
       for(int i = elem.first; i < elem.first + elem.second; i++) {
           str[i] = '#';
       }
   }
   return str;
}

