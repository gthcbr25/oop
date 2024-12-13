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
    Position coords = { 10.0f, 20.0f };
    Ork ork("Ork1", coords.x, coords.y);

    EXPECT_EQ(ork.GetType(), "Ork");
    EXPECT_EQ(ork.GetName(), "Ork1");
    EXPECT_FLOAT_EQ(ork.GetPosX(), 10.0f);
    EXPECT_FLOAT_EQ(ork.GetPosY(), 20.0f);
}

TEST(WorldTest, World) {
    World w;
    Visitor v(10.0);
    ConsoleObserver ob;

    EXPECT_NO_THROW(w.AddCharacter("Ork", "Ork1", 0.0, 0.0));
    EXPECT_NO_THROW(w.AddCharacter("Bear", "Bear1", 0.0, 1.0));

    EXPECT_NO_THROW(v.AddObserver(&ob));

    EXPECT_NO_THROW(w.Engage(v));
}

TEST(FileOperationsTest, SaveAndLoadNPCs) {
    World w;

    w.AddCharacter("Ork", "Ork1", 10.0, 10.0);
    w.AddCharacter("Bear", "Bear2", 30.0, 40.0);

    const std::string filename = "npcs.txt";

    w.Serialize(filename);

    World w2;

    w2.Deserialize(filename);
    auto loaded_npcs = *reinterpret_cast<std::vector<std::shared_ptr<Character>>*>(&w2);
    ASSERT_EQ(loaded_npcs.size(), 2);
    EXPECT_EQ(loaded_npcs[0]->GetType(), "Ork");
    EXPECT_EQ(loaded_npcs[0]->GetName(), "Ork1");
    EXPECT_EQ(loaded_npcs[1]->GetType(), "Bear");
    EXPECT_EQ(loaded_npcs[1]->GetName(), "Bear2");

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}