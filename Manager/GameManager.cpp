﻿#include "GameManager.h"
#include "../Monster/Monster.h"
#include "../Monster/BossMonster.h"
#include "../Player/Character.h"
#include "../Monster/Troll.h"
#include "../Monster/Orc.h"
#include "../Monster/Goblin.h"
#include "..\Item\HealthPotion.h"
#include "..\Item\AttackBoost.h"
#include <time.h>

GameManager::GameManager()
: BattlePlayer(nullptr), BattleMonster(nullptr)
{
    Init();
}

GameManager::~GameManager()
{
	if (!BattleMonster)
	{
		delete BattleMonster;
	}

	BattleTurnInfos.clear();
}

void GameManager::Init()
{   
	// 난수 초기화
	srand(static_cast<unsigned int>(time(NULL)));
}

Monster* GameManager::GenerateMonster(int Level)
{
	const int MonsterCount = 3;
	int RandNumber = rand() % MonsterCount;

	Monster* CreatedMonster = nullptr;
	switch (RandNumber)
	{
	case 0:
		CreatedMonster = new Orc(Level);
		break;
	case 1:
		CreatedMonster = new Troll(Level);
		break;
	case 2:
		CreatedMonster = new Goblin(Level);
		break;
	default:
		break;
	}

	return CreatedMonster;
}

BossMonster* GameManager::GenerateBossMonster(int Level)
{ 
	return new BossMonster(Level);
}

void GameManager::Battle(Character* Player)
{
	InitBattle(Player);

	if (CanBattle() == false)
		return;

	StartBattle();
	EndBattle();
}

bool GameManager::CanBattle()
{
	if (BattleMonster == nullptr)
	{
		std::cout << "배틀 몬스터가 존재하지 않습니다!" << std::endl;
		return false;
	}
	if (BattlePlayer == nullptr)
	{
		std::cout << "현재 배틀에 참여한 플레이어가 없습니다!" << std::endl;
		return false;
	}

	return true;
}

void GameManager::InitBattle(Character* Player)
{
	if (BattleMonster)
	{
		delete BattleMonster;
		BattleMonster = nullptr;
	}

	if (Player)
	{
		BattleMonster = CreateBattleMonster(Player->GetLevel());
	}

	BattlePlayer = Player;

	// 플레이어 턴 초기화
	BattleTurn = EBattleTurn::PlayerTurn;
	BattleTurnInfos.clear();
}

void GameManager::StartBattle()
{
	// 배틀 시작 시, 초기 플레이어와 몬스터의 정보를 저장합니다.
	SaveTurn();

	while (BattleTurn != EBattleTurn::End)
	{
		PlayTurn();
		SaveTurn();
		NextTurn();
	}
}

void GameManager::EndBattle()
{
	// 배틀 종료 후, 턴별 배틀 정보를 출력합니다.
	DisplayBattleInfos();
	// 배틀 결과에 따라 메시지를 출력합니다.
	DisplayBattleResult();
}

void GameManager::PlayTurn()
{
	switch (BattleTurn)
	{
	case EBattleTurn::PlayerTurn:
		TryUsePotion();
		TargetAttack(BattlePlayer, BattleMonster);
		break;
	case EBattleTurn::MonsterTurn:
		TargetAttack(BattleMonster, BattlePlayer);
		break;
	default:
		break;
	}
}

// 전투 처리와 화면 출력을 분리하고픈 마음에 턴별 데이터를 저장합니다
void GameManager::SaveTurn()
{
	// 화면 출력에 필요한 데이터를 저장합니다.
	FBattleTurnInfo TurnInfo;
	TurnInfo.MonsterHP = BattleMonster->GetHealth();
	TurnInfo.MonsterAttack = BattleMonster->GetAttack();
	TurnInfo.PlayerHP = BattlePlayer->GetHealth();
	TurnInfo.PlayerAttack = BattlePlayer->GetAttack();
	TurnInfo.BattleTurn = BattleTurn;

	BattleTurnInfos.push_back(TurnInfo);
}

