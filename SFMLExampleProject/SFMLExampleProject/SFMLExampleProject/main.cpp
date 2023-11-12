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

int PlaceTroop(Board* _Player, std::string _TroopPath, sf::Event _event, sf::RenderWindow* _WindowRef)
{
    // change the select rectangle to grey
    _Player->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));

    // if mouse button pressed create a troop instance
    if (_event.type == sf::Event::MouseButtonPressed)
    {
        if (_event.mouseButton.button == sf::Mouse::Left)
        {
            Troop* pTroop = new Troop(_TroopPath);
            pTroop->PlaceTroop(_event, _WindowRef);
            _Player->AddTroop(pTroop);
            return 1;
        }
    }
    return 0;
}

int main()
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
    UIElement SinglePlayer(sf::Vector2f(50, 30), sf::Vector2f(150, 50), std::string("SinglePlayer"), UIElementFont, sf::Color::Black);
    MenuElements.push_back(SinglePlayer);
    UIElement TwoPlayer(sf::Vector2f(50, 100), sf::Vector2f(150, 50), std::string("TwoPlayer"), UIElementFont, sf::Color::Black);
    MenuElements.push_back(TwoPlayer);

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
                        // Soldier
                        if (MenuElements[0].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                        {
                            LevelManager::GetInstance()->SetGameType(1);
                        }
                        // Archer
                        if (MenuElements[1].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                        {
                            LevelManager::GetInstance()->SetGameType(2);
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
    }

    PlacingTroop TroopPlaced = PlacingNone;
    Troop* pMovingTroop = new Troop("");
    //bool g_bPlacingSoldier = true;
    bool bMovingTroop = false;

    bool g_bLevelFinished = false;

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
    Board* pPlayer1 = new Board(level, 1);
    Board* pPlayer2 = new Board(level, 2);

    Board* pCurrentPlayer = pPlayer1;

    // UI stuff
    // vector for buttons
    std::vector<UIElement> UIElements;
    // creation of buttons
    UIElement rectElement(sf::Vector2f(50, 30), sf::Vector2f(100, 50), std::string("Soldier(") + std::to_string(5) + std::string(")"), UIElementFont, sf::Color::Black);
    UIElements.push_back(rectElement);
    UIElement circleElement(sf::Vector2f(50, 100), sf::Vector2f(100, 50), std::string("Archer"), UIElementFont, sf::Color::Black);
    UIElements.push_back(circleElement);
    UIElement lineElement(sf::Vector2f(50, 170), sf::Vector2f(100, 50), std::string("Shield"), UIElementFont, sf::Color::Black);
    UIElements.push_back(lineElement);
    UIElement lineWidthIncreaseElement(sf::Vector2f(50, 240), sf::Vector2f(100, 50), std::string("Scout"), UIElementFont, sf::Color::Black);
    UIElements.push_back(lineWidthIncreaseElement);
    UIElement lineWidthReduceElement(sf::Vector2f(50, 310), sf::Vector2f(100, 50), std::string("Boat"), UIElementFont, sf::Color::Black);
    UIElements.push_back(lineWidthReduceElement);
    UIElement saveElement(sf::Vector2f(250, 30), sf::Vector2f(100, 50), std::string("Giant"), UIElementFont, sf::Color::Black);
    UIElements.push_back(saveElement);
    UIElement loadElement(sf::Vector2f(250, 100), sf::Vector2f(100, 50), std::string("idk"), UIElementFont, sf::Color::Black);
    UIElements.push_back(loadElement);

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
    UIElement Player1Element(sf::Vector2f(0, 415), sf::Vector2f(150, 50), std::string("Player 1's turn"), UIElementFont, sf::Color::Blue);
    PlayerTurn.push_back(Player1Element);
    UIElement Player2Element(sf::Vector2f(0, 415), sf::Vector2f(150, 50), std::string("Player 2's turn"), UIElementFont, sf::Color::Red);
    PlayerTurn.push_back(Player2Element);

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
                }

                else if (event.key.code == sf::Keyboard::Num2)
                {
                    LevelManager::GetInstance()->LoadLevel(2, &level);
                }

                else if (event.key.code == sf::Keyboard::Num3)
                {
                    LevelManager::GetInstance()->LoadLevel(3, &level);
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
                }
                else if (g_iPlayer == 2)
                {
                    // say player 2 placing
                    pCurrentPlayer = pPlayer2;
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
                        g_iTroopCounts[5] -= PlaceTroop(pCurrentPlayer, "Troops/Soldier.txt", event, &window);
                    }
                    break;
                case PlacingArcher:
                    if (g_iTroopCounts[0] > 0)
                    {
                        g_iTroopCounts[0] -= PlaceTroop(pCurrentPlayer, "Troops/Archer.txt", event, &window);
                    }
                    break;
                case PlacingScout:
                    if (g_iTroopCounts[3] > 0)
                    {
                        g_iTroopCounts[3] -= PlaceTroop(pCurrentPlayer, "Troops/Scout.txt", event, &window);
                    }
                    break;
                case PlacingGiant:
                    if (g_iTroopCounts[2] > 0)
                    {
                        g_iTroopCounts[2] -= PlaceTroop(pCurrentPlayer, "Troops/Giant.txt", event, &window);
                    }
                    break;
                case PlacingBoat:
                    if (g_iTroopCounts[1] > 0)
                    {
                        g_iTroopCounts[1] -= PlaceTroop(pCurrentPlayer, "Troops/Boat.txt", event, &window);
                    }
                    break;
                case PlacingShield:
                    if (g_iTroopCounts[4] > 0)
                    {
                        g_iTroopCounts[4] -= PlaceTroop(pCurrentPlayer, "Troops/Shield.txt", event, &window);
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
            }

            // -- Turn loop -- //    
            if (!g_bLevelFinished && g_bTroopsPlaced)
            {
                if (g_iPlayer == 1)
                {
                    int iTroopsMoved = 0;
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
                            pPlayer1->AttackEnemies(pPlayer2);
                            pPlayer2->AttackEnemies(pPlayer1);
                            g_iPlayer++;
                        }
                    }
                }
                else if (g_iPlayer == 2)
                {
                    int iTroopsMoved = 0;
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
                            pPlayer2->AttackEnemies(pPlayer1);
                            pPlayer1->AttackEnemies(pPlayer2);
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
                g_bLevelFinished = true;
            }
            else if (pPlayer1->m_Troops.size() <= 0)
            {
                //player 1 win
                g_bLevelFinished = true;
                g_bTroopsPlaced = false;
                pPlayer1->ClearTroops();
                pPlayer2->ClearTroops();
                if (g_LevelManager->GetCurrentLevel() <= 2)
                {
                    LevelManager::GetInstance()->LoadLevel(g_LevelManager->GetCurrentLevel() + 1, &level);
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
                g_iPlayer = 1;
            }
            else if (pPlayer2->m_Troops.size() <= 0)
            {
                // player 2 win
                g_bLevelFinished = true;
                g_bTroopsPlaced = false;
                pPlayer1->ClearTroops();
                pPlayer2->ClearTroops();
                if (g_LevelManager->GetCurrentLevel() <= 2)
                {
                    LevelManager::GetInstance()->LoadLevel(g_LevelManager->GetCurrentLevel() + 1, &level);
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
        window.clear();;

        //drawing **order matters**
        window.draw(terrain->Draw());
        level.Draw(&window);
        if (g_iPlayer == 1)
        {
            window.draw(pPlayer1->GetRangeRect());
        }
        else
        {
            window.draw(pPlayer2->GetRangeRect());
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
        }
        else
        {
            window.draw(pPlayer2->GetSelectRect());
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

        window.display();


        // Options window render loop
        OptionsWindow.clear();
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

    return 0;
}