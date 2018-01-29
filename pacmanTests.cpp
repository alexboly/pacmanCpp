#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;

enum class KindOfToken : char {
    PacmanRight = '>',
    Empty = '\0'
};

string lineOfDots(int dotsCount){
    return "";
}

string makeBoard(string line){
    return "";
}

string tick(string board){
    return "";
}

TEST_CASE("pacman eats the dot on the right when it has dots on the right and it's oriented towards right"){
    int beforeDotsCount = 10;
    int afterDotsCount = 10;
    auto lineWithPacman = lineOfDots(beforeDotsCount) + (char)KindOfToken::PacmanRight + lineOfDots(afterDotsCount);
    auto expectedLineWithPacman = lineOfDots(beforeDotsCount) + (char)KindOfToken::Empty + (char)KindOfToken::PacmanRight + lineOfDots(afterDotsCount - 1);
    auto initialBoard = makeBoard(lineWithPacman);
    auto expectedFinalBoard = makeBoard(expectedLineWithPacman);

    auto boardAfterMove = tick(initialBoard);

    CHECK(boardAfterMove == expectedFinalBoard);

    /*
    beforeDotsCount << (0..<50)
    afterDotsCount << Gen.integer(1..100).take(50)
    totalDotsCount = beforeDotsCount + afterDotsCount + 1
    beforeLineCount << (0..<50)
    afterLineCount << (0..<50)
    makeBoard = this.&makeBoardWithLineWithPacman.curry(beforeLineCount).rcurry(afterLineCount)
    */
}
