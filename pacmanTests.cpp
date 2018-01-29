#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>

using namespace std;

enum class KindOfToken : char {
    Empty = ' ',
    Dot = '.',
    Pacman = '>'
};

typedef string Line;

const Line operator+(const Line& line, const KindOfToken& token){
    return line + (char)token;
}

const Line before(const Line& line, const KindOfToken& element){
    const int position = line.find((char)element);
    return line.substr(0, position);
}

auto beforePacman = [](const Line& line){
    return before(line, KindOfToken::Pacman);
};

const Line after(const Line& line, const KindOfToken& element){
    const int position = line.find((char)element);
    return line.substr(position + 1);
}

auto afterPacman = [](const Line& line){
    return after(line, KindOfToken::Pacman);
};

const Line tick(const Line& initialLine){
    const Line afterAfterMove = afterPacman(initialLine).substr(1);
    return beforePacman(initialLine) + KindOfToken::Empty + KindOfToken::Pacman + afterAfterMove;
}

const Line dots(const int count){
    vector<char> theDots(count, (char)KindOfToken::Dot);
    return Line(theDots.begin(), theDots.end());
}

TEST_CASE("pacman eats the dot on the right when it has dots on the right and it's oriented towards right"){
    Line lineBeforeMove =           dots(4) + KindOfToken::Pacman + dots(4);
    Line expectedLineAfterMove =    dots(4) + KindOfToken::Empty + KindOfToken::Pacman + dots(3);

    auto lineAfterMove = tick(lineBeforeMove);

    CHECK(lineAfterMove == expectedLineAfterMove);
}
