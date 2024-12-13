#include "World.h"
#include "Observer.h"
#include "Visitor.h"
#include <random>
#include <chrono>
#include <atomic>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <array>

std::atomic<bool> gameIsRunning{ true };
std::shared_mutex npc_mutex;

int main() {
    World world(50.0);
    Visitor visitor;
    ConsoleObserver consoleObserver;
    FileObserver fileObserver("log.txt");

    visitor.AddObserver(&consoleObserver);
    visitor.AddObserver(&fileObserver);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::uniform_real_distribution dist(0.0, world.GetSize());

    std::uniform_int_distribution int_dist(0, 2);

    {
        const char* types[] = { "Ork", "Knight", "Bear" };
        std::array<int, 3> counters = { 0, 0, 0 };
        for (int i = 0; i < world.GetSize() / 3; ++i) {
            int rand = int_dist(rng);
            std::string type = types[rand];

            world.AddCharacter(type, type + " " + std::to_string(counters[rand]++), dist(rng), dist(rng));
        }
    }

    std::cout << "Fighters in dungeon:\n";
    std::cout << "------------------------------------------------------------------" << std::endl;
    {
        std::shared_lock lock(npc_mutex);
        world.AnounceFighters();
    }
    std::cout << "------------------------------------------------------------------" << std::endl;

    // moving
    std::thread movement_thread([&]() {
        while (gameIsRunning) {
            {
                std::unique_lock lock(npc_mutex);
                world.MoveCharacters();
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    std::thread battle_thread([&]() {
        while (gameIsRunning) {
            {
                std::unique_lock lock(npc_mutex);
                world.Engage(visitor);
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    std::thread display_thread([&]() {
        while (gameIsRunning) {
            {
                std::unique_lock lock(npc_mutex);
                world.PrintMap();
            }
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    });

    std::this_thread::sleep_for(std::chrono::seconds(30));
    gameIsRunning = false;

    movement_thread.join();
    battle_thread.join();
    display_thread.join();

    std::cout << "\nRemaining Fighters:\n";
    std::cout << "------------------------------------------------------------------" << std::endl;
    {
        std::shared_lock lock(npc_mutex);
        world.PrintMap();
        world.AnounceFighters();
    }
    std::cout << "------------------------------------------------------------------" << std::endl;

    return 0;
}