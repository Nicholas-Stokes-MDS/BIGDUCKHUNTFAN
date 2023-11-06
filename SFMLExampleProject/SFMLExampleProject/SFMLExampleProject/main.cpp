#include "Object.h"
#include "Troop.h"
#include "LevelManager.h"
#include "Board.h"
#include "UIElement.h"
#include <SFML/Audio.hpp>
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
    
    PlacingTroop TroopPlaced = PlacingNone;
    Troop* pMovingTroop = new Troop("");
    bool g_bPlacingSoldier = true;
    bool bMovingTroop = false;

    bool g_bLevelFinished = false;

    int g_iTurns = 0;
    int g_iPlayer = 1;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Game!");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

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

    // add troops to Player1 vector
    Troop* pSoldier = new Troop("Troops/Soldier.txt");
    pPlayer1->AddTroop(pSoldier);
    Troop* pGiant = new Troop("Troops/Giant.txt");
    pPlayer1->AddTroop(pGiant);
    Troop* pArcher = new Troop("Troops/Archer.txt");
    pPlayer1->AddTroop(pArcher);
    Troop* pScout = new Troop("Troops/Scout.txt");
    pPlayer1->AddTroop(pScout);
    Troop* pShield = new Troop("Troops/Shield.txt");
    pPlayer1->AddTroop(pShield);
    Troop* pBoat = new Troop("Troops/Boat.txt");
    pPlayer1->AddTroop(pBoat);

    // add troops to Player2 vector
    Troop* pSoldier1 = new Troop("Troops/Soldier.txt");
    pPlayer2->AddTroop(pSoldier1);
    Troop* pGiant1 = new Troop("Troops/Giant.txt");
    pPlayer2->AddTroop(pGiant1);
    Troop* pArcher1 = new Troop("Troops/Archer.txt");
    pPlayer2->AddTroop(pArcher1);
    Troop* pScout1 = new Troop("Troops/Scout.txt");
    pPlayer2->AddTroop(pScout1);
    Troop* pShield1 = new Troop("Troops/Shield.txt");
    pPlayer2->AddTroop(pShield1);
    Troop* pBoat1 = new Troop("Troops/Boat.txt");
    pPlayer2->AddTroop(pBoat1);

    pSoldier->PrintStats();
    pGiant->PrintStats();

    // UI stuff
    sf::Font* UIElementFont = new sf::Font();
    if (!UIElementFont->loadFromFile("BRLNSR.TTF"))
    {
        std::cout << "Error loading file" << std::endl;
    }

    // vector for buttons
    std::vector<UIElement> UIElements;
    // creation of buttons
    UIElement rectElement(sf::Vector2f(50, 30), sf::Vector2f(100, 50), std::string("Soldier(") + std::to_string(5) + std::string(")"), UIElementFont);
    UIElements.push_back(rectElement);
    UIElement circleElement(sf::Vector2f(50, 100), sf::Vector2f(100, 50), std::string("Archer"), UIElementFont);
    UIElements.push_back(circleElement);
    UIElement lineElement(sf::Vector2f(50, 170), sf::Vector2f(100, 50), std::string("Shield"), UIElementFont);
    UIElements.push_back(lineElement);
    UIElement lineWidthIncreaseElement(sf::Vector2f(50, 240), sf::Vector2f(100, 50), std::string("Scout"), UIElementFont);
    UIElements.push_back(lineWidthIncreaseElement);
    UIElement lineWidthReduceElement(sf::Vector2f(50, 310), sf::Vector2f(100, 50), std::string("Boat"), UIElementFont);
    UIElements.push_back(lineWidthReduceElement);
    UIElement saveElement(sf::Vector2f(250, 30), sf::Vector2f(100, 50), std::string("Giant"), UIElementFont);
    UIElements.push_back(saveElement);
    UIElement loadElement(sf::Vector2f(250, 100), sf::Vector2f(100, 50), std::string("idk"), UIElementFont);
    UIElements.push_back(loadElement);

    std::vector<UIElement> UIElements2;
    // creation of buttons
    UIElement volume1Element(sf::Vector2f(20, 30), sf::Vector2f(150, 50), std::string("Volume+"), UIElementFont);
    UIElements2.push_back(volume1Element);
    UIElement volume2Element(sf::Vector2f(20, 100), sf::Vector2f(150, 50), std::string("Volume-"), UIElementFont);
    UIElements2.push_back(volume2Element);
    UIElement vsync1Element(sf::Vector2f(20, 170), sf::Vector2f(150, 50), std::string("Vsync Enable"), UIElementFont);
    UIElements2.push_back(vsync1Element);
    UIElement vsync2Element(sf::Vector2f(20, 240), sf::Vector2f(150, 50), std::string("Vsync Disable"), UIElementFont);
    UIElements2.push_back(vsync2Element);
    UIElement resolution1Element(sf::Vector2f(20, 310), sf::Vector2f(150, 50), std::string("640 by 480"), UIElementFont);
    UIElements2.push_back(resolution1Element);
    UIElement resolution2Element(sf::Vector2f(220, 30), sf::Vector2f(150, 50), std::string("800 by 600"), UIElementFont);
    UIElements2.push_back(resolution2Element);
    UIElement resolution3Element(sf::Vector2f(220, 100), sf::Vector2f(150, 50), std::string("1920 by 1080"), UIElementFont);
    UIElements2.push_back(resolution3Element);

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

            
            // placing troop if button pressed
            switch (TroopPlaced)
                if (g_bPlacingSoldier)
                {
            case None:
                break;
            case PlacingSoldier:
                if (g_iPlayer == 1)
                {
                    pPlayer1->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));
                    pSoldier->PlaceTroop(event, &window);
                    if (pSoldier->GetPosition() != sf::Vector2f(-100, -100))
                    {
                        g_bPlacingSoldier = false;
                    }
                    break;
                }
                else if (g_iPlayer == 2)
                {
                    pPlayer2->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));
                    pSoldier1->PlaceTroop(event, &window);
                    if (pSoldier1->GetPosition() != sf::Vector2f(-100, -100))
                    {
                        g_bPlacingSoldier = false;
                    }
                    break;
                }
                break;
            case PlacingArcher:
                if (g_iPlayer == 1)
                {
                    pPlayer1->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));
                    pArcher->PlaceTroop(event, &window);
                    if (pArcher->GetPosition() != sf::Vector2f(-100, -100))
                    {
                        g_bPlacingSoldier = false;
                    }
                    break;
                }
                else if (g_iPlayer == 2)
                {
                    pPlayer2->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));
                    pArcher1->PlaceTroop(event, &window);
                    if (pArcher1->GetPosition() != sf::Vector2f(-100, -100))
                    {
                        g_bPlacingSoldier = false;
                    }
                    break;
                }
                break;
            case PlacingScout:
                if (g_iPlayer == 1)
                {
                    pPlayer1->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));
                    pScout->PlaceTroop(event, &window);
                    if (pScout->GetPosition() != sf::Vector2f(-100, -100))
                    {
                        g_bPlacingSoldier = false;
                    }
                    break;
                }
                else if (g_iPlayer == 2)
                {
                    pPlayer2->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));
                    pScout1->PlaceTroop(event, &window);
                    if (pScout1->GetPosition() != sf::Vector2f(-100, -100))
                    {
                        g_bPlacingSoldier = false;
                    }
                    break;
                }
                break;
            case PlacingGiant:
                if (g_iPlayer == 1)
                {
                    pPlayer1->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));
                    pGiant->PlaceTroop(event, &window);
                    if (pGiant->GetPosition() != sf::Vector2f(-100, -100))
                    {
                        g_bPlacingSoldier = false;
                    }
                    break;
                }
                else if (g_iPlayer == 2)
                {
                    pPlayer2->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));
                    pGiant1->PlaceTroop(event, &window);
                    if (pGiant1->GetPosition() != sf::Vector2f(-100, -100))
                    {
                        g_bPlacingSoldier = false;
                    }
                    break;
                }
                break;
            case PlacingBoat:
                if (g_iPlayer == 1)
                {
                    pPlayer1->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));
                    pBoat->PlaceTroop(event, &window);
                    if (pBoat->GetPosition() != sf::Vector2f(-100, -100))
                    {
                        g_bPlacingSoldier = false;
                    }
                    break;
                }
                else if (g_iPlayer == 2)
                {
                    pPlayer2->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));
                    pBoat1->PlaceTroop(event, &window);
                    if (pBoat1->GetPosition() != sf::Vector2f(-100, -100))
                    {
                        g_bPlacingSoldier = false;
                    }
                    break;
                }
                break;
            case PlacingShield:
                if (g_iPlayer == 1)
                {
                    pPlayer1->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));
                    pShield->PlaceTroop(event, &window);
                    if (pShield->GetPosition() != sf::Vector2f(-100, -100))
                    {
                        g_bPlacingSoldier = false;
                    }
                    break;
                }
                else if (g_iPlayer == 2)
                {
                    pPlayer2->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));
                    pShield1->PlaceTroop(event, &window);
                    if (pShield1->GetPosition() != sf::Vector2f(-100, -100))
                    {
                        g_bPlacingSoldier = false;
                    }
                    break;
                }
                break;
            default:
                break;
                }


            // -- Turn loop -- //
            
            if (!g_bLevelFinished)
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
                            pPlayer1->MoveTroop(*pMovingTroop, event, &window);
                        }
                        // count troops moved
                        if (pPlayer1->m_Troops[i]->m_bTroopMoved)
                        {
                            iTroopsMoved++;
                        }
                        // change player if all troops moved
                        if (iTroopsMoved == pPlayer1->m_Troops.size())
                        {
                            for (int j = 0; j < pPlayer1->m_Troops.size(); j++)
                            {
                                pPlayer1->m_Troops[j]->m_bTroopMoved = false;
                            }
                            pPlayer1->AttackEnemies(pPlayer2);
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
                            pPlayer2->MoveTroop(*pMovingTroop, event, &window);
                        }
                        // count troops moved
                        if (pPlayer2->m_Troops[i]->m_bTroopMoved)
                        {
                            iTroopsMoved++;
                        }
                        // change player if all troops moved
                        if (iTroopsMoved == pPlayer2->m_Troops.size())
                        {
                            for (int j = 0; j < pPlayer2->m_Troops.size(); j++)
                            {
                                pPlayer2->m_Troops[j]->m_bTroopMoved = false;
                            }
                            pPlayer2->AttackEnemies(pPlayer1);
                            g_iPlayer--;
                        }
                    }
                }
            }
            // -- turn loop end -- //
        }
        // check if one player has won
        if (pPlayer1->m_Troops.size() <= 0 && pPlayer2->m_Troops.size() <= 0)
        {
            //draw 
            g_bLevelFinished = true;
        }
        else if (pPlayer1->m_Troops.size() <= 0)
        {
            //player 1 win
            g_bLevelFinished = true;
        }
        else if (pPlayer2->m_Troops.size() <= 0)
        {
            // player 2 win
            g_bLevelFinished = true;
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
                        window.create(sf::VideoMode(640, 480), "Game!");
                    }
                    // Giant
                    if (UIElements[5].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(Settings))))
                    {
                        window.create(sf::VideoMode(800, 600), "Game!");
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

        // draw player 1 troops
        for (int i = 0; i < pPlayer1->m_Troops.size(); i++)
        {
            window.draw(pPlayer1->m_Troops[i]->GetSprite());
        }

        // draw player 2 troops
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