#include "Character.h"

Character* Character::Instance = nullptr;

Character::Character(std::string Name)
{
}

Character::~Character()
{
}

void Character::DisplayStatus()
{
    std::cout << "플레이어 스텟 \n"
        << "Level : " << Instance->GetLevel() << std::endl
        << "체력 : " << Instance->GetHealth() << "/" << Instance->GetMaxHealth() << std::endl
        << "공격력 : " << Instance->GetAttack() << std::endl
        << "경험치 : " << Instance->GetExperience() << std::endl
        << "소지 골드 : " << Instance->GetGold() << std::endl;
}

void Character::LevelUp()
{
}

void Character::UseItem(int Index)
{
}

void Character::VisitShop()
{
}