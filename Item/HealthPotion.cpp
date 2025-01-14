#include "HealthPotion.h"

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

void HealthPotion::Use(Character* Player)
{
    int CurrentHP = Player->GetHealth();
    int HealthHP = CurrentHP + HealthRestore;;

    if (CurrentHP >= Player->GetMaxHealth())
    {
        std::cout << "| " << Player->GetName() << "은(는) 회복 물약을 먹을 필요가 없습니다." << std::endl;
        std::cout << "| 사용이 취소 되었습니다." << std::endl;
        return;
    }

    if (HealthHP > Player->GetMaxHealth())
    {
        std::cout << "| " << Player->GetName() << "은(는) HP " << std::to_string(HealthHP - Player->GetMaxHealth()) << " 을 회복했습니다. " << std::endl;
        
        HealthHP = Player->GetMaxHealth();
        Player->SetHealth(HealthHP);
    }
    else
    {
        std::cout << "| " << Player->GetName() << "은(는) HP " << HealthRestore << " 을 회복했습니다. " << std::endl;
        Player->SetHealth(HealthHP);
    }
}