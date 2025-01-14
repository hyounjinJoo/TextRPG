#pragma once
#include<vector>
#include "../Item/Item.h"
#include "../Player/Character.h"
class Character;

class Shop
{
public:
    Shop();
    ~Shop();

public:
    void DisplayItems(Character* Player);
    void DisplayBuyMenu(Character* Player);
    void DisplaySellMenu(Character* Player);
    void BuyItem(int Index, Character* Player);
    void SellItem(int Index, Character* Player);
private:
    std::vector<Item*> AvailableItems;
    std::vector<int> ItemPrices;

};
