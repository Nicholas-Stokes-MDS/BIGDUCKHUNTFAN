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
    bool g_bPlacingSoldier = true;
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

    // creates board and troops
    Board* pBoard = new Board(level);

    // add troops to Board vector
    Troop* pSoldier = new Troop("Troops/Soldier.txt");
    pBoard->AddTroop(*pSoldier);
    Troop* pGiant = new Troop("Troops/Giant.txt");
    pBoard->AddTroop(*pGiant);
    Troop* pArcher = new Troop("Troops/Archer.txt");
    pBoard->AddTroop(*pArcher);
    Troop* pScout = new Troop("Troops/Scout.txt");
    pBoard->AddTroop(*pScout);
    Troop* pShield = new Troop("Troops/Shield.txt");
    pBoard->AddTroop(*pShield);
    Troop* pBoat = new Troop("Troops/Boat.txt");
    pBoard->AddTroop(*pBoat);

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
            switch (TroopPlaced)
            if (g_bPlacingSoldier)
            {
            case None:
                break;
            case PlacingSoldier:
                pBoard->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));
                pSoldier->PlaceTroop(event, &window);
                if (pSoldier->GetPosition() != sf::Vector2f(-100, -100))
                {
                    g_bPlacingSoldier = false;
                }
                break;
            case PlacingArcher:
                pBoard->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));
                pArcher->PlaceTroop(event, &window);
                if (pArcher->GetPosition() != sf::Vector2f(-100, -100))
                {
                    TroopPlaced = PlacingNone;
                }
                break;
            case PlacingScout:
                pBoard->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));
                pScout->PlaceTroop(event, &window);
                if (pScout->GetPosition() != sf::Vector2f(-100, -100))
                {
                    TroopPlaced = PlacingNone;
                }
                break;
            case PlacingGiant:
                pBoard->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));
                pGiant->PlaceTroop(event, &window);
                if (pGiant->GetPosition() != sf::Vector2f(-100, -100))
                {
                    TroopPlaced = PlacingNone;
                }
                break;
            case PlacingBoat:
                pBoard->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));
                pBoat->PlaceTroop(event, &window);
                if (pBoat->GetPosition() != sf::Vector2f(-100, -100))
                {
                    TroopPlaced = PlacingNone;
                }
                break;
            case PlacingShield:
                pBoard->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));
                pShield->PlaceTroop(event, &window);
                if (pShield->GetPosition() != sf::Vector2f(-100, -100))
                {
                    TroopPlaced = PlacingNone;
                }
                break;
            default:
                break;
            }
        }
        sf::Event OptionsEvent;
        while (OptionsWindow.pollEvent(OptionsEvent))
        {
            // lets user close the window
            if (OptionsEvent.type == sf::Event::Closed)
            {
                OptionsWindow.close();
            }

            if (OptionsEvent.type == sf::Event::MouseButtonPressed)
            {
                if (OptionsEvent.mouseButton.button == sf::Mouse::Left)
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
        
        pBoard->ShowMouseSquare(&window);

        //clearing
        window.clear();;

        //drawing **order matters**
        window.draw(terrain->Draw());
        level.Draw(&window);
        window.draw(pBoard->GetRangeRect());
        window.draw(pSoldier->GetSprite());
        window.draw(pGiant->GetSprite());
        window.draw(pArcher->GetSprite());
        window.draw(pBoat->GetSprite());
        window.draw(pScout->GetSprite());
        window.draw(pShield->GetSprite());
        window.draw(pBoard->GetSelectRect());

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