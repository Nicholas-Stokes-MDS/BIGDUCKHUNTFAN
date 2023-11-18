#include "Object.h"
#include "Troop.h"
#include "LevelManager.h"
#include "Board.h"
#include "UIElement.h"
#include <SFML/Audio.hpp>
#include <algorithm>
// ALWAYS BUILD IN RELEASE, AT LEAST ONCE A DAY. 
enum PlacingTroop
{
    PlacingNone,
    PlacingSoldier,
    PlacingArcher,
    PlacingScout,
    PlacingGiant,
    PlacingBoat,
    PlacingShield,
};

int PlaceTroop(Board* _Player, std::string _TroopPath, sf::Event _event, sf::RenderWindow* _WindowRef, Board* _EnemyPlayer, Level _level)
{
    // assume space is valid
    bool bAvailableSpace = false;
    // change the select rectangle to grey
    _Player->SetMouseColour(sf::Color(255, 255, 255, 128));

    if (_Player->m_bIsComputer)
    {
        Troop* pTroop = new Troop(_TroopPath);
        pTroop->PlaceComputerTroop();
        _Player->AddTroop(pTroop);
        return 1;
    }

    // if mouse button pressed create a troop instance
    if (_event.type == sf::Event::MouseButtonPressed)
    {
        if (_event.mouseButton.button == sf::Mouse::Left)
        {
            Troop* pTroop = new Troop(_TroopPath);

            // only move if on suitable terrain
            if (pTroop->GetName() == "Boat")
            {
                for (int i = 0; i < _level.m_LevelTiles.size(); i++)
                {
                    if (_level.m_LevelTiles[i]->m_TerrainType == Water)
                    {
                        if (_Player->GetSelectRect().getGlobalBounds().intersects(_level.m_LevelTiles[i]->m_CharacterSprite.getGlobalBounds()))
                        {
                            bAvailableSpace = true;
                        }
                    }
                }
            }
            else
            {
                for (int i = 0; i < _level.m_LevelTiles.size(); i++)
                {
                    if (_level.m_LevelTiles[i]->m_TerrainType == Wall)
                    {
                        if (_Player->GetSelectRect().getGlobalBounds().intersects(_level.m_LevelTiles[i]->m_CharacterSprite.getGlobalBounds()))
                        {
                            bAvailableSpace = true;
                            std::cout << "wall" << std::endl;
                        }
                    }
                }
            }

            // make sure area is not own troop member ! has to be after the tile checks !
            for (auto it = _Player->m_Troops.begin(); it != _Player->m_Troops.end(); /* no increment here */)
            {
                for (auto& playerTroop : _Player->m_Troops)
                {
                    if (_Player->GetSelectRect().getGlobalBounds().intersects((*it)->GetSprite().getGlobalBounds()))
                    {
                        bAvailableSpace = false;
                    }
                }
                it++;
            }

            // make sure area is not enemy troop member ! has to be after the tile checks !
            for (auto it = _EnemyPlayer->m_Troops.begin(); it != _EnemyPlayer->m_Troops.end(); /* no increment here */)
            {
                for (auto& playerTroop : _Player->m_Troops)
                {
                    if (_Player->GetSelectRect().getGlobalBounds().intersects((*it)->GetSprite().getGlobalBounds()))
                    {
                        bAvailableSpace = false;
                    }
                }
                it++;
            }

            // actually place troop
            if (bAvailableSpace)
            {
                pTroop->PlaceTroop(_event, _WindowRef);
                _Player->AddTroop(pTroop);
                // return 1 to count the troops placed
                return 1;
            }
            else
            {
                // change the rectangle to red
                _Player->SetMouseColour(sf::Color(255, 0, 0, 128));
            }
        }
    }
    return 0;
}

