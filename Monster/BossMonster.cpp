#include <iostream>
#include <random>
#include "BossMonster.h"
#include "../Item/Item.h"
#include "../Item/AttackBoost.h"
#include "../Item/HealthPotion.h"

using namespace std;

BossMonster::BossMonster(int Level) : Name("투명드래곤") // 투명드래곤 : 드래곤중에서도 최강의 투명드래곤이 울부짓었다. 투명드래곤은 졸라짱쎄서 드래곤중에서 최강이엇다.
{
    // 레벨에 따라 체력과 공격력을 랜덤하게 설정.
    random_device R;
    mt19937 Gen(R());
    uniform_int_distribution<int> DistHealth(30, 45); // 보스 몬스터의 체력은 기존 몬스터의 1.5배 범위를 랜덤으로 설정.
    uniform_int_distribution<int> DistAttack(7.5, 15); // 보스 몬스터의 공격력은 기존 몬스터의 1.5배 범위를 랜덤으로 설정.
    int RandomHealth = DistHealth(Gen);
    int RandomAttack = DistAttack(Gen);

    Health = Level * RandomHealth;
    Attack = Level * RandomAttack;

    // 투명드래곤 생성시 출력되는 메시지.
    cout << "크아아아아" << endl;

}

BossMonster::~BossMonster()
{
    // 투명드래곤 소멸시 출력되는 메시지.
    cout << "크아아아악" << endl;
}

const std::string& BossMonster::GetName() const
{
    // 투명드래곤의 이름을 반환.
    return Name;
}

int BossMonster::GetHealth() const
{
    // 투명드래곤의 체력을 반환.
    return Health;
}

int BossMonster::GetAttack() const
{
    // 투명드래곤의 공격력을 반환.
    return Attack;
}

void BossMonster::TakeDamage(int Damage)
{
    // 데미지를 받아 몬스터의 체력이 감소.
    if (Health > 0)
    {
        Health -= Damage;
    }
}

Item* BossMonster::DropItem()
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