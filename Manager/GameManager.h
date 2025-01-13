#pragma once
#include <vector>

class Monster;
class BossMonster;
class Character;
class Item;

namespace
{
	#define ITEM_DROP_CHANCE 30

	enum EPotionType
	{
		ITEM_IDX_HEALTHPOTION,
		ITEM_IDX_ATTACKBOOST,
	};

	enum EBattleResult
	{
		PlayerWin,
		MonsterWin, 
	};

	enum EBattleTurn
	{
		PlayerTurn,
		MonsterTurn,
		End,
	};

	struct FBattleTurnInfo
	{
		int MonsterHP;
		int MonsterAttack;
		int PlayerHP;
		int PlayerAttack;
		EBattleTurn BattleTurn;
	};

	struct FBattleReward
	{
		int Experience;
		int Gold;
		Item* Item;
	};
}

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
	void ReceiveBattleReward();
	void TryTakePotion(Item* RewardItem, EPotionType PostionType);

	Monster* CreateBattleMonster(int PlayerLevel);

	void TryUsePotion();
	void TargetAttack(Monster* Attacker, Character* Defender);
	void TargetAttack(Character* Attacker, Monster* Defender);

	void DisplayBattleInfos();
	void DisplayBattleInfo(const FBattleTurnInfo& PrevInfo, const FBattleTurnInfo& CurInfo, int TurnIdx);
	void DisplayBattleResult();

private:
    Character* BattlePlayer;
    Monster* BattleMonster;

	EBattleTurn BattleTurn;
	EBattleResult BattleResult;
	FBattleReward BattleReward;
	std::vector<FBattleTurnInfo> BattleTurnInfos;
};