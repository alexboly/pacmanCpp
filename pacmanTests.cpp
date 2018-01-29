#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>

using namespace std;

enum class KindOfToken : char {
    Empty = ' ',
    Dot = '.',
    Pacman = '>'
};

const string before(const string& line, const char& element){
    const int position = line.find(element);
    return line.substr(0, position);
}

auto beforePacman = [](const string& line){
    return before(line, '>');
};

const string after(const string& line, const char& element){
    const int position = line.find(element);
    return line.substr(position + 1);
}

auto afterPacman = [](const string& line){
    return after(line, '>');
};

const string tick(const string& initialLine){
    const string afterAfterMove = afterPacman(initialLine).substr(1);
    return beforePacman(initialLine) + ' ' + '>' + afterAfterMove;
}

const string dots(const int count){
    vector<char> theDots(count, '.');
    return string(theDots.begin(), theDots.end());
}

TEST_CASE("pacman eats the dot on the right when it has dots on the right and it's oriented towards right"){
    string lineBeforeMove =           dots(4) + (char)KindOfToken::Pacman + dots(4);
    string expectedLineAfterMove =    dots(4) + (char)KindOfToken::Empty + (char)KindOfToken::Pacman + dots(3);

    auto lineAfterMove = tick(lineBeforeMove);

    CHECK(lineAfterMove == expectedLineAfterMove);
}
