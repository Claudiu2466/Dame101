#include <gtest/gtest.h>
#include "state.h"

// Test Constructor implicit
TEST(StateTest, DefaultConstructor) {
    State state;
    EXPECT_EQ(state.GetPlayer(), kValidPlayerO);
}

// Test Constructor cu string
TEST(StateTest, ConstructorWithDataString) {
    State state("OXOXX");
    EXPECT_EQ(state.GetPlayer(), kValidPlayerO);
}

// Test Operator `==`
TEST(StateTest, OperatorEquality) {
    State state1("OXOX");
    State state2("OXOX");

    EXPECT_TRUE(state1 == state2);
}

// Test Metoda `Move`
TEST(StateTest, MovePiece) {
    auto coord1 = std::make_shared<Coord>(2, 2);
    auto coord2 = std::make_shared<Coord>(3, 3);

    Turn turn({coord1, coord2}, false);
    State state("OXOX");
    state.Move(std::make_shared<Turn>(turn));

    EXPECT_EQ(state.GetPlayer(), kValidPlayerX);
}
