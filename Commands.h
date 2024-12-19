#pragma once
#include "Command.h"

class RotateLeftCommand : public Command {
public:
    void execute(Player& player, float deltaTime) override;
};

class RotateRightCommand : public Command {
public:
    void execute(Player& player, float deltaTime) override;
};

class MoveForwardCommand : public Command {
public:
    void execute(Player& player, float deltaTime) override;
};

class ShootCommand : public Command {
public:
    void execute(Player& player, float deltaTime) override;
};
#pragma once
