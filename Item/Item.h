#pragma once
#include <string>

class Character;

class Item
{
public:
    Item();
    virtual ~Item();

    virtual std::string GetName() = 0;
    virtual void Use(Character* Player) = 0;
};
