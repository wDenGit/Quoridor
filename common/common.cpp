// #include <sstream>
#include <iostream>
#include <unistd.h> // sleep()
#include "common.hpp"

using namespace std;

vector<string> Parser::splitBySeparator(string line, string separator) {
    vector<string> vectorWords;
    size_t pos=0;
    string data;
    while ((pos = line.find(separator)) != std::string::npos) {
        data = line.substr(0, pos);
        vectorWords.push_back(data);
        line.erase(0, pos + separator.length());
    }
    vectorWords.push_back(line);
    return vectorWords;
}

vector<int> FriendsParser::getFriendsKeyList() {
    vector<int> friendsKey;
    vector<string> toConvert = this->getVectorWords();
    toConvert.pop_back();
    for (string &s: toConvert){
        friendsKey.push_back(stoi(s));
    }
    return friendsKey;
}