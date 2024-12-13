#pragma once

#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "npc.h"
#include "Observer.h"

class Visitor {
public:
    void AddObserver(EventObserver* observer) {
        observers.push_back(observer);
    }
    void Engage(std::vector<std::shared_ptr<Character>>& characters) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rng(seed);
        std::uniform_int_distribution dist(1, 6);

        for (size_t i = 0; i < characters.size(); ++i) {
            for (size_t j = i + 1; j < characters.size(); ++j) {
                auto leftChar = characters[i];
                auto rightChar = characters[j];

                if (!leftChar->IsAlive() || !rightChar->IsAlive()) {
                    continue;
                }

                double distance = std::sqrt(std::pow(leftChar->GetPosX() - rightChar->GetPosX(), 2) + std::pow(leftChar->GetPosY() - rightChar->GetPosY(), 2));

                bool leftWon = leftChar->Beats(*rightChar) && distance <= leftChar->GetAttackRange() && dist(rng) > dist(rng);
                bool rightWon = rightChar->Beats(*leftChar) && distance <= rightChar->GetAttackRange() && dist(rng) > dist(rng);

                if (leftWon && rightWon) {
                    Announce(leftChar->GetName() + " and " + rightChar->GetName() + " destroyed each other in deadly battle.");
                    leftChar->Kill();
                    rightChar->Kill();
                }
                else if (leftWon) {
                    Announce(leftChar->GetName() + " attack " + rightChar->GetName());
                    rightChar->Kill();
                }
                else if (rightWon) {
                    Announce(rightChar->GetName() + " attack " + leftChar->GetName());
                    leftChar->Kill();
                }
                else {
                    continue;
                }
            }
        }
    }
private:
    void Announce(const std::string& event) {
        for (auto observer : observers) {
            observer->handleEvent(event);
        }
    }
private:
    std::vector<EventObserver*> observers;
};