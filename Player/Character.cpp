#include "Character.h"

Character* Character::Instance = nullptr;

Character::Character(std::string Name) : Name(Name), Level(1), Health(0), MaxHealth(200), Attack(30), Experience(0), Gold(0)
{
    Health = MaxHealth;
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
    if (Instance->GetLevel() < 10)
    {
        Instance->SetLevel(Instance->GetLevel() + 1);
        Instance->SetMaxHealth((Instance->GetLevel() * 20) + Instance->GetMaxHealth());
        Instance->SetAttack((Instance->GetLevel() * 5) + Instance->GetAttack());
}
}

void Character::GetExperience(int AddExperience)
{
    Instance->SetExperience(Instance->GetExperience() + AddExperience);
    if (Instance->GetExperience() / 100 > 0)
    {
        for (int i = 0; i < Instance->GetExperience() / 100; i++)
{
            LevelUp();
}
        Instance->SetExperience(Instance->GetExperience() % 100);
    }
}

void Character::UseItem(int Index)
{
    std::vector<Item*> Inventory = Instance->GetInventory();
    if (!Inventory.empty() && Inventory.size() > Index)
{
        Inventory[Index]->GetItemDescription();
        Inventory[Index]->Use(Instance);
        Inventory.erase(Inventory.begin() + Index);
    }
}