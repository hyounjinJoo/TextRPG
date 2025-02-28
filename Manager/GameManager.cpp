﻿#include "GameManager.h"

#include <cassert>

#include "../Monster/Monster.h"
#include "../Monster/BossMonster.h"
#include "../Player/Character.h"
#include "../Monster/Troll.h"
#include "../Monster/Orc.h"
#include "../Monster/Goblin.h"
#include "..\Item\HealthPotion.h"
#include "..\Item\AttackBoost.h"
#include "..\Shop\Shop.h"
#include <time.h>
#include <iostream>
#include <cctype>
#include <conio.h>

#define DELAY_MILLI(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));
#define MAKE_ALERT() std::cout.flush();\
					 std::cout<<'\a';\
					 std::cout.flush();
#define MIN_DURATION 50
#define SHORT_DURATION 100
#define DEFAULT_DURATION 200
#define MID_DURATION 500
#define LONG_DURATION 1000
GameManager::GameManager()
: BattlePlayer(nullptr), BattleMonster(nullptr)
{
    Init();
}

GameManager::~GameManager()
{
	if (BattleMonster)
	{
		delete BattleMonster;
		BattleMonster = nullptr;
	}

	if(GameShop)
	{
		delete GameShop;
		GameShop = nullptr;
	}

	BattleTurnInfos.clear();

	if(BattlePlayer)
	{
		delete BattlePlayer;
		BattlePlayer = nullptr;
	}

	if(musicThread && musicThread->joinable())
	{
		musicThread->join();
	}
}

void GameManager::Init()
{   
	// 난수 초기화
	srand(static_cast<unsigned int>(time(NULL)));
	GameShop = new Shop();
	CreateCharacter();
}

void GameManager::CreateCharacter()
{
	std::string IntroText = "==========================전설의 시작==========================";
	size_t Length = IntroText.length();
	for(size_t IDX = 0; IDX < Length; ++IDX)
	{
		std::cout << IntroText[IDX];
		DELAY_MILLI(MIN_DURATION);
	}
	std::cout << "\n";

	std::cout << "| 이름에는 공백이나 특수문자가 포함될 수 없습니다." << "\n";	DELAY_MILLI(DEFAULT_DURATION);
	std::cout << "| 캐릭터 이름을 입력하세요 : ";
	std::string Name;
	bool bNeedReInputName = false;
	do
	{
		std::getline(std::cin, Name);
		size_t Length = Name.length();
		char Char = NULL;
		bNeedReInputName = false;

		if (Name.empty())
		{
			std::cout << "| 이름의 길이가 0일 수 없습니다. 캐릭터 이름을 다시 입력하세요 : ";
			bNeedReInputName = true;
			continue;
		}

		for (int IDX = 0; IDX < Length; ++IDX)
		{
			Char = Name[IDX];
			if (Char == ' ' || Char == '%' || Char == '/' || Char == '!' || Char == '@' || Char == '#'
				|| Char == '$' || Char == '^' || Char == '&' || Char == '*' || Char == '(' || Char == ')'
				|| Char == '-' || Char == '=' || Char == '+' || Char == '`' || Char == '~' || Char == '['
				|| Char == ']' || Char == '{' || Char == '}' || Char == '\\' || Char == ';' || Char == ':'
				|| Char == '\'' || Char == '\"' || Char == ',' || Char == '.' || Char == '<' || Char == '>'
				|| Char == '?' || Char == '_')
			{
				std::cout << "| 잘못된 입력입니다. 캐릭터 이름을 다시 입력하세요 : ";
				Name = std::string();
				bNeedReInputName = true;
				break;
			}
		}

		if (!bNeedReInputName)
		{
			break;
		}
	} while (bNeedReInputName);

	BattlePlayer = Character::GetInstance(Name);

	DELAY_MILLI(DEFAULT_DURATION);
	std::cout << "| " << BattlePlayer->GetName() << "이(가) 태어났습니다! 레벨 : " << BattlePlayer->GetLevel()
		<< " 체력: " << BattlePlayer->GetHealth() << " 공격력: " << BattlePlayer->GetAttack() << "\n";
	WaitEnterKeyPressed();
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

bool GameManager::Battle(Character* Player)
{
	InitBattle(Player);

	assert(CanBattle());
	StartBattle();
	bool bNeedContinue = EndBattle();

	return bNeedContinue;
}

bool GameManager::CanBattle()
{
	if (BattleMonster == nullptr)
	{
		std::cout << "| 배틀 몬스터가 존재하지 않습니다!" << std::endl;
		return false;
	}
	if (BattlePlayer == nullptr)
	{
		std::cout << "| 현재 배틀에 참여한 플레이어가 없습니다!" << std::endl;
		return false;
	}

	return true;
}

void GameManager::InitBattle(Character* Player)
{
	if (Player)
	{
		BattleMonster = CreateBattleMonster(Player->GetLevel());
		// 플레이어가 유효할 경우 배틀 플레이어를 설정합니다.
		BattlePlayer = Player;
	}

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
		InitTurn();
		PlayTurn();
		SaveTurn();
		NextTurn();
	}
}

