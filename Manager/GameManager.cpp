#include "GameManager.h"
#include "../Monster/Monster.h"
#include "../Monster/BossMonster.h"
#include "../Player/Character.h"
#include "../Monster/Troll.h"
#include "../Monster/Orc.h"
#include "../Monster/Goblin.h"
#include <time.h>

GameManager::GameManager()
{
    Init();
}

GameManager::~GameManager()
{

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

}

void GameManager::VisitShop(Character* Player)
{
    
}

void GameManager::DisplayInventory(Character* Player)
{

}