// 다음 배틀턴을 설정합니다.
void GameManager::NextTurn()
{
	// 몬스터 체력이 없을 경우, 플레이어 승리 및 턴 종료 
	if (BattleMonster->GetHealth() <= 0)
	{
		BattleResult = EBattleResult::PlayerWin;
		BattleTurn = EBattleTurn::End;
		// 플레이어가 승리할 경우 보상을 획득합니다.
		ReceiveBattleReward();
	}
	// 플레이어 체력이 없을 경우, 몬스터 승리 및 턴 종료 
	else if (BattlePlayer->GetHealth() <= 0)
	{
		BattleResult = EBattleResult::MonsterWin;
		BattleTurn = EBattleTurn::End;
	}
	else
	{
		// 승자가 없을 경우 다음 턴을 계산합니다. (PlayerTurn -> MonsterTurn, MonsterTurn -> PlayerTurn)
		BattleTurn = static_cast<EBattleTurn>((static_cast<int>(BattleTurn) + 1) % static_cast<int>(EBattleTurn::End));
	}
}

// 전투 보상
void GameManager::ReceiveBattleReward()
{
	// 경험치 보상 획득
	{
		int RewardExperience = 50;
		BattlePlayer->GetExperience(RewardExperience);
		BattleReward.Experience = RewardExperience;
	}

	// 골드 보상 획득
	{
		int RewardGold = 10 + (rand() % 10 + 1);
		int TotalGold = BattlePlayer->GetGold() + RewardGold;
		BattlePlayer->SetGold(TotalGold);
		BattleReward.Gold = RewardGold;
	}
	
	// 아이템 보상
	{
		int RandNum = rand() % 100;
		// 아이템 획득 확률을 벗어난 경우 리턴합니다.
		if (RandNum >= ITEM_DROP_CHANCE)  
		{
			return;
		}

		Item* RewardItem = BattleMonster->DropItem();
		// 아이템이 유효하지 않은 경우 리턴합니다.
		if (RewardItem == nullptr)
			return;

		// 아이템 획득을 시도합니다. 
		if (dynamic_cast<HealthPotion*>(RewardItem))
		{
			TryTakePotion(RewardItem, EPotionType::ITEM_IDX_HEALTHPOTION);
		}
		else if (dynamic_cast<AttackBoost*>(BattleReward.Item))
		{
			TryTakePotion(RewardItem, EPotionType::ITEM_IDX_ATTACKBOOST);
		}
	}
}

// 이미 인벤토리에 아이템이 있는지 확인합니다. 
void GameManager::TryTakePotion(Item* RewardItem, EPotionType postionType)
{
	// 소유 중인 아이템이라면 획득한 아이템을 소멸시킵니다.
	if (BattlePlayer->IsExistInInventory(postionType))
	{
		delete RewardItem;
		BattleReward.Item = nullptr;
	}
	// 그렇지 않다면 아이템을 획득합니다.
	else
	{
		std::vector<Item*>& Inventory = BattlePlayer->GetInventory();
		Inventory[postionType] = RewardItem;
	}
}

Monster* GameManager::CreateBattleMonster(int PlayerLevel)
{
	Monster* CreatedMonster = nullptr;
	if (PlayerLevel >= 10)
	{
		CreatedMonster = GenerateBossMonster(PlayerLevel);
	}
	else
	{
		CreatedMonster = GenerateMonster(PlayerLevel);
	}

	return CreatedMonster;
}

/* TODO: 전투 중 포션 사용 */
void GameManager::TryUsePotion()
{

}

void GameManager::TargetAttack(Character* Attacker, Monster* Defender)
{
	// 플레이어 공격, 몬스터의 HP를 수정합니다
	Defender->TakeDamage(Attacker->GetAttack());
}

void GameManager::TargetAttack(Monster* Attacker, Character* Defender)
{
	// 몬스터 공격, 플레이어의 HP를 수정합니다
	int CurrentHealth = std::max(0, Defender->GetHealth() - Attacker->GetAttack());
	Defender->SetHealth(CurrentHealth);
}

