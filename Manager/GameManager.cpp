#include "GameManager.h"
#include "../Monster/Monster.h"
#include "../Monster/BossMonster.h"
#include "../Player/Character.h"
#include "../Monster/Troll.h"
#include "../Monster/Orc.h"
#include "../Monster/Goblin.h"
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
	while (BattleTurn != EBattleTurn::End)
	{
		PlayTurn();
		SaveTurn();
		NextTurn();
	}
}

void GameManager::EndBattle()
{
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

void GameManager::VisitShop(Character* Player)
{
    
}

void GameManager::DisplayInventory(Character* Player)
{

}
