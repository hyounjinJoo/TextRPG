#pragma once
#include <string>
#include "../Player/Character.h"

class Character;

class Item
{
public:
    virtual ~Item() = default;

    virtual std::string GetName() = 0;
    virtual void Use(Character* Player) = 0;
};
