#pragma once

namespace
{
	enum EBattleTurn
	{
		PlayerTurn,
		MonsterTurn,
		End,
	};
};

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
	void PlayTurn();
	void SaveTurn();
	void NextTurn();

	Monster* CreateBattleMonster(int PlayerLevel);

	void TryUsePotion();
	void TargetAttack(Monster* Attacker, Character* Defender);
	void TargetAttack(Character* Attacker, Monster* Defender);

private:
    Character* BattlePlayer;
    Monster* BattleMonster;

	EBattleTurn BattleTurn;
};