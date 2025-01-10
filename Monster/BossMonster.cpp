#include "BossMonster.h"

BossMonster::BossMonster(int level)
{
}

BossMonster::~BossMonster()
{
}

const std::string& BossMonster::GetName() const
{

    return std::string();
}

int BossMonster::GetHealth() const
{

    return 0;
}

int BossMonster::GetAttack() const
{

    return 0;
}

void BossMonster::TakeDamage(int Damage)
{
}

Item* BossMonster::DropItem()
{

    return nullptr;
}