bool GameManager::EndBattle()
{
	// 배틀 종료 후, 턴별 배틀 정보를 출력합니다.
	DisplayBattleInfos();

	// 배틀 결과에 따라 메시지를 출력합니다.
	bool bNeedContinue = ReturnAndDisplayBattleResult();
	// 플레이어 상태를 화면에 출력합니다.
	if (bNeedContinue && BattleResult == EBattleResult::PlayerWin)
	{
		DisplayPlayerStatus(BattlePlayer);
	}

	return bNeedContinue;
}

void GameManager::InitTurn()
{
	// 턴 진입전 데이터를 초기화합니다.
	CurTurnInfo.MonsterHP = -1;
	CurTurnInfo.MonsterAttack = -1;
	CurTurnInfo.PlayerAttack = -1;
	CurTurnInfo.PlayerHP = -1;
	CurTurnInfo.UsePotionType = EPotionType::NONE;
	CurTurnInfo.UseItemName.clear();
	CurTurnInfo.UseItemDescription.clear();
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
	CurTurnInfo.MonsterHP = BattleMonster->GetHealth();
	CurTurnInfo.MonsterAttack = BattleMonster->GetAttack();
	CurTurnInfo.PlayerHP = BattlePlayer->GetHealth();
	CurTurnInfo.PlayerAttack = BattlePlayer->GetAttack();
	CurTurnInfo.BattleTurn = BattleTurn;

	BattleTurnInfos.push_back(CurTurnInfo);
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

		std::cout << "| 몬스터가 아이템을 떨어뜨렸습니다. 떨어뜨린 아이템은..." << RewardItem->GetName() << "입니다.\n";

		// 아이템 획득을 시도합니다. 
		if (dynamic_cast<HealthPotion*>(RewardItem))
		{
			TryTakePotion(RewardItem, EPotionType::ITEM_IDX_HEALTHPOTION);
		}
		else if (dynamic_cast<AttackBoost*>(RewardItem))
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
		std::cout << "| 하지만, 이미 소지한 아이템이므로 필요없으니 버립니다.\n";
		delete RewardItem;
		BattleReward.Item = nullptr;
	}
	// 그렇지 않다면 아이템을 획득합니다.
	else
	{
		std::cout << "| 없는 아이템이니 줍고 갑니다.\n";
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

	DELAY_MILLI(DEFAULT_DURATION);
	return CreatedMonster;
}

// 포션은 한 턴에 한 번 사용할 수 있습니다.
void GameManager::TryUsePotion()
{
	std::vector<Item*>& Inventory = BattlePlayer->GetInventory();
	float HealthPercent = static_cast<float>(BattlePlayer->GetHealth()) / BattlePlayer->GetMaxHealth();

	// Health 포션은 체력이 40% 이하인 경우에 사용합니다.
	if (HealthPercent <= HEALTH_RECOVERY_THRESHOLD &&
		BattlePlayer->IsExistInInventory(EPotionType::ITEM_IDX_HEALTHPOTION))
	{
		UsePotion(Inventory, EPotionType::ITEM_IDX_HEALTHPOTION);
	}
	// AttackBoost 포션은 소유하고 있다면 바로 사용합니다.
	else if (BattlePlayer->IsExistInInventory(EPotionType::ITEM_IDX_ATTACKBOOST))
	{
		UsePotion(Inventory, EPotionType::ITEM_IDX_ATTACKBOOST);
	}
}

