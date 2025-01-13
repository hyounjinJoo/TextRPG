#include "Shop.h"

#include <iostream>
#include <iomanip>
#include "../Player/Character.h"
#include "../Item/HealthPotion.h" 
#include "../Item/AttackBoost.h" 
#include "../Item/Item.h" 
Shop::Shop()
{
	AvailableItems.push_back(new HealthPotion());
	AvailableItems.push_back(new AttackBoost());
	ItemPrices.push_back(10);	//HealthPotion 가격
	ItemPrices.push_back(10);	//AttackBoost 가격
}

Shop::~Shop()
{
	for (Item* item : AvailableItems)
	{
		delete item;
	}
}

void Shop::DisplayItems(Character* Player)
{
	while (true)
	{
		std::cout << "\n====== 상점에 오신걸 환영합니다! ======\n";
		std::cout << "\n====== 소지하고 있는 아이템 목록 ======\n";
		for (int i = 0; i < AvailableItems.size(); i++)
		{
			Item* item = AvailableItems[i];
			std::cout << std::setw(2) << i + 1 << ". "
				<< item->GetName()
				<< " - "
				<< item->GetItemDescription();
		}
		std::cout << "============================\n";
		std::cout << "소지금: " << Player->GetGold() << " Gold\n";

		std::cout << "\n 행동을 선택해주세요: \n";
		std::cout << "1. 아이템 구매 \n";
		std::cout << "2. 아이템 판매 \n";
		std::cout << "3. 상점 나가기 \n";
		std::cout << "어떤 행동을 하시겠습니까?:  \n";

		int choice;
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			DisplayBuyMenu(Player); //아이템 구매
			break;
		case 2:
			DisplaySellMenu(Player); //아이템 판매
			break;
		case 3:
			std::cout << "상점을 방문해주셔서 감사합니다! \n";
			return;
		default:
		std::cout << "잘못 선택하셨습니다. 다시 선택해주세요. \n";
			break;
		}
	}
}
void Shop::DisplayBuyMenu(Character* Player)
{
}

void Shop::DisplaySellMenu(Character* Player)
{
}

void Shop::BuyItem(int Index, Character* Player)
{
}

void Shop::SellItem(int Index, Character* Player)
{
}