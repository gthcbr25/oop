#include "npc.h"
#include "Visitor.h"
#include "Observer.h"
#include "Factory.h"
#include "World.h"
#include <gtest/gtest.h>
#include <vector>
#include <memory>
#include <sstream>

TEST(NPCTest, CreateAndAccess) {
    Ork ork("Ork1", 10.0f, 20.0f);

    EXPECT_EQ(ork.GetType(), "Ork");
    EXPECT_EQ(ork.GetName(), "Ork1");
    EXPECT_FLOAT_EQ(ork.GetPosX(), 10.0f);
    EXPECT_FLOAT_EQ(ork.GetPosY(), 20.0f);
}

TEST(WorldTest, World) {
    World w(100.0);
    Visitor v;
    ConsoleObserver ob;

    EXPECT_NO_THROW(w.AddCharacter("Ork", "Ork1", 0.0, 0.0));
    EXPECT_NO_THROW(w.AddCharacter("Bear", "Bear1", 0.0, 10.0));

    EXPECT_NO_THROW(v.AddObserver(&ob));

    EXPECT_NO_THROW(w.Engage(v));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}