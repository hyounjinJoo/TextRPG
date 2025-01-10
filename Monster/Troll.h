#pragma once
#include "Monster.h"

class Troll : public Monster
{
public:
    Troll(int level);
    virtual ~Troll();

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
