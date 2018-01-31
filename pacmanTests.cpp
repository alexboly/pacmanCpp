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

const char to_string(const KindOfToken& token){
    return (char)token;
}

const string to_string(const Line& line){
    string value;
    // This transform doesn't work as expected; it returns empty string
    transform(
            line.begin(), line.end(), value.begin(),
            [](const auto token) {
                return (char)token;
            }
    );
    cout << " to string: " << value << endl;
    return value;
}

void propertyTest(const int dotsBefore, const int dotsAfter){
     cout << "START for dots before: " << dotsBefore << " and dots after " << dotsAfter << endl;
   Line lineBeforeMove =           dots(dotsBefore) + KindOfToken::Pacman + dots(dotsAfter);
    Line expectedLineAfterMove =    dots(dotsBefore) + KindOfToken::Empty + KindOfToken::Pacman + dots(dotsAfter - 1);

    auto lineAfterMove = tick(lineBeforeMove);

    CHECK(lineAfterMove == expectedLineAfterMove);

    cout << " Line before move: " << to_string(lineBeforeMove) << endl;
    cout << " Line after move: " << to_string(lineAfterMove) << endl;
    cout << "DONE for dots before: " << dotsBefore << " and dots after " << dotsAfter << endl;
}

TEST_CASE("pacman eats the dot on the right when it has dots on the right and it's oriented towards right"){
    vector<int> dotsBefore({0, 1, 4});
    vector<int> dotsAfter( {1, 1, 4});

    for(int i = 0; i < dotsBefore.size(); ++i){
        propertyTest(dotsBefore[i], dotsAfter[i]);
    }
}
