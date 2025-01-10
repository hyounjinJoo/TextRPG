#include "AttackBoost.h"

AttackBoost::AttackBoost()
{
}

AttackBoost::~AttackBoost()
{
}

std::string AttackBoost::GetName() const
{
    return this->Name;
}

std::string AttackBoost::GetItemDescription() const
{
    std::string StrItemDescription = "";
    StrItemDescription = Name + " : " + std::to_string(AttackIncrease);

    return StrItemDescription;
}

void AttackBoost::Use(Character* Player)
{
}