#pragma once
#include <vector>
#include <string>
#include <thread> // EndCredits에서 sleep_for 사용
#include <chrono> // EndCredits에서 시간 관련 기능

class Monster;
class BossMonster;
class Character;
class Item;
class Shop;

namespace
{
	#define ITEM_DROP_CHANCE 30
	#define HEALTH_RECOVERY_THRESHOLD 40

	enum EPotionType
	{
		ITEM_IDX_HEALTHPOTION,
		ITEM_IDX_ATTACKBOOST,
		NONE,
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
		EPotionType UsePotionType;
		std::string UseItemName;
		std::string UseItemDescription;
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
    bool Battle(Character* Player);
    void DisplayInventory(Character* Player);
	void DisplayPlayerStatus(Character* Player);
	void EndCredits(); // 엔딩 크레딧

private:
    void Init();

/* 캐릭터 생성 */
	void CreateCharacter();

/* 전투 관련 */
	bool CanBattle();
	void InitBattle(Character* Player);
	void StartBattle();
	bool EndBattle();
	void InitTurn();
	void PlayTurn();
	void SaveTurn();
	void NextTurn();
	void ReceiveBattleReward();
	void TryTakePotion(Item* RewardItem, EPotionType PostionType);

	Monster* CreateBattleMonster(int PlayerLevel);
	
	void TryUsePotion();
	void UsePotion(std::vector<Item*>& Inventory, EPotionType UsePotionType);
	void TargetAttack(Monster* Attacker, Character* Defender);
	void TargetAttack(Character* Attacker, Monster* Defender);

	void DisplayBattleInfos();
	void DisplayBattleInfo(const FBattleTurnInfo& PrevInfo, const FBattleTurnInfo& CurInfo, int TurnIdx);
	// 플레이어가 살아있는 경우 true 반환, 아닌 경우 false 반환
	bool ReturnAndDisplayBattleResult();

private:
    Character* BattlePlayer;
    Monster* BattleMonster;

	EBattleTurn BattleTurn;
	EBattleResult BattleResult;
	FBattleReward BattleReward;
	std::vector<FBattleTurnInfo> BattleTurnInfos;
	FBattleTurnInfo CurTurnInfo;

/* Shop 관련 */
public:
	void VisitShop(Character* Player);

private:
	Shop* GameShop;
};