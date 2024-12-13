#include "World.h"
#include "Observer.h"
#include "Visitor.h"
#include <random>
#include <chrono>

int main() {
    World world;
    Visitor visitor(50.0);
    ConsoleObserver consoleObserver;
    FileObserver fileObserver("log.txt");

    visitor.AddObserver(&consoleObserver);
    visitor.AddObserver(&fileObserver);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::uniform_real_distribution dist(0.0, 500.0);

    std::uniform_int_distribution int_dist(0, 2);

    const char* types[] = {"Bear", "Ork", "Knight"};
    for (int i = 0; i < 50; ++i) {

        std::string type = types[int_dist(rng)];

        world.AddCharacter(type, type + " " + std::to_string(i), dist(rng), dist(rng));
    }

    std::cout << "Fighters" << std::endl;
    world.AnounceFighters();
    std::cout << std::endl;

    world.Engage(visitor);

    world.Deserialize("dungeon.txt");

    return 0;
}