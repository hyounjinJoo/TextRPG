#include "HealthPotion.h"
#include "../Manager/GameManager.h"

HealthPotion::HealthPotion()
{
    Name = "체력 회복 포션";
    HealthRestore = 50;
}

HealthPotion::~HealthPotion()
{
}

std::string HealthPotion::GetName() const
{
    return Name;
}

std::string HealthPotion::GetItemDescription() const
{
    std::string StrItemDescription = "";
    StrItemDescription = Name + " : " + std::to_string(HealthRestore);

    return StrItemDescription;
}

bool HealthPotion::Use(Character* Player, GameManager* manager)
{
    int CurrentHP = Player->GetHealth();
    int HealthHP = CurrentHP + HealthRestore;;

    // 사용할 필요가 없으므로 false return
    if (CurrentHP >= Player->GetMaxHealth())
    {
        manager->PushItemUsingText("| " + Player->GetName() + "은(는) 회복 물약을 먹을 필요가 없습니다.\n");
        manager->PushItemUsingText("| 사용이 취소 되었습니다.\n");
        return false;
    }

    if (HealthHP > Player->GetMaxHealth())
    {
        manager->PushItemUsingText("| " + Player->GetName() + "은(는) HP " + std::to_string(HealthHP - Player->GetMaxHealth()) + " 을 회복했습니다.\n");
        
        HealthHP = Player->GetMaxHealth();
        Player->SetHealth(HealthHP);
    }
    else
    {
        manager->PushItemUsingText("| " + Player->GetName() + "은(는) HP " + std::to_string(HealthRestore) + " 을 회복했습니다.\n");
        Player->SetHealth(HealthHP);
    }

    return true;
}