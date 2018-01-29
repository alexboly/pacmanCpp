#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>

using namespace std;

const string before(const string& line, const char& element){
    const int position = line.find(element);
    return line.substr(0, position);
}

const string after(const string& line, const char& element){
    const int position = line.find(element);
    return line.substr(position + 1);
}

const string tick(const string& initialLine){
    const string afterAfterMove = after(initialLine, '>').substr(1);
    return before(initialLine, '>') + ' ' + '>' + afterAfterMove;
}

TEST_CASE("pacman eats the dot on the right when it has dots on the right and it's oriented towards right"){
    string lineBeforeMove =           "....>....";
    string expectedLineAfterMove =    ".... >...";

    auto lineAfterMove = tick(lineBeforeMove);

    CHECK(lineAfterMove == expectedLineAfterMove);
}
