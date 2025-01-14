#include "AttackBoost.h"

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

void AttackBoost::Use(Character* Player)
{
    int AfterDamage = Player->GetAttack() + AttackIncrease;
    Player->SetAttack(AfterDamage);

    std::cout << "| " << Name << "을(를) 사용 했습니다." << std::endl;
    std::cout << "| " << Player->GetName() << "의 현재 공격력 : " << Player->GetAttack() << std::endl;
}