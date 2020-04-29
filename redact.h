#ifndef REDACT_H
#define REDACT_H

#include <string>
#include <vector>

using std::string;
using std::vector;

string redact_all_chars(string input);
string redact_alphabet_digits(string input);
string redact_words(string input, vector<string> vec);


#endif
 