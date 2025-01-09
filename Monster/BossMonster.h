#pragma once
#include "Monster.h"

class BossMonster : public Monster
{
public:
    BossMonster();
    virtual ~BossMonster();
    
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
