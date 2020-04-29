#include "self_destructing.h"
#include "redact.h"

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm> 
#include <numeric>
#include <map>
#include <set>
#include <sstream>

using std::stringstream;
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
using std::getline;

// Empty constructor initialized with empty values

SelfDestructingMessage::SelfDestructingMessage() {
    messages = {};
    views_remaining = {};
    start_views = 0;
}


// Constructor that takes vector and number of allowed views will assign the messages to the 
// private messages vector in the SelfDestructingMessage class and the views to the private start_views
// variable. We create a views remaining vector that had the same size as messages so that each corresponsing 
// element indicates the views left for the message at that index. 

SelfDestructingMessage::SelfDestructingMessage(vector<string> vec, long views) {
    messages = vec;
    start_views = views;
    for(int i = 0; i < messages.size(); i++) {
        views_remaining.push_back(views);
    }
}

// Here we create our copy constructor and make sure to move all the data to the new object that has been assigned to an old object
// to preserve the number of views left to assure that no extra views are allowed when a new assignment is made. 

SelfDestructingMessage::SelfDestructingMessage(SelfDestructingMessage &message_input) {
    cout << "Copy Constructor!" << endl;
    start_views = message_input.start_views;
    for(int i = 0; i < message_input.views_remaining.size(); i++) {
        messages.push_back(message_input.messages[i]);
        views_remaining.push_back(message_input.views_remaining[i]);
        message_input.views_remaining[i] = 0;
    }
}

// Messages vector size

int SelfDestructingMessage::size() {
    return messages.size();
}

// Here we redact any part of a message that matches any of the three conditions to be either some letter or number

vector<string> SelfDestructingMessage::get_redacted() {
    vector<string> redacted;
    for(auto elem: messages) {
        string str = elem;
        for (size_t i = 0; i < str.length(); i++) {
            if((str[i] <= 90 && str[i] >= 65) || (str[i] <= 122 && str[i] >= 97) || (str[i] <= 57 && str[i] >= 48)) {
                str[i] = '#';
            }
        }
        redacted.push_back(str);
    }

    return redacted;
}

// We return the views left for a message from the vector that contains solely the number of views for each 
// corresponding index and message in the messages array

int SelfDestructingMessage::number_of_views_remaining(int index) {
    return views_remaining[index];
}

// We decrement the views for the message viewed at the index and check to see if the index is in range before
// viewing the message

const string& SelfDestructingMessage::operator[](size_t index) {
    if(index < messages.size() && index >= 0 && views_remaining[index] > 0) {
        views_remaining[index]--;
        return messages[index];
    } else {
        if(index < 0 || index >= messages.size()) {
            throw std::out_of_range ("out of range");
        } else {
            throw std::invalid_argument ("invalid argument");
        } 
    }
}


// We add the messages from the array to the messages vector which contains all the messages and add
// the starting number of views for each message too

void SelfDestructingMessage::add_array_of_lines(string messages_input[], long arr_size) {
    for(size_t i = 0; i < arr_size; i++) {
        messages.push_back(messages_input[i]);
        views_remaining.push_back(start_views);
    }
}

// We format the output here accordingly based on how it is shown in the test cases

ostream& operator<<(ostream &out, SelfDestructingMessage &message_feed) {
    vector<string> messages_input = message_feed.get_redacted();
    for(int i = 0; i < messages_input.size(); i++) {
        if(message_feed.number_of_views_remaining(i) < 10) {
            out << "0" << message_feed.number_of_views_remaining(i) << ": " << messages_input[i] << endl;
        } else {
            out << message_feed.number_of_views_remaining(i) << ": " << messages_input[i] << endl;
        }
    }
    return out;
}

// Here we read into a string using getline to assure that we capture all parts of the message to read

istream& operator>>(istream &in, SelfDestructingMessage &messages_input) {
    string result_line = "";
    getline(in, result_line);
    messages_input.messages.push_back(result_line);
    messages_input.views_remaining.push_back(messages_input.start_views);
    return in;
}

// Here we assure that all the attributes for the messages and views are transferred to the new object and zeroed out
// in the old object. 

SelfDestructingMessage& SelfDestructingMessage::operator=(SelfDestructingMessage &message_input) {
    for(int i = 0; i < message_input.views_remaining.size(); i++) {
        messages.push_back(message_input.messages[i]);
        views_remaining.push_back(message_input.views_remaining[i]);
        message_input.views_remaining[i] = 0;
    }
    return *this;
}


int main() {
    vector<string> m = {
    "The plan is go!!!",
    "Attack - at - midnight",
    "Bring 97 cookies!"
    };

    SelfDestructingMessage sdm(m, 2);

    sdm[1];
    sdm[1];
    sdm.number_of_views_remaining(1);
    sdm[2];

    /*ASSERT_EQ(string("Attack - at - midnight"), sdm[1]);
    ASSERT_EQ(string("Attack - at - midnight"), sdm[1]);
    ASSERT_EQ(0, sdm.number_of_views_remaining(1));
    ASSERT_EQ(string("Bring 97 cookies!"), sdm[2]);*/

    string expected = R"(02: ### #### ## ##!!!
    00: ###### - ## - ########
    01: ##### ## #######!
    )";
    string expected_no_view = R"(00: ### #### ## ##!!!
    00: ###### - ## - ########
    00: ##### ## #######!
    )";

    stringstream ss;
    ss << sdm;
    cout << ss.str() << endl;
    cout << endl;
    //ASSERT_EQ(expected, ss.str());

    ss.str(""); ss.clear();
    ss << sdm;
    cout << ss.str() << endl;
    cout << endl;
    //ASSERT_EQ(expected, ss.str());

    SelfDestructingMessage sdm2(sdm);
    ss.str(""); ss.clear();
    ss << sdm2;
    cout << ss.str() << endl;
    cout << endl;
    //ASSERT_EQ(expected, ss.str());

    ss.str(""); ss.clear();
    ss << sdm;
    cout << ss.str() << endl;
    cout << endl;
    //ASSERT_EQ(expected_no_view, ss.str());
}