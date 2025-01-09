#include "Goblin.h"

Goblin::Goblin()
{
}

Goblin::~Goblin()
{
}

const std::string& Goblin::GetName() const
{

    return std::string();
}

int Goblin::GetHealth() const
{
    
    return 0;
}

int Goblin::GetAttack() const
{

    return 0;
}

void Goblin::TakeDamage(int Damage)
{
}

Item* Goblin::DropItem()
{

    return nullptr;
}