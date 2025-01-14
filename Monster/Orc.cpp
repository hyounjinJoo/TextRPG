#include <iostream>
#include <random>
#include "Orc.h"
#include "../Item/Item.h"
#include "../Item/AttackBoost.h"
#include "../Item/HealthPotion.h"

using namespace std;

Orc::Orc(int Level) : Name("오크") // 오크 : 전투력이 강하며 공격적인 성격을 가진 몬스터.
{
    // 레벨에 따라 체력과 공격력을 랜덤하게 설정.
    random_device R;
    mt19937 Gen(R());
    uniform_int_distribution<int> DistHealth(20, 30);
    uniform_int_distribution<int> DistAttack(6, 12); // 공격력 증가 최소, 최댓값을 높게 설정.
    int RandomHealth = DistHealth(Gen);
    int RandomAttack = DistAttack(Gen);

    Health = Level * RandomHealth;
    Attack = Level * RandomAttack;

    // 오크 생성시 출력되는 메시지.
    cout << "\n| 오크 : 와아아악!!\n" << endl;
}

Orc::~Orc()
{
    // 오크 소멸시 출력되는 메시지.
    if (Health <= 0)
    {
        cout << "\n| 오크 : 끄어억\n" << endl;
    }
}

const std::string& Orc::GetName() const
{
    // 오크의 이름을 반환.
    return Name;
}

int Orc::GetHealth() const
{
    // 오크의 체력을 반환.
    return Health;
}

int Orc::GetAttack() const
{
    // 오크의 공격력을 반환.
    return Attack;
}

void Orc::TakeDamage(int Damage)
{
    // 데미지를 받아 몬스터의 체력이 감소.
    if (Health > 0)
    {
        Health -= Damage;
    }
}

Item* Orc::DropItem()
{
    // 공격력 증가 포션을 드랍을 할지 결정.
    // 오크의 공격적인 성격을 반영하여 오크의 피로 만든 공격력 증가 포션만 확률적으로 드랍.
    random_device R;
    mt19937 Gen(R());
    uniform_int_distribution<int> DropChance(1, 100);
    int Drop = DropChance(Gen);

    // 아이템 드랍 확률 30%
    if (Drop <= 30)
    {
        return new AttackBoost();
    }
    else
    {
        return nullptr;
    }
}