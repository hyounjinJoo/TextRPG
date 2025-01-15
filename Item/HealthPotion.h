#pragma once
#include "Item.h"

class HealthPotion : public Item
{
public:
    HealthPotion();
    virtual ~HealthPotion();

public:
    std::string GetName() const override;
    std::string GetItemDescription() const override;
    bool Use(Character* Player, class GameManager* manager) override;

private:
    std::string Name;
    int HealthRestore;
};
