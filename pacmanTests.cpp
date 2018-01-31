#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include <algorithm>

using namespace std;

enum class KindOfToken : char {
    Empty = ' ',
    Dot = '.',
    Pacman = '>'
};

typedef vector<KindOfToken> Line;

const Line operator+(const Line& line, const KindOfToken& token){
    Line newLine(line);
    newLine.push_back(token);
    return newLine;
}

const Line operator+(const Line& first, const Line& second){
    Line newLine(first);
    newLine.insert(newLine.end(), second.begin(), second.end());
    return newLine;
}

const Line before(const Line& line, const KindOfToken& element){
    auto position = find(line.begin(), line.end(), element);
    return Line(line.begin(), position);
}

auto beforePacman = [](const Line& line){
    return before(line, KindOfToken::Pacman);
};

const Line after(const Line& line, const KindOfToken& element){
    auto position = find(line.begin(), line.end(), element);
    return Line(position + 1, line.end());
}

auto afterPacman = [](const Line& line){
    return after(line, KindOfToken::Pacman);
};

const Line tick(const Line& initialLine){
    const Line after = afterPacman(initialLine);
    const Line afterAfterMove(after.begin() + 1, after.end());
    return (
            beforePacman(initialLine) + 
            KindOfToken::Empty + 
            KindOfToken::Pacman + 
            afterAfterMove
           );
}

const Line dots(const int count){
    return Line(count, KindOfToken::Dot);
}

const string to_string(const Line& line){
    string value;
    transform(
            line.begin(), line.end(), value.begin(), 
            [](const auto token) {
                return (char)token;
            }
    );
    return value;
}

TEST_CASE("pacman eats the dot on the right when it has dots on the right and it's oriented towards right"){
    Line lineBeforeMove =           dots(4) + KindOfToken::Pacman + dots(4);
    Line expectedLineAfterMove =    dots(4) + KindOfToken::Empty + KindOfToken::Pacman + dots(3);

    auto lineAfterMove = tick(lineBeforeMove);

    CHECK(lineAfterMove == expectedLineAfterMove);
    cout << "Line before move: " << to_string(lineBeforeMove) << endl;
    cout << " Line after move: " << to_string(lineAfterMove) << endl;
}