// 인벤토리의 포션 사용 후 화면 출력을 위해 데이터를 저장합니다.
void GameManager::UsePotion(std::vector<Item*>& Inventory, EPotionType UsePotionType)
{
	CurTurnInfo.UsePotionType = UsePotionType;
	CurTurnInfo.UseItemName = Inventory[UsePotionType]->GetName();
	CurTurnInfo.UseItemDescription = Inventory[UsePotionType]->GetItemDescription();
	BattlePlayer->UseItem(UsePotionType, this);
}

void GameManager::TargetAttack(Character* Attacker, Monster* Defender)
{
	// 플레이어 공격, 몬스터의 HP를 수정합니다
	Defender->TakeDamage(Attacker->GetAttack());
}

void GameManager::TargetAttack(Monster* Attacker, Character* Defender)
{
	// 몬스터 공격, 플레이어의 HP를 수정합니다
	int CurrentHealth = (std::max)(0, Defender->GetHealth() - Attacker->GetAttack());
	Defender->SetHealth(CurrentHealth);
}

void GameManager::DisplayBattleInfos()
{
	// 턴 정보를 화면에 출력하기 위해 최소 2개가 필요합니다.
	// [0] 배틀 시작시 초기 플레이어와 몬스터 정보
	// [1] 배틀 시작후 1턴 이상의 전투 정보
	static const int MIN_TURN_IDX = 2;

 	if (BattleTurnInfos.size() < MIN_TURN_IDX)
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
		std::cout << "| 몬스터 : " << BattleMonster->GetName() << " 등장! 체력: " << PrevInfo.MonsterHP << ", 공격력: " << PrevInfo.MonsterAttack << std::endl;
		DELAY_MILLI(MID_DURATION);
	}

	switch (CurInfo.BattleTurn)
	{
		case EBattleTurn::PlayerTurn:
			// 해당 턴에 포션을 사용하였다면 화면에 출력합니다.
			if (CurInfo.UsePotionType != EPotionType::NONE)
			{
				std::cout << "| " << BattlePlayer->GetName() << "이(가) " << CurInfo.UseItemName << "을(를) 사용합니다! " << CurInfo.UseItemDescription << "!" << std::endl;
				DELAY_MILLI(LONG_DURATION);
				while (!BattleItemUsingTexts.empty())
				{
					std::cout << BattleItemUsingTexts.front();
					BattleItemUsingTexts.pop();
					DELAY_MILLI(MID_DURATION);
				}

				if (CurInfo.UsePotionType == ITEM_IDX_HEALTHPOTION)
				{
					std::cout << "| 플레이어의 현재 체력 : " << CurInfo.PlayerHP << " / " << BattlePlayer->GetMaxHealth() << std::endl;
					DELAY_MILLI(MID_DURATION);
				}
				else if (CurInfo.UsePotionType == ITEM_IDX_ATTACKBOOST)
				{
					std::cout << "| 플레이어의 공격력 : " << CurInfo.PlayerAttack << std::endl;
					DELAY_MILLI(MID_DURATION);
				}
			}
			if (CurInfo.MonsterHP > 0)
			{
				std::cout << "| " << BattlePlayer->GetName() << "이(가) " << BattleMonster->GetName() << "을(를) 공격합니다! " << BattleMonster->GetName() << " 체력: " << CurInfo.MonsterHP << std::endl;
			}
			else
			{
				std::cout << "| " << BattlePlayer->GetName() << "이(가) " << BattleMonster->GetName() << "을(를) 공격합니다! " << BattleMonster->GetName() << " 처치!" << std::endl;
			}
			MAKE_ALERT();
			DELAY_MILLI(MID_DURATION);
			break;
		case EBattleTurn::MonsterTurn:
			if (CurInfo.PlayerHP > 0)
			{
				std::cout << "| " << BattleMonster->GetName() << "이(가) " << BattlePlayer->GetName() << "을(를) 공격합니다! " << BattlePlayer->GetName() << " 체력: " << CurInfo.PlayerHP << " / " << BattlePlayer->GetMaxHealth() << std::endl;
			}
			else
				{
				std::cout << "| " << BattleMonster->GetName() << "이(가) " << BattlePlayer->GetName() << "을(를) 공격합니다! " << BattlePlayer->GetName() << " 체력: " << PrevInfo.PlayerHP << "->" << CurInfo.PlayerHP << std::endl;
			}
			DELAY_MILLI(MID_DURATION);
			break;
		default:
			break;
	}
}

