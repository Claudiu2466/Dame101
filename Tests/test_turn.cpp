#include <gtest/gtest.h>
#include "turn.h"
#include <memory>

// Test Constructor implicit
TEST(TurnTest, DefaultConstructor) {
    Turn turn;
    EXPECT_FALSE(turn.Capture());
}

// Test Constructor cu parametrii
TEST(TurnTest, ConstructorWithParams) {
    auto coord1 = std::make_shared<Coord>(1, 2);
    auto coord2 = std::make_shared<Coord>(3, 4);
    std::vector<std::shared_ptr<Coord>> coords = {coord1, coord2};

    Turn turn(coords, true);
    EXPECT_TRUE(turn.Capture());
    EXPECT_EQ(turn.Coords().size(), 2);
}

// Test Operator de atribuire
TEST(TurnTest, CopyConstructor) {
    auto coord1 = std::make_shared<Coord>(1, 2);
    auto coord2 = std::make_shared<Coord>(3, 4);
    std::vector<std::shared_ptr<Coord>> coords = {coord1, coord2};

    Turn original(coords, true);
    Turn copy = original;

    EXPECT_TRUE(copy.Capture());
    EXPECT_EQ(copy.Coords().size(), 2);
}

// Test Operator `==`
TEST(TurnTest, OperatorEquality) {
    auto coord1 = std::make_shared<Coord>(2, 3);
    auto coord2 = std::make_shared<Coord>(4, 5);
    std::vector<std::shared_ptr<Coord>> coords = {coord1, coord2};

    Turn turn1(coords, false);
    Turn turn2(coords, false);

    EXPECT_TRUE(turn1 == turn2);
}
