#include "Orc.h"

Orc::Orc()
{
}

Orc::~Orc()
{
}

const std::string& Orc::GetName() const
{

    return std::string();
}

int Orc::GetHealth() const
{

    return 0;
}

int Orc::GetAttack() const
{

    return 0;
}

void Orc::TakeDamage(int Damage)
{
}

Item* Orc::DropItem()
{

    return nullptr;
}