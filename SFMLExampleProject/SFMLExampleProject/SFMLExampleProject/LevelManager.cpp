#include "LevelManager.h"
LevelManager* LevelManager::g_LevelManagerRef = NULL;

LevelManager::LevelManager()
{
    // Load the current level from the file when the game starts.
    std::ifstream infile("Levels/levelState.txt");
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
    std::ofstream outfile("Levels/levelState.txt");
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


