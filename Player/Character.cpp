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

void Character::LevelUp()                                                                               // 레벨업 시 
{
    if (Instance->GetLevel() < 10)                                                                      // 최대 레벨은 10으로 제한
    {
        Instance->SetLevel(Instance->GetLevel() + 1);
        Instance->SetMaxHealth((Instance->GetLevel() * 20) + Instance->GetMaxHealth());                 // 현재 체력 + (레벨 * 20)
        Instance->SetAttack((Instance->GetLevel() * 5) + Instance->GetAttack());                        // 현재 공격력 + (레벨 * 5)
        Instance->SetHealth(Instance->GetMaxHealth());                                                  // 체력 회복
    }
}

void Character::GetExperience(int AddExperience)                                                        // 경험치 획득
{
    Instance->SetExperience(Instance->GetExperience() + AddExperience);
    if (Instance->GetExperience() / 100 > 0)                                                            // 최대 경험치 100, 경험치가 100을 넘어갔을 경우
    {
        for (int i = 0; i < Instance->GetExperience() / 100; i++)                                       // 획득한 경험치가 1레벨 이상 업할 경우
        {
            LevelUp();
        }
        Instance->SetExperience(Instance->GetExperience() % 100);                                       // 남은 경험치
    }
}

void Character::UseItem(int Index)
{
    std::vector<Item*> Inventory = Instance->GetInventory();
    if (!Inventory.empty() && Inventory.size() > Index)                                                 // 인벤토리가 비어있거나 Index가 아이템의 수를 넘어갈 경우
    {
        Inventory[Index]->GetItemDescription();
        Inventory[Index]->Use(Instance);
        Inventory.erase(Inventory.begin() + Index);                                                     // 사용한 아이템 제거
    }
}