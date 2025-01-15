#pragma once
#include <string>
#include <iostream>
#include "../Player/Character.h"

class Character;

class Item
{
public:
    virtual ~Item() = default;

    virtual std::string GetName() const = 0;
    virtual std::string GetItemDescription() const = 0;
    // 250115 주현진 수정, 아이템을 사용할 필요가 없는 경우 false를 반환하도록 수정
    // 수정 사유 - 아이템이 사용할 필요가 없는데 삭제하지 않도록 하기 위해서
    virtual bool Use(Character* Player, class GameManager* manager) = 0;
};
