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

/* 전투 관련 */
	bool CanBattle();
	void InitBattle(Character* Player);
	void StartBattle();
	void EndBattle();

	Monster* CreateBattleMonster(int PlayerLevel);

private:
    Character* BattlePlayer;
    Monster* BattleMonster;
};