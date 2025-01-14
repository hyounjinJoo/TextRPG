#include <iostream>
#include <random>
#include "Goblin.h"
#include "../Item/Item.h"
#include "../Item/AttackBoost.h"
#include "../Item/HealthPotion.h"

using namespace std;

Goblin::Goblin(int Level) : Name("고블린")
{
    // 레벨에 따라 체력과 공격력을 랜덤하게 설정.
    random_device R;
    mt19937 Gen(R());
    uniform_int_distribution<int> DistHealth(20, 30);
    uniform_int_distribution<int> DistAttack(5, 10);
    int RandomHealth = DistHealth(Gen);
    int RandomAttack = DistAttack(Gen);

    Health = Level * RandomHealth;
    Attack = Level * RandomAttack;

    // 고블린 생성시 출력되는 메시지.
    cout << "| 고블린 : 낄낄낄" << endl;
}

Goblin::~Goblin()
{
    // 고블린 소멸시 출력되는 메시지.
    if (Health <= 0)
    {
        cout << "| 고블린 : 끼에엑" << endl;
    }
}

const std::string& Goblin::GetName() const
{
	// 고블린의 이름을 반환.
    return Name;
}

int Goblin::GetHealth() const
{
	// 고블린의 체력을 반환.
    return Health;
}

int Goblin::GetAttack() const
{
	// 고블린의 공격력을 반환.
    return Attack;
}

void Goblin::TakeDamage(int Damage)
{
	// 데미지를 받아 몬스터의 체력이 감소.
    if (Health > 0)
    {
        Health -= Damage;
    }
}

Item* Goblin::DropItem()
{
    // 체력 회복 포션과 공격력 증가 포션을 랜덤하게 드랍.
    random_device R;
    mt19937 Gen(R());
    uniform_int_distribution<int> DropChance(1, 100);
    uniform_int_distribution<int> ItemType(0, 1);
    int Drop = DropChance(Gen);

    // 아이템 드랍 확률 30%
    if (Drop <= 30)
    {
        if (ItemType(Gen) == 0)
        {
            return new HealthPotion();
        }
        else
        {
            return new AttackBoost();
        }
    }
    else
    {
        return nullptr;
    }
}