void GameManager::DisplayBattleInfos()
{
	// 턴 정보를 화면에 출력하기 위해 최소 2개가 필요합니다.
	// [0] 배틀 시작시 초기 플레이어와 몬스터 정보
	// [1] 배틀 시작후 1턴 이상의 전투 정보
	static const int MIN_TURN_IDX = 2;

 	if (BattleTurnInfos.size() <= MIN_TURN_IDX)
		return;

	for (int TurnIdx = 1; TurnIdx < BattleTurnInfos.size(); ++TurnIdx)
	{
		FBattleTurnInfo& PrevInfo = BattleTurnInfos[TurnIdx - 1];
		FBattleTurnInfo& CurInfo = BattleTurnInfos[TurnIdx];

		DisplayBattleInfo(PrevInfo, CurInfo, TurnIdx);
	}
}


void GameManager::DisplayBattleInfo(const FBattleTurnInfo& PrevInfo, const FBattleTurnInfo& CurInfo, int TurnIdx)
{
	// 첫 턴에는 몬스터의 정보를 출력합니다.
	if (TurnIdx == 1)
	{
		std::cout << "몬스터" << BattlePlayer->GetName() << " 등장! 체력: " << PrevInfo.MonsterHP << ", 공격력: " << PrevInfo.MonsterAttack << std::endl;
		return;
	}

	switch (CurInfo.BattleTurn)
	{
		case EBattleTurn::PlayerTurn:
			if (CurInfo.MonsterHP > 0)
			{
				std::cout << "" << BattlePlayer->GetName() << "이(가) " << BattleMonster->GetName() << "을(를) 공격합니다! " << BattleMonster->GetName() << " 체력: " << CurInfo.MonsterHP << std::endl;
			}
			else
				{
			std::cout << "" << BattlePlayer->GetName() << "이(가) " << BattleMonster->GetName() << "을(를) 공격합니다! " << BattleMonster->GetName() << " 처치!" << std::endl;
			}
			break;
		case EBattleTurn::MonsterTurn:
			if (CurInfo.PlayerHP > 0)
			{
				std::cout << "" << BattleMonster->GetName() << "이(가) " << BattlePlayer->GetName() << "을(를) 공격합니다!" << BattlePlayer->GetName() << "체력: " << CurInfo.PlayerHP << " / " << BattlePlayer->GetMaxHealth() << std::endl;
			}
			else
				{
			std::cout << "" << BattleMonster->GetName() << "이(가) " << BattlePlayer->GetName() << "을(를) 공격합니다!" << BattlePlayer->GetName() << "체력: " << PrevInfo.PlayerHP << "->" << CurInfo.PlayerHP << std::endl;
			}
			break;
		default:
			break;
	}
}

void GameManager::DisplayBattleResult()
{
	std::cout << "==========================전투 결과==========================" << std::endl;

	switch (BattleResult)
	{
		case EBattleResult::PlayerWin:
			// 보스 몬스터일 경우 
			if (dynamic_cast<BossMonster*>(BattleMonster))
			{
				std::cout << "==========================게임 승리!==========================" << std::endl;
				std::cout << "태어난 김에 보스까지 잡았으니 이제 백수가 되었습니다. 이제 현생을 사십시오." << std::endl;
			}
			// 일반 몬스터일 경우
			else
			{
				std::cout << BattlePlayer->GetName() << "이(가) " << BattleReward.Experience << "EXP와 " << BattleReward.Gold << " 골드를 획득했습니다. " << std::endl;
				std::cout << "현재 EXP:" << BattlePlayer->GetExperience() << " / 100 골드: " << BattlePlayer->GetGold() << std::endl;
			}
			break;
		case EBattleResult::MonsterWin:
			std::cout << BattlePlayer->GetName() << "이(가) 사망했습니다. 게임 오버!" << std::endl;
			break;
		default:
			break;
	}
}

void GameManager::VisitShop(Character* Player)
{
    
}

void GameManager::DisplayInventory(Character* Player)
{

}
