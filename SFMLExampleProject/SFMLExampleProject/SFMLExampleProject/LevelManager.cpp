#include "LevelManager.h"
LevelManager* LevelManager::g_LevelManagerRef = NULL;

LevelManager::LevelManager()
{
	currentLevelNum = 1;
}

void LevelManager::LoadLevel(int _LevelNum, Level* _LevelRef)
{
	_LevelRef->UnloadLevel();
	_LevelRef->LoadLevel(LevelList[_LevelNum - 1]);
	SetCurrentLevel(_LevelNum);
}

void LevelManager::SetCurrentLevel(int _Level)
{
	this->currentLevelNum = _Level;
}

void LevelManager::GetCurrentLevel()
{
	std::cout << "The current level is level" << this->currentLevelNum << std::endl;
}

