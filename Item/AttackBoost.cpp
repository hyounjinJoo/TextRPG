#include "AttackBoost.h"
#include "../Manager/GameManager.h"

AttackBoost::AttackBoost()
{
    Name = "공격력 포션";
    AttackIncrease = 10;
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

void AttackBoost::Use(Character* Player, GameManager* manager)
{
    int AfterDamage = Player->GetAttack() + AttackIncrease;
    Player->SetAttack(AfterDamage);

    manager->PushItemUsingText("| " + Name + "을(를) 사용 했습니다.\n");
    manager->PushItemUsingText("| " + Player->GetName() + "의 현재 공격력 : " + std::to_string(Player->GetAttack()) + "\n");
}