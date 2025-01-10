#include "GameManager.h"
#include "../Monster/Monster.h"
#include "../Monster/BossMonster.h"
#include "../Player/Character.h"
#include "../Monster/Troll.h"
#include "../Monster/Orc.h"
#include "../Monster/Goblin.h"
#include "../Monster/BossMonster.h"
#include <time.h>

GameManager::GameManager()
{
    Init();
}

void GameManager::Init()
{   
	// 난수 초기화
	srand(time(NULL));
}

GameManager::Monster* GameManager::GenerateMonster(int Level)
{

}

GameManager::BossMonster* GameManager::GenerateBossMonster(int Level)
{ 
    
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


