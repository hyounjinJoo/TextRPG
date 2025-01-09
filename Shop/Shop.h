#pragma once

class Character;

class Shop
{
public:
    Shop();
    ~Shop();

public:
    void DisplayItems();
    void BuyItem(int Index, Character* Player);
    void SellItem(int Index, Character* Player);
};
