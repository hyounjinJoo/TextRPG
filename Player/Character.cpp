#include "Character.h"
#include "../Manager/GameManager.h"

Character* Character::Instance = nullptr;

Character::Character(std::string Name) : Name(Name), Level(1), Health(0), MaxHealth(200), Attack(30), Experience(0), Gold(0)
{
    Health = MaxHealth;
    Inventory.resize(2);
}

Character::~Character()
{
    if(Instance)
    {
        Instance = nullptr;
    }

    for (Item* item : Inventory)
    {
        delete item;
        item = nullptr;
    }

    Inventory.clear();
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

// 250113 주현진 수정, Item 사용후 삭제, erase()를 사용하지 않으므로 반드시 아이템 획득 시에는 Item을 생성해서 넣어주시기 바랍니다.
// 수정 이유 - 요구 사항 명세가 변경되었음.
void Character::UseItem(int Index, GameManager* manager)
{
    // HealthPotion, AttackBoost의 범위를 넘어가는 경우에 대한 예외처리
    if(Index < 0 || 1 < Index)
    {
        return;
    }

    std::vector<Item*>& Inventory = Instance->GetInventory();

    // Item이 없는 경우에 대한 예외처리
    if(Inventory.empty())
    {
        return;
    }

    // Item이 해당 인덱스에 없는 경우에 대한 예외처리
    if(!Inventory[Index])
    {
        return;
    }

    Inventory[Index]->Use(Instance, manager);

    // Item 사용후 삭제, erase()를 사용하지 않으므로 반드시 아이템 획득 시에는 Item을 생성해서 넣어주시기 바랍니다.
    delete Inventory[Index];
    Inventory[Index] = nullptr;
}