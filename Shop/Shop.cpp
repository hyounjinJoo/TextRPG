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

		int Choice;
		std::cin >> Choice;

		switch (Choice)
		{
		case 1:
			DisplayBuyMenu(Player); //아이템 구매
			return; //밸런스 패치로 인한 구매제한
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
	while (true)
	{
		std::cout << "\n======구매 가능한 아이템 목록======\n";
		for (int i = 0; i < AvailableItems.size(); i++)
		{
			Item* item = AvailableItems[i];
			std::cout << std::setw(2) << i + 1 << ". "
				<< item->GetName()
				<< " - "
				<< item->GetItemDescription()
				<< " ( " << ItemPrices[i] << " Gold)";

		}
		std::cout << "소지금: " << Player->GetGold() << " Gold\n";

		std::cout << "0. 상점메뉴로 돌아가기\n";
		std::cout << "구매할 아이템 번호 입력: ";

		int ItemIndex;
		std::cin >> ItemIndex;

		if (ItemIndex == 0)
		{
			return; // 상점 메뉴로 돌아가기
		}
		// 1,2,0 외의 숫자를 눌렀을시 오류 메시지
		else if (ItemIndex < 1 || ItemIndex > AvailableItems.size()) 
		{
			std::cout << "잘못 입력하였습니다. 다시 입력해주세요.\n";
		}
		else
		{
			// 아이템 구매 처리
			if (Player->GetGold() >= ItemPrices[ItemIndex - 1])
			{
				BuyItem(ItemIndex - 1, Player); // 구매 로직 호출
				std::cout << AvailableItems[ItemIndex - 1]->GetName()
					<< " 아이템을 구매하셨습니다!\n";
			}
			else
			{
				std::cout << "소지금이 부족합니다. 아이템을 구매할 수 없습니다.\n";
			}
		}
	}
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