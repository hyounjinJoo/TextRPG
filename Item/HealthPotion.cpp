#include "HealthPotion.h"

HealthPotion::HealthPotion()
{
}

HealthPotion::~HealthPotion()
{
}

std::string HealthPotion::GetName() const
{
    return Name;
}

std::string HealthPotion::GetItemDescription() const
{
    std::string StrItemDescription = "";
    StrItemDescription = Name + " : " + std::to_string(HealthRestore);

    return StrItemDescription;
}

void HealthPotion::Use(Character* Player)
{
}