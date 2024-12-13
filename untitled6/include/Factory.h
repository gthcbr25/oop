#pragma once

#include "npc.h"
#include <memory>
#include <stdexcept>

class Factory {
public:
    static std::shared_ptr<Character> CreateCharacter(const std::string& type, const std::string& name, double x, double y) {
        if (type == "Ork") {
            return std::make_shared<Ork>(name, x, y);
        }
        else if (type == "Knight") {
            return std::make_shared<Knight>(name, x, y);
        }
        else if (type == "Bear") {
            return std::make_shared<Bear>(name, x, y);
        }
        else {
            throw std::invalid_argument("Unknown NPC type: " + type);
        }
    }
};