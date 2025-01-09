#pragma once


class GameManager
{
public:
    GameManager();
    ~GameManager();    
    
    class Monster;
    class BossMonster;
    class Character;
public:
    Monster* GenerateMonster(int Level);
    BossMonster* GenerateBossMonster(int Level);
    void Battle(Character* Player);
    void VisitShop(Character* Player);
    void DisplayInventory(Character* Player);
};
