#include <iostream>
#include <random>
#include "Troll.h"
#include "../Item/Item.h"
#include "../Item/AttackBoost.h"
#include "../Item/HealthPotion.h"

using namespace std;

Troll::Troll(int Level) : Name("트롤") // 트롤 : 일반적으로 지능은 낮지만 키가 매우 크고 특유의 재생 능력을 가진 강한 몬스터.
{
    // 레벨에 따라 체력과 공격력을 랜덤하게 설정.
    random_device R;
    mt19937 Gen(R());
    uniform_int_distribution<int> DistHealth(30, 35); // 기본 체력이 높다.
    uniform_int_distribution<int> DistAttack(5, 10); // 한방한방의 데미지는 강하지만 지능이 낮고 공격속도가 느려 평균적인 공격력은 기존의 랜덤폭으로 설정. 
    int RandomHealth = DistHealth(Gen);
    int RandomAttack = DistAttack(Gen);

    Health = Level * RandomHealth;
    Attack = Level * RandomAttack;

    // 트롤 생성시 출력되는 메시지.
    cout << "그어어어!!" << endl;
}

Troll::~Troll()
{
	// 트롤 소멸시 출력되는 메시지.
	cout << "그오오억" << endl;
}

const std::string& Troll::GetName() const
{
    // 트롤의 이름을 반환.
    return Name;
}

int Troll::GetHealth() const
{
    // 트롤의 체력을 반환.
    return Health;
}

int Troll::GetAttack() const
{
    // 트롤의 공격력을 반환.
    return Attack;
}

void Troll::TakeDamage(int Damage)
{
    // 데미지를 받아 몬스터의 체력이 감소.
    // 트롤은 질긴 피부를 가지고 있어 데미지 경감 구현.
	if (Health > 0)
	{
		Health = Health - (Damage - 2);
	}
}

Item* Troll::DropItem()
{
    // 체력 회복 포션 드랍을 할지 결정.
    // 트롤의 강한 회복력 반영하여 트롤의 피로 만든 체력 회복 포션만 확률적으로 드랍.
    random_device R;
    mt19937 Gen(R());
    uniform_int_distribution<int> DropChance(1, 100);
    int Drop = DropChance(Gen);

    // 아이템 드랍 확률 30%
    if (Drop <= 30)
    {
        return new HealthPotion();
    }
    else
    {
        return nullptr;
    }
}