#include "../Player/Character.h"
#include "Goblin.h"
#include <iostream>

using namespace std;

Goblin::Goblin(int level) : Name("고블린"), Health(0), Attack(0)
{
    // 고블린의 체력과 공격력을 설정 중입니다.
    // Character* character = Character::GetInstance();
    // Health = character -> GetLevel() * 20;
    // Attack = character-> GetLevel() * 5;
}

Goblin::~Goblin()
{
    cout << "끼에엑" << endl;
}

const std::string& Goblin::GetName() const
{
    return std::string(Name);
}

int Goblin::GetHealth() const
{
    return Health;
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