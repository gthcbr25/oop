#pragma once

#include <vector>

#include "Factory.h"
#include "npc.h"
#include "Visitor.h"
#include <random>
#include <chrono>

class World {
public:
    World(double size) : worldSize(size) {}
    void AddCharacter(const std::string& type, const std::string& name, double x, double y) {
        characters.push_back(Factory::CreateCharacter(type, name, x, y));
    }
    void AnounceFighters() const {
        for (const auto& c : characters) {
            if (!c->IsAlive())
                continue;

            std::cout << c->GetType() << " '" << c->GetName() << "' ("
                << c->GetPosX() << ", " << c->GetPosY() << ")\n";
        }
    }
    void Serialize(const std::string& filename) const {
        std::ofstream fs(filename);
        for (const auto& c : characters) {
            fs << c->GetType() << " " << c->GetName() << " "
                << c->GetPosX() << " " << c->GetPosY() << "\n";
        }
    }
    void Deserialize(const std::string& filename) {
        std::ifstream fs(filename);
        std::string type, name;
        double x, y;
        while (fs >> type >> name >> x >> y) {
            AddCharacter(type, name, x, y);
        }
    }
    void Engage(Visitor& visitor) {
        visitor.Engage(characters);
    }
    void MoveCharacters() {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rng(seed);
        std::uniform_real_distribution dist(-1.0, 1.0);

        for (auto c : characters) {
            Vec2 dir = Vec2{ dist(rng), dist(rng) };
            c->Move(dir);

            c->SetPosition(Vec2{ std::clamp(c->GetPosX(), 0.0, worldSize), std::clamp(c->GetPosY(), 0.0, worldSize) });
        }
    }
    void PrintMap() const {
        int xSize = int(worldSize);
        int ySize = int(worldSize);

        for (int i = 0; i <= xSize + 2; ++i) {
            std::cout << '-';
        }
        std::cout << '\n';

        for (int i = 0; i <= ySize; ++i) {
            std::cout << '|';
            for (int j = 0; j <= xSize; ++j) {
                bool printed = false;
                for (auto c : characters) {
                    if (!c->IsAlive())
                        continue;

                    printed = true;
                    if ((int)c->GetPosX() == j && (int)c->GetPosY() == i) {
                        if (c->GetType() == "Ork") {
                            std::cout << '#';
                            break;
                        }
                        else if (c->GetType() == "Knight") {
                            std::cout << '*';
                            break;
                        }
                        else if (c->GetType() == "Bear") {
                            std::cout << '@';
                            break;
                        }
                    }
                    else {
                        printed = false;
                    }
                }
                if (!printed) {
                    std::cout << ' ';
                }
            }
            std::cout << '|';
            std::cout << '\n';
        }

        for (int i = 0; i <= xSize + 2; ++i) {
            std::cout << '-';
        }
        std::cout << '\n';
    }
    double GetSize() const {
        return worldSize;
    }
private:
    double worldSize;
    std::vector<std::shared_ptr<Character>> characters;
};