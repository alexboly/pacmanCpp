#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>

using namespace std;

typedef string Line;

enum class KindOfToken : char {
    Empty = ' ',
    Dot = '.',
    Pacman = '>'
};

const Line before(const Line& line, const char& element){
    const int position = line.find(element);
    return line.substr(0, position);
}

auto beforePacman = [](const Line& line){
    return before(line, '>');
};

const Line after(const Line& line, const char& element){
    const int position = line.find(element);
    return line.substr(position + 1);
}

auto afterPacman = [](const Line& line){
    return after(line, '>');
};

const Line tick(const Line& initialLine){
    const Line afterAfterMove = afterPacman(initialLine).substr(1);
    return beforePacman(initialLine) + ' ' + '>' + afterAfterMove;
}

const Line dots(const int count){
    vector<char> theDots(count, '.');
    return Line(theDots.begin(), theDots.end());
}

TEST_CASE("pacman eats the dot on the right when it has dots on the right and it's oriented towards right"){
    Line lineBeforeMove =           dots(4) + (char)KindOfToken::Pacman + dots(4);
    Line expectedLineAfterMove =    dots(4) + (char)KindOfToken::Empty + (char)KindOfToken::Pacman + dots(3);

    auto lineAfterMove = tick(lineBeforeMove);

    CHECK(lineAfterMove == expectedLineAfterMove);
}