bool GameManager::ReturnAndDisplayBattleResult()
{
	bool bBattleMonsterIsBoss = false;
	// 몬스터 사망 처리
	if (BattleMonster && BattleResult == EBattleResult::PlayerWin)
	{
		if(dynamic_cast<BossMonster*>(BattleMonster))
		{
			bBattleMonsterIsBoss = true;
		}

		// 플레이어가 승리한 보상을 획득합니다.
		ReceiveBattleReward();
		delete BattleMonster;
		BattleMonster = nullptr;

		WaitEnterKeyPressed();
	}

	system("cls");
	if (!bBattleMonsterIsBoss)
	{
		std::cout << "==========================전투 결과==========================" << std::endl;
	}

	bool bResult = false;
	switch (BattleResult)
	{
		case EBattleResult::PlayerWin:
			// 보스 몬스터일 경우 
			if (bBattleMonsterIsBoss)
			{
				std::cout << "==========================게임 승리!==========================" << std::endl;
				std::cout << "| 태어난 김에 보스까지 잡았으니 이제 백수가 되었습니다.\n";
				std::cout << "| 이제 현생을 사십시오.\n";
				StopMusic();
				WaitEnterKeyPressed();
				EndCredits();
			}
			// 일반 몬스터일 경우
			else
			{
				bResult = true;
				std::cout << "| " << BattlePlayer->GetName() << "이(가) " << BattleReward.Experience << " EXP와 " << BattleReward.Gold << " 골드를 획득했습니다. " << std::endl;
				std::cout << "| 현재 EXP:" << BattlePlayer->GetExperience() << " / 100 골드: " << BattlePlayer->GetGold() << std::endl;
			}
			break;
		case EBattleResult::MonsterWin:
			{
				std::string GameOverSTR = BattlePlayer->GetName() + "이(가) 사망했습니다. 게임 오버!\n";
				size_t Length = GameOverSTR.length();
				UINT DefaultMilli = 100;
				for (size_t IDX = 0; IDX < Length; ++IDX)
				{
					std::cout << GameOverSTR[IDX];
					DELAY_MILLI(DefaultMilli);
				}

				for(int Iter = 0; Iter < 20; ++Iter)
				{
					std::cout << "\n";
				}
				StopMusic();
				WaitEnterKeyPressed();
			}
			break;
		default:
			break;
	}

	return bResult;
}

// 인벤토리를 화면에 출력합니다.
void GameManager::DisplayInventory(Character* Player)
{
	// 플레이어가 유효한지 확인합니다.
	if (Player == nullptr)
		return;

	std::vector<Item*>& Inventory = Player->GetInventory();

	std::cout << "==========================인벤토리==========================" << std::endl;
	// 인벤토리가 비어있는지 확입합니다.
	if (Inventory.empty())
	{
		std::cout << "| 현재 아이템이 없습니다." << std::endl;
	}
	else
	{
		for (int idx = 0; idx < Inventory.size(); ++idx)
		{
			std::cout << "|" << idx << ". " << Inventory[idx]->GetItemDescription() << std::endl;
		}
	}
}

void GameManager::DisplayPlayerStatus(Character* Player)
{
	if (Player == nullptr)
		return;

	std::cout << "========================플레이어 정보========================" << std::endl;
	std::cout << "| 레벨 : " << Player->GetLevel() << std::endl;
	std::cout << "| 이름 : " << Player->GetName() << std::endl;
	std::cout << "| 공격력 : " << Player->GetAttack() << std::endl;
	std::cout << "| 체력 : " << Player->GetHealth() << " / " << Player->GetMaxHealth() << std::endl;
	std::cout << "| 골드 : " << Player->GetGold() << std::endl;
	std::cout << "| 경험치 : " << Player->GetExperience() << " / " << 100 << std::endl;
}


