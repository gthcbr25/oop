#pragma once

#include <cmath>
#include <vector>
#include <algorithm>

#include "npc.h"
#include "Observer.h"

class Visitor {
public:
    Visitor(double range) : attackRange(range){}

    void AddObserver(EventObserver* observer) {
        observers.push_back(observer);
    }

    void Engage(std::vector<std::shared_ptr<Character>>& characters) {
        for (size_t i = 0; i < characters.size(); ++i) {
            for (size_t j = i + 1; j < characters.size(); ++j) {
                const auto& leftChar = characters[i];
                const auto& rightChar = characters[j];

                if (!leftChar->IsAlive() || !rightChar->IsAlive()) {
                    continue;
                }

                double distance = std::sqrt(std::pow(leftChar->GetPosX() - rightChar->GetPosX(), 2) + std::pow(leftChar->GetPosY() - rightChar->GetPosY(), 2));

                if (distance <= attackRange) {
                    bool leftWon = leftChar->Beats(*rightChar);
                    bool rightWon = rightChar->Beats(*leftChar);

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
    double attackRange;
    std::vector<EventObserver*> observers;
};