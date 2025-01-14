#include "Shop.h"

#include <iostream>
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
		std::cout << "\n| 행동을 선택해주세요: \n";
		std::cout << "| 1. 아이템 구매 \n";
		std::cout << "| 2. 아이템 판매 \n";
		std::cout << "| 3. 상점 나가기 \n";
		std::cout << "| 어떤 행동을 하시겠습니까?:  ";

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
		case 3:
			std::cout<<"\n| 상점 이용을 종료합니다.\n";
				return;
		default:
		std::cout << "| 다시 어떤 행동을 할지 선택하세요! \n\n";
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
			std::cout <<"| "  << i + 1 << ". "
				<< item->GetName()
				<< " ("
				<< item->GetItemDescription()
				<< ") "
				<< ": " << ItemPrices[i] << " 골드)";

		}
		std::cout << "| 0. 상점메뉴로 이동 \n";
		std::cout << "| 현재 보유 골드: " << Player->GetGold()<<" \n";
		std::cout << "| 구매할 아이템 번호 입력: ";

		int ItemIndex;
		std::cin >> ItemIndex;

		
		// 1,2 외의 숫자를 눌렀을시 오류 메시지
		if (ItemIndex == 0) 
		{
			return;
		}
		else if (ItemIndex < 1 || ItemIndex > AvailableItems.size()) 
		{
			std::cout << "\n| 다시 어떤 아이템을 구매할 지 선택하세요!\n\n";
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
		std::cout << "| 상점메뉴로 돌아갑니다!\n";
		return;
	}
	while (true)
	{
		std::cout << "\n====== 판매 가능한 아이템 목록 ======\n";
		for (int i = 0; i < Inventory.size(); i++)
		{
			Item* item = Inventory[i];
			std::cout << "| " << i + 1 << ". "
						<< item->GetName()
						<< " - "
						<< item->GetItemDescription()
						<< " (판매 가격: " << ItemPrices[i] * 0.6 << " Gold)\n";
		}
		std::cout << "| 0. 상점메뉴로 이동 \n";
		std::cout << "| 판매할 아이템 번호 입력: ";

		int ItemIndex;
		std::cin >> ItemIndex;
		if (ItemIndex == 0)
		{
			return;
		}
		else if (ItemIndex < 1 || ItemIndex > Inventory.size())
		{
			std::cout << "| 다시 어떤 아이템을 팔지 선택해주세요!\n\n";
			continue;
		}

			SellItem(ItemIndex - 1, Player);
			break;

	}
}

void Shop::BuyItem(int Index, Character* Player)
{
	std::vector<Item*>& Inventory = Player->GetInventory();

	// 중복 확인: 인벤토리 순회하며 동일 아이템이 있는지 검사
	for (Item* item : Inventory)
	{
		if (item == AvailableItems[Index]) // 동일 아이템인지 비교
		{
			std::cout << "| 이미 이 아이템을 보유하고 있습니다. 구매할 수 없습니다!\n";
			return;
		}
	}
	//골드 부족 확인
	if (Player->GetGold() < ItemPrices[Index])
	{
		std::cout << "| 구매에 실패했습니다! 골드가 부족합니다! \n";
		return;
	}

	// 골드 차감 및 인벤토리에 추가
	Player->SetGold(Player->GetGold() - ItemPrices[Index]);
	Player->GetInventory().push_back(AvailableItems[Index]);

	std::cout << "| " << AvailableItems[Index]->GetName() << " 아이템을(를) 구매했습니다!\n";
	std::cout << "| 남은 골드: " << Player->GetGold() << " 골드\n";
	std::cout << "| 상점 메뉴로 돌아갑니다. \n";
}

void Shop::SellItem(int Index, Character* Player)
{
	std::vector<Item*>& Inventory = Player->GetInventory();

	// 유효하지 않은 인덱스 체크
	if (Index < 0 || Index >= Inventory.size())
	{
		std::cout << "|유효하지 않은 아이템 번호입니다! 다시 선택해주세요.\n\n";
		return;
	}

	// 판매 아이템 처리
	Item* itemToSell = Inventory[Index];
	int sellPrice = static_cast<int>(ItemPrices[Index] * 0.6);

	// 골드 추가 및 아이템 제거
	Player->SetGold(Player->GetGold() + sellPrice);
	Inventory.erase(Inventory.begin() + Index);

	std::cout << "| " << itemToSell->GetName() << "을(를) " << sellPrice << " 골드에 판매했습니다!\n";
	delete itemToSell; // 메모리 해제

	std::cout << "| 상점 메뉴로 돌아갑니다.\n";
}