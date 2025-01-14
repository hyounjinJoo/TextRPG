#pragma once
#include <string>
#include <iostream>
#include "../Player/Character.h"

class Character;

class Item
{
public:
    virtual ~Item() = default;

    virtual std::string GetName() const = 0;
    virtual std::string GetItemDescription() const = 0;
    virtual void Use(Character* Player, class GameManager* manager) = 0;
};
