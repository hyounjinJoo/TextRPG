#pragma once
#include "Item.h"

class AttackBoost : public Item
{
public:
    AttackBoost();
    virtual ~AttackBoost();
    
public:
    std::string GetName() const override;
    std::string GetItemDescription() const override;
    void Use(Character* Player, class GameManager* manager) override;

private:
    std::string Name;
    int AttackIncrease;
};
