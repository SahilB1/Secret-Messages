#ifndef SELF_DESTRUCTING_H
#define SELF_DESTRUCTING_H

#include <string>
#include <vector>
#include <ios>
#include <utility>
#include <ostream>
#include <istream>


using std::vector;
using std::string;
using std::pair;
using std::ostream;
using std::istream;

class SelfDestructingMessage {

    private:

    vector<string> messages;
    vector<long> views_remaining;
    long start_views;

    public:

    SelfDestructingMessage();
    SelfDestructingMessage(vector<string> vec, long views);
    SelfDestructingMessage(SelfDestructingMessage &message_input);
    SelfDestructingMessage& operator=(SelfDestructingMessage &message_input);

    int size();
    vector<string> get_redacted();
    int number_of_views_remaining(int index);
    void add_array_of_lines(string messages_input[], long arr_size);

    const string& operator[](size_t index);
    friend ostream& operator<<(ostream &out, SelfDestructingMessage &messages_input);
    friend istream& operator>>(istream &in, SelfDestructingMessage &messages_input);

};

#endif