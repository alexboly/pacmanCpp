#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;

const string tick(const string& initialLine){
    return ".... >...";
}

TEST_CASE("pacman eats the dot on the right when it has dots on the right and it's oriented towards right"){
    string lineBeforeMove =           "....>....";
    string expectedLineAfterMove =    ".... >...";

    auto lineAfterMove = tick(lineBeforeMove);

    CHECK(lineAfterMove == expectedLineAfterMove);
}