// 엔딩 크레딧
void GameManager::EndCredits()
{
	// 멤버 역할과 이름.
	std::cout << "[Credit]\n";
	std::vector<std::string> Members = {
	"| Project Manager : 주현진",
	"| Game Manager 제작 : 김동현",
	"| Shop 제작 : 심홍기",
	"| Character 제작 : 최지한",
	"| Item 제작 : 김건우",
	"| Monster 제작 : 김도훈",
	"| 제작 지원 도움 및 영혼의 구심점 및 그저 왕 : 최민성 튜터님",
	"| 총 제작기간 : 25.01.10 ~ 25.01.16(5일)\n",
	"[제작 환경]",
	"| IDE : MicroSoft Visual Studio Community 2022",
	"| Language : ISO C++14 Standard",
	"| Source Control : Git & GitHub",
	"| 작업 기록 : Notion",
	"| 작업 장소 : 자택, Zep",
	"| Special Thanks : Google.com"};

	// 각 멤버별로 한 글자씩 출력하고 다음 멤버 출력시 줄바꿈.
	for (const std::string& Member : Members) {  // 벡터의 각 요소 순회
		for (char C : Member) {				// 문자열의 각 문자 순회
			std::cout << C;                 // 한 글자씩 출력
			if (' ' != C && '\n' != C)
			{
				Beep(520, 50);
				Beep(340, 10);
			}
			std::cout.flush();              // 버퍼를 강제로 비우기
			std::this_thread::sleep_for(std::chrono::milliseconds(50));    // 150ms 대기
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(150));    // 줄 간격 대기
		std::cout << "\n"; // 줄 바꿈
	}
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
	WaitEnterKeyPressed();
}

// 상점 방문 구현
void GameManager::VisitShop(Character* Player)
{
	if (Player == nullptr)
		return;

	std::string YesNo;
	static int EasterEgg = 1;
	int haha = 1;
	std::string NormalSTR =    "==========================상점 방문==========================\n";
	std::string EasterEggSTR = "==========================상점 방문========아니좀제대로입력해===\n";
	std::string PrintSTR = NormalSTR;
	while (true)
	{
		std::cout << PrintSTR;
		std::cout << "| 상점을 방문하시겠습니까? (Y/N) : ";

		std::cin.clear();
		std::cin >> YesNo;

		if(YesNo == "Y" || YesNo == "y")
		{
			GameShop->DisplayItems(Player);
			system("cls");
			return;
		}
		else if(YesNo == "N" || YesNo == "n")
		{
			system("cls");
			return;
		}
		else
		{
			std::cout << "| Y 또는 N을 입력해 주세요." << std::endl;
			DELAY_MILLI(LONG_DURATION);
			system("cls");
			if(EasterEgg++ >= haha)
			{
				EasterEgg = 1;
				std::cout << "히히 오줌발싸!\n";
				DELAY_MILLI(SHORT_DURATION);
				system("cls");
				PrintSTR = EasterEggSTR;
				std::cout << PrintSTR;
				DELAY_MILLI(DEFAULT_DURATION);
				system("cls");
				PrintSTR = NormalSTR;
			}
			else
			{
				PrintSTR = NormalSTR;
			}
		}		
	}
}

void GameManager::WaitEnterKeyPressed()
{
	std::cout << "| 계속하려면 엔터키를 입력하세요";

	int Limit = 5;
	int Count = 0;
	while(true)
	{
		if(Count++ < Limit)
			std::cout << ".";

		DELAY_MILLI(SHORT_DURATION)
		if(_kbhit() && _getch() == '\r')
		{
			system("cls");
			break;
		}
	}
}

void GameManager::StartMusic() {
	musicThread = std::make_shared<std::thread>(&GameManager::PlayMusic, this); // playMusic을 별도 스레드에서 실행
}

// Zelda - Song of Time
void GameManager::PlayMusic() {
	while (!stopMusicThread.load()) { // 무한 반복
		Beep(880, 400);  // A5 1-2
		Beep(587, 900);  // D5 1
		Beep(698, 400);  // F5 1-2
		Beep(880, 400);  // A5 1-2
		Beep(587, 900);  // D5 1
		Beep(698, 400);  // F5 1-2
		Beep(880, 150);  // A5 1-4
		Beep(1046, 250); // C6 1-4
		Beep(987, 400);  // B5 1-2
		Beep(783, 400);  // G5 1-2
		Beep(698, 150);  // F5 1-4
		Beep(783, 250);  // G5 1-4
		Beep(880, 400);  // A5 1-2
		Beep(587, 400);  // D5 1
		Beep(523, 150);  // C5 1-4
		Beep(659, 150);  // E5 1-4
		Beep(587, 950);  // D5 3-4
		Sleep(800);
	}
}

void GameManager::StopMusic()
{
	stopMusicThread.store(true);
}