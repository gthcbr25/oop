#pragma once

#include <vector>

#include "Factory.h"
#include "npc.h"
#include "Visitor.h"

class World {
public:
    void AddCharacter(const std::string& type, const std::string& name, double x, double y) {
        characters.push_back(Factory::CreateCharacter(type, name, x, y));
    }
    void AnounceFighters() const {
        for (const auto& c : characters) {
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
private:
    std::vector<std::shared_ptr<Character>> characters;
};