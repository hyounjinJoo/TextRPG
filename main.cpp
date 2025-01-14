
#include <crtdbg.h>
#include <memory>

#include "Manager/GameManager.h"
#include "Player/Character.h"


#define _CRTDBG_MAP_ALLOC
int main(int argc, char* argv[])
{
	GameManager* Manager = new GameManager();

	bool bNeedContinueBattle = true;
	while(bNeedContinueBattle)
	{
		bNeedContinueBattle = Manager->Battle(Character::GetInstance());
	}

	delete Manager;

	_CrtDumpMemoryLeaks();
	return 0;
}
