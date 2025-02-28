﻿#pragma once
#include <atomic>
#include <string>
#include <thread> // EndCredits에서 sleep_for 사용
#include <chrono> // EndCredits에서 시간 관련 기능
#include <queue>
#include <windows.h> // Beep 함수를 사용하기 위한 헤더 파일

class Monster;
class BossMonster;
class Character;
class Item;
class Shop;

namespace
{
	#define ITEM_DROP_CHANCE 30
	#define HEALTH_RECOVERY_THRESHOLD 0.4f

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

		FBattleTurnInfo()
			: MonsterHP(-1)
			, MonsterAttack(-1)
			, PlayerHP(-1)
			, PlayerAttack(-1)
			, UsePotionType(EPotionType::NONE)
			, BattleTurn(EBattleTurn::End)
		{
		}
	};

	struct FBattleReward
	{
		int Experience;
		int Gold;
		Item* Item;

		FBattleReward()
			: Experience(0)
			, Gold(0)
			, Item(nullptr)
		{
		}
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
	void StartMusic(); // BGM 시작

private:
	std::shared_ptr<std::thread> musicThread;
	std::atomic<bool> stopMusicThread{false};

private:
    void Init();
	void PlayMusic(); // BGM 재생
	void StopMusic();
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

public:
	void PushItemUsingText(std::string Text) { BattleItemUsingTexts.push(Text); }

private:
    Character* BattlePlayer;
    Monster* BattleMonster;

	EBattleTurn BattleTurn;
	EBattleResult BattleResult;
	FBattleReward BattleReward;
	std::vector<FBattleTurnInfo> BattleTurnInfos;
	FBattleTurnInfo CurTurnInfo;
	std::queue<std::string> BattleItemUsingTexts;

/* Shop 관련 */
public:
	void VisitShop(Character* Player);

private:
	Shop* GameShop;

/* 진행 관련 */
public:
	void WaitEnterKeyPressed();
};