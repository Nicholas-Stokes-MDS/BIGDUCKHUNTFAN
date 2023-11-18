#include "LevelManager.h"
LevelManager* LevelManager::g_LevelManagerRef = NULL;

LevelManager::LevelManager()
{
    // Load the current level from the file when the game starts.
    std::ifstream infile("Levels/currentLevel.txt");
    if (infile.is_open())
    {
        infile >> this->currentLevelNum;
        infile.close();
    }
    else
    {
        // If the file does not exist, start at level 1.
        this->currentLevelNum = 1;
    }

    std::ifstream infile2("Levels/gameType.txt");
    if (infile2.is_open())
    {
        infile2 >> this->gameType;
        infile2.close();
    }
    else
    {
        // If the file does not exist
        this->currentLevelNum = 0;
    }
}

void LevelManager::LoadLevel(int _LevelNum, Level* _LevelRef)
{
    _LevelRef->UnloadLevel();
    _LevelRef->LoadLevel(LevelList[_LevelNum - 1]);
    SetCurrentLevel(_LevelNum);
    std::cout << "The current level is level " << this->currentLevelNum << std::endl;
}

void LevelManager::SetCurrentLevel(int _Level)
{
    this->currentLevelNum = _Level;

    // Save the current level to a file.
    std::ofstream outfile("Levels/currentLevel.txt");
    if (outfile.is_open())
    {
        outfile << this->currentLevelNum;
        outfile.close();
    }
}

void LevelManager::PrintCurrentLevel()
{
    std::cout << "The current level is level " << this->currentLevelNum << std::endl;
}

int LevelManager::GetCurrentLevel()
{
    return this->currentLevelNum;
}

void LevelManager::SetGameType(int _gameType)
{
    this->gameType = _gameType;

    // Save the current gameType to a file.
    std::ofstream outfile("Levels/gameType.txt");
    if (outfile.is_open())
    {
        outfile << this->gameType;
        outfile.close();
    }
}

int LevelManager::GetGameType()
{
    return this->gameType;
}


