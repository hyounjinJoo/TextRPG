#pragma once
#include "Item.h"

class AttackBoost : public Item
{
public:
    AttackBoost();
    virtual ~AttackBoost();
    
public:
    std::string GetName() override;
    void Use(Character* Player) override;

private:
    std::string Name;
    int AttackIncrease;
};
