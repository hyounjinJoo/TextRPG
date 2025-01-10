#pragma once
#include "Monster.h"

class Goblin : public Monster
{
public:
    Goblin(int Level);
    virtual ~Goblin();

public:
    const std::string& GetName() const override;
    int GetHealth() const override;
    int GetAttack() const override;
    void TakeDamage(int Damage) override;
    Item* DropItem() override;

private:
    std::string Name;
    int Health;
    int Attack;
};