int main()
{
    // initialize random seed
    srand(time(0));

    bool g_bGameRunning = true;

    while (g_bGameRunning)
    {
        sf::SoundBuffer laugh;
        laugh.loadFromFile("laugh.wav");
        //if (!laugh.loadFromFile("laugh.wav"))
        //{
        //    std::cout << "Error loading file" << std::endl;
        //}
        sf::Sound sound;
        sound.setBuffer(laugh);
        sound.play();

        // menu
        sf::Font* UIElementFont = new sf::Font();
        if (!UIElementFont->loadFromFile("BRLNSR.TTF"))
        {
            std::cout << "Error loading file" << std::endl;
        }

        sf::RenderWindow window(sf::VideoMode(800, 600), "Game!");
        window.setFramerateLimit(60);
        window.setVerticalSyncEnabled(true);

        std::vector<UIElement> MenuElements;
        // creation of buttons
        UIElement SinglePlayer(sf::Vector2f(300, 30), sf::Vector2f(150, 50), std::string("SinglePlayer"), UIElementFont, sf::Color::Black);
        MenuElements.push_back(SinglePlayer);
        UIElement TwoPlayer(sf::Vector2f(300, 100), sf::Vector2f(150, 50), std::string("TwoPlayer"), UIElementFont, sf::Color::Black);
        MenuElements.push_back(TwoPlayer);
        UIElement Instruction1(sf::Vector2f(50, 170), sf::Vector2f(700, 50), std::string("1.Use the buttons on the troop panel to place your troops"), UIElementFont, sf::Color::Black);
        MenuElements.push_back(Instruction1);
        UIElement Instruction2(sf::Vector2f(50, 220), sf::Vector2f(700, 50), std::string("2.Click on a troop to move them"), UIElementFont, sf::Color::Black);
        MenuElements.push_back(Instruction2);
        UIElement Instruction3(sf::Vector2f(50, 270), sf::Vector2f(700, 50), std::string("3.Once each troop has been moved or the end turn button has been"), UIElementFont, sf::Color::Black);
        MenuElements.push_back(Instruction3);
        UIElement Instruction4(sf::Vector2f(50, 320), sf::Vector2f(700, 50), std::string("   pressed, troops deal damage to each other."), UIElementFont, sf::Color::Black);
        MenuElements.push_back(Instruction4);
        UIElement Instruction5(sf::Vector2f(50, 370), sf::Vector2f(700, 50), std::string("4.If a troop is adjacent to another troop, those troops will give"), UIElementFont, sf::Color::Black);
        MenuElements.push_back(Instruction5);
        UIElement Instruction6(sf::Vector2f(50, 420), sf::Vector2f(700, 50), std::string("   each other plus one damage (non stackable). "), UIElementFont, sf::Color::Black);
        MenuElements.push_back(Instruction6);
        UIElement Instruction7(sf::Vector2f(50, 470), sf::Vector2f(700, 50), std::string("5.Strategically move your troops to defeat all the opponent troops."), UIElementFont, sf::Color::Black);
        MenuElements.push_back(Instruction7);
        
        LevelManager::GetInstance()->SetGameType(0);
        while (LevelManager::GetInstance()->GetGameType() == 0)
        {
            while (window.isOpen() && LevelManager::GetInstance()->GetGameType() == 0)
            {
                sf::Event menu;
                while (window.pollEvent(menu) && LevelManager::GetInstance()->GetGameType() == 0)
                {
                    if (menu.type == sf::Event::Closed)
                    {
                        window.close();
                    }

                    if (menu.type == sf::Event::MouseButtonPressed)
                    {
                        if (menu.mouseButton.button == sf::Mouse::Left)
                        {
                            //clicking buttons in Options window and calling the appropriate class method
                            // Single Player
                            if (MenuElements[0].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                            {
                                LevelManager::GetInstance()->SetGameType(1);
                            }
                            // Two player
                            if (MenuElements[1].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                            {
                                LevelManager::GetInstance()->SetGameType(2);
                            }
                        }
                    }


                }
                // Menu render loop
                window.clear();
                // draw UI elements of menu
                for (int i = 0; i < MenuElements.size(); i++)
                {
                    MenuElements[i].Draw(&window);
                }
                window.display();
                // Settings window render loop

            }
        }

        PlacingTroop TroopPlaced = PlacingNone;
        Troop* pMovingTroop = new Troop("");
        //bool g_bPlacingSoldier = true;
        bool bMovingTroop = false;

        bool g_bLevelFinished = false;
        bool g_bPlayer1Won = false;
        bool g_bPlayer2Won = false;

        bool g_bTroopsPlaced = false;
        int g_iTroopsPlaced = 0;
        int g_iTroopCounts[6]{};
        for (int i = 0; i < 6; i++)
        {
            if (LevelManager::GetInstance()->GetCurrentLevel() == 1)
            {
                g_iTroopCounts[i] = LevelManager::GetInstance()->g_iLevel1Troops[i];
            }
            else if (LevelManager::GetInstance()->GetCurrentLevel() == 2)
            {
                g_iTroopCounts[i] = LevelManager::GetInstance()->g_iLevel2Troops[i];
            }
            else if (LevelManager::GetInstance()->GetCurrentLevel() == 3)
            {
                g_iTroopCounts[i] = LevelManager::GetInstance()->g_iLevel3Troops[i];
            }
        }

        int g_iTurns = 0;
        int g_iPlayer = 1;

        sf::RenderWindow OptionsWindow(sf::VideoMode(400, 400), "Place troops");
        OptionsWindow.setVerticalSyncEnabled(true);

        sf::RenderWindow Settings(sf::VideoMode(400, 400), "Settings");
        Settings.setVerticalSyncEnabled(true);

        LevelManager* g_LevelManager = LevelManager::GetInstance();
        LevelManager::GetInstance()->GetCurrentLevel();

        // creates level instance and loads level based on supplied text file
        Level level;
        //level.LoadLevel("Levels/level1.txt");

        // creates instance of terrain tiles
        Terrain* terrain = new Terrain();
        terrain->SetWindowRef(&window);

        // These objects handle player actions
        Board* pPlayer1 = new Board(level, 1, false);
        Board* pPlayer2 = new Board(level, 2, false);

        if (LevelManager::GetInstance()->GetGameType() == 1)
        {
            pPlayer2->m_bIsComputer = true;
        }

        Board* pCurrentPlayer = pPlayer1;
        Board* pCurrentEnemy = pPlayer2;

        // UI stuff
        // vector for buttons
        std::vector<UIElement> UIElements;
        // creation of buttons
        UIElement UISoldier(sf::Vector2f(50, 30), sf::Vector2f(100, 50), std::string("Soldier (") + std::to_string(g_iTroopCounts[5]) + std::string(")"), UIElementFont, sf::Color::Black);
        UIElements.push_back(UISoldier);
        UIElement UIArcher(sf::Vector2f(50, 100), sf::Vector2f(100, 50), std::string("Archer (") + std::to_string(g_iTroopCounts[0]) + std::string(")"), UIElementFont, sf::Color::Black);
        UIElements.push_back(UIArcher);
        UIElement UIShield(sf::Vector2f(50, 170), sf::Vector2f(100, 50), std::string("Shield (") + std::to_string(g_iTroopCounts[4]) + std::string(")"), UIElementFont, sf::Color::Black);
        UIElements.push_back(UIShield);
        UIElement UIScout(sf::Vector2f(50, 240), sf::Vector2f(100, 50), std::string("Scout (") + std::to_string(g_iTroopCounts[3]) + std::string(")"), UIElementFont, sf::Color::Black);
        UIElements.push_back(UIScout);
        UIElement UIBoat(sf::Vector2f(50, 310), sf::Vector2f(100, 50), std::string("Boat (") + std::to_string(g_iTroopCounts[1]) + std::string(")"), UIElementFont, sf::Color::Black);
        UIElements.push_back(UIBoat);
        UIElement UIGiant(sf::Vector2f(250, 30), sf::Vector2f(100, 50), std::string("Giant (") + std::to_string(g_iTroopCounts[2]) + std::string(")"), UIElementFont, sf::Color::Black);
        UIElements.push_back(UIGiant);
        UIElement UIdeselect(sf::Vector2f(250, 100), sf::Vector2f(100, 50), std::string("deselect"), UIElementFont, sf::Color::Black);
        UIElements.push_back(UIdeselect);

        std::vector<UIElement> UIElements2;
        // creation of buttons
        UIElement volume1Element(sf::Vector2f(20, 30), sf::Vector2f(150, 50), std::string("Volume+"), UIElementFont, sf::Color::Black);
        UIElements2.push_back(volume1Element);
        UIElement volume2Element(sf::Vector2f(20, 100), sf::Vector2f(150, 50), std::string("Volume-"), UIElementFont, sf::Color::Black);
        UIElements2.push_back(volume2Element);
        UIElement vsync1Element(sf::Vector2f(20, 170), sf::Vector2f(150, 50), std::string("Vsync Enable"), UIElementFont, sf::Color::Black);
        UIElements2.push_back(vsync1Element);
        UIElement vsync2Element(sf::Vector2f(20, 240), sf::Vector2f(150, 50), std::string("Vsync Disable"), UIElementFont, sf::Color::Black);
        UIElements2.push_back(vsync2Element);
        UIElement resolution1Element(sf::Vector2f(20, 310), sf::Vector2f(150, 50), std::string("800 by 600"), UIElementFont, sf::Color::Black);
        UIElements2.push_back(resolution1Element);
        UIElement resolution2Element(sf::Vector2f(220, 30), sf::Vector2f(150, 50), std::string("1366 by 768"), UIElementFont, sf::Color::Black);
        UIElements2.push_back(resolution2Element);
        UIElement resolution3Element(sf::Vector2f(220, 100), sf::Vector2f(150, 50), std::string("1920 by 1080"), UIElementFont, sf::Color::Black);
        UIElements2.push_back(resolution3Element);

        std::vector<UIElement> PlayerTurn;
        UIElement Player1Element(sf::Vector2f(165, 480), sf::Vector2f(150, 50), std::string("Player 1's turn"), UIElementFont, sf::Color::Blue);
        PlayerTurn.push_back(Player1Element);
        UIElement Player2Element(sf::Vector2f(165, 480), sf::Vector2f(150, 50), std::string("Player 2's turn"), UIElementFont, sf::Color::Red);
        PlayerTurn.push_back(Player2Element);
        UIElement EndTurn(sf::Vector2f(330, 480), sf::Vector2f(150, 50), std::string("End Turn"), UIElementFont, sf::Color::Black);
        PlayerTurn.push_back(EndTurn);
        UIElement LevelNumber(sf::Vector2f(0, 480), sf::Vector2f(150, 50), std::string("Level: ") + std::to_string(LevelManager::GetInstance()->GetCurrentLevel()), UIElementFont, sf::Color::Black);
        PlayerTurn.push_back(LevelNumber);
        UIElement Win(sf::Vector2f(0, 540), sf::Vector2f(150, 50), std::string("Player 1 wins"), UIElementFont, sf::Color::Blue);
        PlayerTurn.push_back(Win);
        UIElement Lose(sf::Vector2f(0, 540), sf::Vector2f(150, 50), std::string("Player 2 wins"), UIElementFont, sf::Color::Red);
        PlayerTurn.push_back(Lose);
        UIElement NextLevel(sf::Vector2f(165, 540), sf::Vector2f(150, 50), std::string("Next level"), UIElementFont, sf::Color::Black);
        PlayerTurn.push_back(NextLevel);
        UIElement Restart(sf::Vector2f(330, 540), sf::Vector2f(150, 50), std::string("Restart"), UIElementFont, sf::Color::Black);
        PlayerTurn.push_back(Restart);

        //LevelNumber(std::string("End Turn"))



        //UIElement PlayerTurn[3](sf::Vector2f(0, 480), sf::Vector2f(150, 50), std::string("Level: ") + std::to_string(LevelManager::GetInstance()->GetCurrentLevel()), UIElementFont, sf::Color::Black);

        if (LevelManager::GetInstance()->GetCurrentLevel() == 1)
        {
            level.LoadLevel("Levels/level1.txt");
        }
        else if (LevelManager::GetInstance()->GetCurrentLevel() == 2)
        {
            level.LoadLevel("Levels/level2.txt");
        }
        else if (LevelManager::GetInstance()->GetCurrentLevel() == 3)
        {
            level.LoadLevel("Levels/level3.txt");
        }

        level.PrintTerrainType();

        pPlayer1->SetLevel(level);
        pPlayer2->SetLevel(level);

        while (window.isOpen())
        {
            sf::Event event;

            // -- main event loop -- //
            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Num1)
                    {
                        LevelManager::GetInstance()->LoadLevel(1, &level);
                        level.PrintTerrainType();
                    }

                    else if (event.key.code == sf::Keyboard::Num2)
                    {
                        LevelManager::GetInstance()->LoadLevel(2, &level);
                        level.PrintTerrainType();
                    }

                    else if (event.key.code == sf::Keyboard::Num3)
                    {
                        LevelManager::GetInstance()->LoadLevel(3, &level);
                        level.PrintTerrainType();
                    }

                    else if (event.key.code == sf::Keyboard::Num7)
                    {

                    }

                    else if (event.key.code == sf::Keyboard::Num8)
                    {

                    }

                    else if (event.key.code == sf::Keyboard::Num9)
                    {
                        sound.play();
                    }
                    break;
                default:
                    break;
                }

                // placing troops
                if (!g_bTroopsPlaced)
                {
                    g_bLevelFinished = false;
                    // check which player placing troops
                    if (g_iPlayer == 1)
                    {
                        // say player 1 placing
                        pCurrentPlayer = pPlayer1;
                        pCurrentEnemy = pPlayer2;
                    }
                    else if (g_iPlayer == 2)
                    {
                        // say player 2 placing
                        pCurrentPlayer = pPlayer2;
                        pCurrentEnemy = pPlayer1;


                    }

                    // placing troop if button pressed
                    switch (TroopPlaced)
                    {
                        // troop created based on button
                    case PlacingNone:
                        break;
                    case PlacingSoldier:
                        // count number of troops placed every time new troop placed
                        // only allow placing as many as are in the level troop array
                        if (g_iTroopCounts[5] > 0)
                        {
                            g_iTroopCounts[5] -= PlaceTroop(pCurrentPlayer, "Troops/Soldier.txt", event, &window, pCurrentEnemy, level);
                        }
                        break;
                    case PlacingArcher:
                        if (g_iTroopCounts[0] > 0)
                        {
                            g_iTroopCounts[0] -= PlaceTroop(pCurrentPlayer, "Troops/Archer.txt", event, &window, pCurrentEnemy, level);
                        }
                        break;
                    case PlacingScout:
                        if (g_iTroopCounts[3] > 0)
                        {
                            g_iTroopCounts[3] -= PlaceTroop(pCurrentPlayer, "Troops/Scout.txt", event, &window, pCurrentEnemy, level);
                        }
                        break;
                    case PlacingGiant:
                        if (g_iTroopCounts[2] > 0)
                        {
                            g_iTroopCounts[2] -= PlaceTroop(pCurrentPlayer, "Troops/Giant.txt", event, &window, pCurrentEnemy, level);
                        }
                        break;
                    case PlacingBoat:
                        if (g_iTroopCounts[1] > 0)
                        {
                            g_iTroopCounts[1] -= PlaceTroop(pCurrentPlayer, "Troops/Boat.txt", event, &window, pCurrentEnemy, level);
                        }
                        break;
                    case PlacingShield:
                        if (g_iTroopCounts[4] > 0)
                        {
                            g_iTroopCounts[4] -= PlaceTroop(pCurrentPlayer, "Troops/Shield.txt", event, &window, pCurrentEnemy, level);
                        }
                        break;
                    default:
                        break;
                    }

                    int iTotalTroops = 0;
                    // get total number of troops to be placed
                    for (int count = 0; count < 6; count++)
                    {
                        iTotalTroops += g_iTroopCounts[count];
                    }
                    // stop placing troops if all troops placed
                    if (iTotalTroops == 0)
                    {
                        TroopPlaced = PlacingNone;
                        for (int i = 0; i < 6; i++)
                        {
                            if (LevelManager::GetInstance()->GetCurrentLevel() == 1)
                            {
                                g_iTroopCounts[i] = LevelManager::GetInstance()->g_iLevel1Troops[i];
                            }
                            else if (LevelManager::GetInstance()->GetCurrentLevel() == 2)
                            {
                                g_iTroopCounts[i] = LevelManager::GetInstance()->g_iLevel2Troops[i];
                            }
                            else if (LevelManager::GetInstance()->GetCurrentLevel() == 3)
                            {
                                g_iTroopCounts[i] = LevelManager::GetInstance()->g_iLevel3Troops[i];
                            }
                        }
                        if (g_iPlayer == 1)
                        {
                            g_bTroopsPlaced = false;
                            g_iPlayer++;
                            //g_iTroopsPlaced = 0;
                            for (int j = 0; j < pPlayer1->m_Troops.size(); j++)
                            {
                                pPlayer1->m_Troops[j]->m_bTroopMoved = false;
                            }
                        }
                        else
                        {
                            g_bTroopsPlaced = true;
                            g_iPlayer = 1;
                            for (int j = 0; j < pPlayer1->m_Troops.size(); j++)
                            {
                                pPlayer2->m_Troops[j]->m_bTroopMoved = false;
                            }
                        }
                    }
                    else
                    {
                        if (pPlayer2->m_bIsComputer)
                        {
                            for (int i = 0; i < iTotalTroops; i++)
                            {
                                if (g_iTroopCounts[5] > 0)
                                {
                                    g_iTroopCounts[5] -= PlaceTroop(pCurrentPlayer, "Troops/Soldier.txt", event, &window, pCurrentEnemy, level);
                                }
                                if (g_iTroopCounts[0] > 0)
                                {
                                    g_iTroopCounts[0] -= PlaceTroop(pCurrentPlayer, "Troops/Archer.txt", event, &window, pCurrentEnemy, level);
                                }
                                if (g_iTroopCounts[3] > 0)
                                {
                                    g_iTroopCounts[3] -= PlaceTroop(pCurrentPlayer, "Troops/Scout.txt", event, &window, pCurrentEnemy, level);
                                }
                                if (g_iTroopCounts[2] > 0)
                                {
                                    g_iTroopCounts[2] -= PlaceTroop(pCurrentPlayer, "Troops/Giant.txt", event, &window, pCurrentEnemy, level);
                                }
                                if (g_iTroopCounts[1] > 0)
                                {
                                    g_iTroopCounts[1] -= PlaceTroop(pCurrentPlayer, "Troops/Boat.txt", event, &window, pCurrentEnemy, level);
                                }
                                if (g_iTroopCounts[4] > 0)
                                {
                                    g_iTroopCounts[4] -= PlaceTroop(pCurrentPlayer, "Troops/Shield.txt", event, &window, pCurrentEnemy, level);
                                }
                            }
                        }
                    }
                }

                // -- Turn loop -- //    
                if (!g_bLevelFinished && g_bTroopsPlaced)
                {
                    int iTroopsMoved = 0;

                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        // end turn button
                        if (PlayerTurn[2].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                        {
                            // end turn code
                            if (g_iPlayer == 2)
                            {
                                iTroopsMoved = pPlayer2->m_Troops.size();
                                g_iPlayer = 1;
                            }
                            else
                            {
                                iTroopsMoved = pPlayer1->m_Troops.size();
                                g_iPlayer = 2;
                            }
                        }
                        // next level button
                        if (PlayerTurn[6].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                        {
                            if (g_bPlayer1Won || g_bPlayer2Won)
                            {
                                // next level code
                                if (g_LevelManager->GetCurrentLevel() <= 2)
                                {
                                    LevelManager::GetInstance()->SetCurrentLevel(LevelManager::GetInstance()->GetCurrentLevel() + 1);
                                    if (LevelManager::GetInstance()->GetCurrentLevel() == 1)
                                    {
                                        level.LoadLevel("Levels/level1.txt");
                                    }
                                    else if (LevelManager::GetInstance()->GetCurrentLevel() == 2)
                                    {
                                        level.LoadLevel("Levels/level2.txt");
                                    }
                                    else if (LevelManager::GetInstance()->GetCurrentLevel() == 3)
                                    {
                                        level.LoadLevel("Levels/level3.txt");
                                    }
                                    level.PrintTerrainType();
                                }
                                for (int i = 0; i < 6; i++)
                                {
                                    if (LevelManager::GetInstance()->GetCurrentLevel() == 1)
                                    {
                                        g_iTroopCounts[i] = LevelManager::GetInstance()->g_iLevel1Troops[i];
                                    }
                                    else if (LevelManager::GetInstance()->GetCurrentLevel() == 2)
                                    {
                                        g_iTroopCounts[i] = LevelManager::GetInstance()->g_iLevel2Troops[i];
                                    }
                                    else if (LevelManager::GetInstance()->GetCurrentLevel() == 3)
                                    {
                                        g_iTroopCounts[i] = LevelManager::GetInstance()->g_iLevel3Troops[i];
                                    }
                                }

                                g_bLevelFinished = true;
                                g_bTroopsPlaced = false;
                                bool bMovingTroop = false;

                                bool g_bLevelFinished = false;
                                bool g_bPlayer1Won = false;
                                bool g_bPlayer2Won = false;

                                bool g_bTroopsPlaced = false;
                                int g_iTroopsPlaced = 0;
                            }
                        }
                        // restart button pressed
                        if (PlayerTurn[7].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                        {
                            g_iPlayer = 0;
                            LevelManager::GetInstance()->SetGameType(0);
                            LevelManager::GetInstance()->SetCurrentLevel(1);
                            window.close();
                        }

                    }

                    if (g_iPlayer == 1)
                    {
                        // click on troops to move them
                        for (int i = 0; i < pPlayer1->m_Troops.size(); i++)
                        {
                            // check if mouse is clicking in troop sprite
                            if (pPlayer1->m_Troops[i]->GetSprite().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                            {
                                if (event.type == sf::Event::MouseButtonPressed)
                                {
                                    if (event.mouseButton.button == sf::Mouse::Left)
                                    {
                                        // only move if troop hasn't moved this turn
                                        if (!pPlayer1->m_Troops[i]->m_bTroopMoved)
                                        {
                                            bMovingTroop = true;
                                            pMovingTroop = pPlayer1->m_Troops[i];
                                        }
                                    }
                                }
                            }

                            if (bMovingTroop)
                            {
                                pPlayer1->MoveTroop(*pMovingTroop, event, &window, pPlayer2);
                            }
                            // count troops moved
                            if (pPlayer1->m_Troops[i]->m_bTroopMoved)
                            {
                                if (g_bTroopsPlaced)
                                {
                                    iTroopsMoved++;
                                }
                            }
                            // change player if all troops moved
                            if (iTroopsMoved == pPlayer1->m_Troops.size())
                            {
                                for (int j = 0; j < pPlayer1->m_Troops.size(); j++)
                                {
                                    pPlayer1->m_Troops[j]->m_bTroopMoved = false;
                                }
                                pPlayer1->BuffTroops();
                                pPlayer2->BuffTroops();
                                pPlayer1->AttackEnemies(pPlayer2);
                                pPlayer2->AttackEnemies(pPlayer1);
                                pPlayer1->ResetBuffs();
                                pPlayer2->ResetBuffs();
                                g_iPlayer++;
                            }
                        }
                    }
                    else if (g_iPlayer == 2)
                    {
                        if (!pPlayer2->m_bIsComputer)
                        {
                            // click on troops to move them
                            for (int i = 0; i < pPlayer2->m_Troops.size(); i++)
                            {
                                // check if mouse is clicking in troop sprite
                                if (pPlayer2->m_Troops[i]->GetSprite().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                                {
                                    if (event.type == sf::Event::MouseButtonPressed)
                                    {
                                        if (event.mouseButton.button == sf::Mouse::Left)
                                        {
                                            // only move if troop hasn't moved this turn
                                            if (!pPlayer2->m_Troops[i]->m_bTroopMoved)
                                            {
                                                bMovingTroop = true;
                                                pMovingTroop = pPlayer2->m_Troops[i];
                                            }
                                        }
                                    }
                                }

                                if (bMovingTroop)
                                {
                                    pPlayer2->MoveTroop(*pMovingTroop, event, &window, pPlayer1);
                                }
                                // count troops moved
                                if (pPlayer2->m_Troops[i]->m_bTroopMoved)
                                {
                                    if (g_bTroopsPlaced)
                                    {
                                        iTroopsMoved++;
                                    }
                                }
                                // change player if all troops moved
                                if (iTroopsMoved == pPlayer2->m_Troops.size())
                                {
                                    for (int j = 0; j < pPlayer2->m_Troops.size(); j++)
                                    {
                                        pPlayer2->m_Troops[j]->m_bTroopMoved = false;
                                    }
                                    pPlayer2->BuffTroops();
                                    pPlayer1->BuffTroops();
                                    pPlayer2->AttackEnemies(pPlayer1);
                                    pPlayer1->AttackEnemies(pPlayer2);
                                    pPlayer1->ResetBuffs();
                                    pPlayer2->ResetBuffs();
                                    g_iPlayer--;
                                }
                            }
                        }
                        else
                        {
                            // move troops if computer and change player
                            if (pPlayer2->ComputerMove(pPlayer1))
                            {
                                for (int j = 0; j < pPlayer2->m_Troops.size(); j++)
                                {
                                    pPlayer2->m_Troops[j]->m_bTroopMoved = false;
                                }
                                // change player and call end turn functions
                                pPlayer2->BuffTroops();
                                pPlayer1->BuffTroops();
                                pPlayer2->AttackEnemies(pPlayer1);
                                pPlayer1->AttackEnemies(pPlayer2);
                                pPlayer1->ResetBuffs();
                                pPlayer2->ResetBuffs();
                                g_iPlayer--;
                            }
                        }
                    }
                }
                // -- turn loop end -- //
            }
            // check if one player has won
            if (g_bTroopsPlaced)
            {
                if (pPlayer1->m_Troops.size() <= 0 && pPlayer2->m_Troops.size() <= 0)
                {
                    //draw 
                    //g_bLevelFinished = true;
                }
                else if (pPlayer1->m_Troops.size() <= 0)
                {
                    //player 1 win
                    pPlayer1->ClearTroops();
                    pPlayer2->ClearTroops();
                    g_iPlayer = 1;
                    g_bPlayer1Won = true;
                }
                else if (pPlayer2->m_Troops.size() <= 0)
                {
                    // player 2 win
                    pPlayer1->ClearTroops();
                    pPlayer2->ClearTroops();
                    g_bPlayer2Won = true;
                    g_iPlayer = 1;
                }
            }
            // -- main window event loop end --//

            // -- select troop event loop -- //
            sf::Event SelectTroopEvent;
            while (OptionsWindow.pollEvent(SelectTroopEvent))
            {
                // lets user close the window
                if (SelectTroopEvent.type == sf::Event::Closed)
                {
                    OptionsWindow.close();
                }

                if (SelectTroopEvent.type == sf::Event::MouseButtonPressed)
                {
                    if (SelectTroopEvent.mouseButton.button == sf::Mouse::Left)
                    {
                        //clicking buttons in Options window and calling the appropriate class method
                        // Soldier
                        if (UIElements2[0].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                        {
                            TroopPlaced = PlacingSoldier;
                        }
                        // Archer
                        if (UIElements2[1].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                        {
                            TroopPlaced = PlacingArcher;
                        }
                        // Shield
                        if (UIElements2[2].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                        {
                            TroopPlaced = PlacingShield;
                        }
                        // Scout
                        if (UIElements2[3].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                        {
                            TroopPlaced = PlacingScout;
                        }
                        // Boat
                        if (UIElements2[4].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                        {
                            TroopPlaced = PlacingBoat;
                        }
                        // Giant
                        if (UIElements2[5].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                        {
                            TroopPlaced = PlacingGiant;
                        }
                        // idk
                        if (UIElements2[6].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                        {
                            TroopPlaced = PlacingNone;
                        }
                    }
                }
            }
            // -- troop select event loop end -- // 

            // -- settings event loop -- //
            sf::Event SettingsEvent;
            while (Settings.pollEvent(SettingsEvent))
            {
                // lets user close the window
                if (SettingsEvent.type == sf::Event::Closed)
                {
                    Settings.close();
                }

                if (SettingsEvent.type == sf::Event::MouseButtonPressed)
                {
                    if (SettingsEvent.mouseButton.button == sf::Mouse::Left)
                    {
                        //clicking buttons in Options window and calling the appropriate class method
                        // Soldier
                        if (UIElements2[0].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(Settings))))
                        {

                        }
                        // Archer
                        if (UIElements[1].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(Settings))))
                        {

                        }
                        // Shield
                        if (UIElements[2].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(Settings))))
                        {
                            Settings.setVerticalSyncEnabled(true);
                        }
                        // Scout
                        if (UIElements[3].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(Settings))))
                        {
                            Settings.setVerticalSyncEnabled(false);
                        }
                        // Boat
                        if (UIElements[4].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(Settings))))
                        {
                            window.create(sf::VideoMode(800, 600), "Game!");
                        }
                        // Giant
                        if (UIElements[5].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(Settings))))
                        {
                            window.create(sf::VideoMode(1366, 768), "Game!");
                        }
                        // idk
                        if (UIElements[6].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(Settings))))
                        {
                            window.create(sf::VideoMode(1920, 1080), "Game!");
                        }

                    }
                }
            }
            // -- settings event loop end -- //

            if (g_iPlayer == 1)
            {
                pPlayer1->ShowMouseSquare(&window);
            }
            else
            {
                pPlayer2->ShowMouseSquare(&window);
            }

            //clearing
            window.clear();

            //drawing **order matters**
            window.draw(terrain->Draw());
            level.Draw(&window);

            if (bMovingTroop && g_bTroopsPlaced)
            {
                if (g_iPlayer == 1)
                {
                    window.draw(pPlayer1->GetRangeRect());
                }
                else
                {
                    window.draw(pPlayer2->GetRangeRect());
                }
            }

            //draw player 1 troops
            for (int i = 0; i < pPlayer1->m_Troops.size(); i++)
            {
                window.draw(pPlayer1->m_Troops[i]->GetSprite());
            }

            //draw player 2 troops
            for (int i = 0; i < pPlayer2->m_Troops.size(); i++)
            {
                window.draw(pPlayer2->m_Troops[i]->GetSprite());
            }

            if (g_iPlayer == 1)
            {
                window.draw(pPlayer1->GetSelectRect());
                pPlayer2->ColourTroops(window);
            }
            else
            {
                window.draw(pPlayer2->GetSelectRect());
                pPlayer1->ColourTroops(window);
            }

            if (g_iPlayer == 1)
            {
                // say player 1 placing
                PlayerTurn[0].Draw(&window);

            }
            else if (g_iPlayer == 2)
            {
                // say player 2 placing
                PlayerTurn[1].Draw(&window);
            }

            //if player 1 wins
            if (g_bPlayer1Won)
            {
                PlayerTurn[4].Draw(&window);
            }

            //if player 2 wins
            if (g_bPlayer2Won)
            {
                PlayerTurn[5].Draw(&window);
            }

            // if a player wins
            PlayerTurn[6].Draw(&window);


            PlayerTurn[3].Update(std::string("Level: ") + std::to_string(LevelManager::GetInstance()->GetCurrentLevel()));
            PlayerTurn[2].Draw(&window);
            PlayerTurn[3].Draw(&window);
            PlayerTurn[7].Draw(&window);

            window.display();


            // Options window render loop
            OptionsWindow.clear();
            UIElements[0].Update(std::string("Soldier (") + std::to_string(g_iTroopCounts[5]) + std::string(")"));
            UIElements[1].Update(std::string("Archer (") + std::to_string(g_iTroopCounts[0]) + std::string(")"));
            UIElements[2].Update(std::string("Shield (") + std::to_string(g_iTroopCounts[4]) + std::string(")"));
            UIElements[3].Update(std::string("Scout (") + std::to_string(g_iTroopCounts[3]) + std::string(")"));
            UIElements[4].Update(std::string("Boat (") + std::to_string(g_iTroopCounts[1]) + std::string(")"));
            UIElements[5].Update(std::string("Giant (") + std::to_string(g_iTroopCounts[2]) + std::string(")"));
            
            // draw UI elements of options window
            for (int i = 0; i < UIElements.size(); i++)
            {
                UIElements[i].Draw(&OptionsWindow);
            }
            OptionsWindow.display();
            // Options window render loop

            // Settings window render loop
            Settings.clear();
            // draw UI elements of options window
            for (int i = 0; i < UIElements2.size(); i++)
            {
                UIElements2[i].Draw(&Settings);
            }
            Settings.display();
            // Settings window render loop


        }
    }

    return 0;
}