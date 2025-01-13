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
		std::cout << "\n | 행동을 선택해주세요: \n";
		std::cout << "| 1. 아이템 구매 \n";
		std::cout << "| 2. 아이템 판매 \n";
		std::cout << "| 3. 상점 나가기 \n";
		std::cout << "| 골드: " << Player->GetGold() << "\n";
		std::cout << "| 어떤 행동을 하시겠습니까?:  \n";

		int Choice;
		std::cin >> Choice;

		switch (Choice)
		{
		case 1:
			DisplayBuyMenu(Player); //아이템 구매
			break; 
		case 2:
			DisplaySellMenu(Player); //아이템 판매
			break;
		case3:
			std::cout<<"| 상점 이용을 종료합니다.\n";
				return;
		default:
		std::cout << "| 다시 어떤 행동을 할지 선택하세요! \n";
			break;
		}
	}
}

void Shop::DisplayBuyMenu(Character* Player)
{
	while (true)
	{
		std::cout << "\n======구매 가능한 아이템 목록======\n";
		for (int i = 0; i < AvailableItems.size(); i++)
		{
			Item* item = AvailableItems[i];
			std::cout <<"| " << std::setw(2) << i + 1 << ". "
				<< item->GetName()
				<< " ("
				<< item->GetItemDescription()
				<< ") "
				<< ": " << ItemPrices[i] << " 골드)";

		}
		std::cout << "| 현재 보유 골드: " << Player->GetGold()<<" \n";
		std::cout << "| 0. 상점메뉴로 이동 \n";
		std::cout << "| 구매할 아이템 번호 입력: ";

		int ItemIndex;
		std::cin >> ItemIndex;

		
		// 1,2 외의 숫자를 눌렀을시 오류 메시지
		if (ItemIndex < 1) 
		{

		}
		else if (ItemIndex < 1 || ItemIndex > AvailableItems.size()) 
		{
			std::cout << "| 다시 어떤 아이템을 구매할 지 선택하세요!\n";
			continue;
		}
		BuyItem(ItemIndex - 1, Player);
		return; // 아이템 한번 구매 후 상점에서 나가기(밸런스 패치)
		
	}
}

void Shop::DisplaySellMenu(Character* Player)
{	
	const std::vector<Item*>& Inventory = Player->GetInventory();

	if (Inventory.empty())
	{
		std::cout << "\n| 현재 아이템이 없습니다!\n";
		return;
	}
	while (true)
	{
		std::cout << "\n====== 판매 가능한 아이템 목록 ======\n";
		for (int i = 0; i < Inventory.size(); i++)
		{
			Item* item = Inventory[i];
			std::cout << std::setw(2) << i + 1 << ". "
						<< item->GetName()
						<< " - "
						<< item->GetItemDescription()
						<< " (판매 가격: " << ItemPrices[i] * 0.6 << " Gold)\n";
		}
		std::cout << "| 판매할 아이템 번호 입력: \n";

		int ItemIndex;
		std::cin >> ItemIndex;

		if (ItemIndex < 1 || ItemIndex > Inventory.size())
		{
			std::cout << "| 다시 어떤 아이템을 팔지 선택해주세요!\n";
			continue;
		}

			SellItem(ItemIndex - 1, Player);
			break;

	}
}

void Shop::BuyItem(int Index, Character* Player)
{
	Item* itemToBuy = AvailableItems[Index];
	
	if (Player->GetGold() < ItemPrices[Index])
	{
		std::cout << "| 구매에 실패했습니다! 골드가 부족합니다! \n";
		return;
	}
	Player->SetGold(Player->GetGold() - ItemPrices[Index]);
	Player->GetInventory().push_back(AvailableItems[Index]);

	std::cout << "| " << AvailableItems[Index]->GetName() << " 아이템을(를) 구매했습니다!\n";
	std::cout << "| 남은 골드: " << Player->GetGold() << " 골드\n";
	std::cout << "| 상점 이용을 종료합니다. \n";
}

void Shop::SellItem(int Index, Character* Player)
{

}