#pragma once
#include <SFML/Graphics.hpp>

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(class Player& player, float deltaTime) = 0;
};