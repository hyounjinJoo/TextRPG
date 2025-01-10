#pragma once

class Monster;
class BossMonster;
class Character;

class GameManager
{
public:
    GameManager();
    ~GameManager();    

public:
    Monster* GenerateMonster(int Level);
    BossMonster* GenerateBossMonster(int Level);
    void Battle(Character* Player);
    void VisitShop(Character* Player);
    void DisplayInventory(Character* Player);

private:
    void Init();
};
