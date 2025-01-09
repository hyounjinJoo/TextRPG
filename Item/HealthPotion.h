#pragma once
#include "Item.h"

class HealthPotion : public Item
{
public:
    HealthPotion();
    virtual ~HealthPotion();

public:
    std::string GetName() override;
    void Use(Character* Player) override;

private:
    std::string Name;
    int HealthRestore;
};
