#pragma once
#include <string>

class Item;

class Monster
{
public:
    Monster() = default;
    virtual ~Monster() = default;

public:
    virtual const std::string& GetName() const = 0;
    virtual int GetHealth() const = 0;
    virtual int GetAttack() const = 0;
    virtual void TakeDamage(int Damage) = 0;
    virtual Item* DropItem() = 0;
};
