#include "Object.h"
#include "Troop.h"
#include "LevelManager.h"
#include "Board.h"
// ALWAYS BUILD IN RELEASE, AT LEAST ONCE A DAY. 

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game!");
    window.setFramerateLimit(60);

    Board* pBoard = new Board();

    Troop* pSoldier = new Troop("Troops/Soldier.txt");
    Troop* pGiant = new Troop("Troops/Giant.txt");

    pSoldier->PrintStats();
    pGiant->PrintStats();

    LevelManager* g_LevelManager = LevelManager::GetInstance();
    LevelManager::GetInstance()->GetCurrentLevel();
    
    // creates level instance and loads level based on supplied text file
    Level level;
    level.LoadLevel("Levels/level1.txt");

    // creates instance of terrain tiles
    Terrain* terrain = new Terrain();
    terrain->SetWindowRef(&window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num1)
                {
                    LevelManager::GetInstance()->LoadLevel(1, &level);
                    //g_LevelManager->LoadLevel(1, &level);
                }

                if (event.key.code == sf::Keyboard::Num2)
                {
                    LevelManager::GetInstance()->LoadLevel(2, &level);
                    //g_LevelManager->LoadLevel(2, &level);
                }

                if (event.key.code == sf::Keyboard::Num3)
                {
                    LevelManager::GetInstance()->LoadLevel(3, &level);
                    //g_Level   ->LoadLevel(3, &level);
                }
            }
            pSoldier->PlaceTroop(event, &window);
        }
        pBoard->ShowMouseSquare(&window);

        window.clear();

        //drawing
        window.draw(terrain->Draw());
        level.Draw(&window);
        window.draw(pSoldier->GetSprite());
        window.draw(pBoard->GetSelectRect());

        window.display();
    }

    return 0;
}