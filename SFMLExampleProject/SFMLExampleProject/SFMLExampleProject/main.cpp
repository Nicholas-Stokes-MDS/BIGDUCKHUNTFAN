#include "Object.h"
#include "Troop.h"
#include "LevelManager.h"
#include "Board.h"
#include "UIElement.h"
// ALWAYS BUILD IN RELEASE, AT LEAST ONCE A DAY. 

int main()
{
    bool g_bPlacingSoldier = true;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game!");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    sf::RenderWindow OptionsWindow(sf::VideoMode(400, 400), "Place troops");
    OptionsWindow.setVerticalSyncEnabled(true);

    sf::RenderWindow Settings(sf::VideoMode(400, 400), "Settings");
    Settings.setVerticalSyncEnabled(true);

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
                    
                }
                break;
            default:
                break;

            }
            if (g_bPlacingSoldier)
            {
                pBoard->GetSelectRect().setFillColor(sf::Color(255, 255, 255, 128));
                pSoldier->PlaceTroop(event, &window);
                if (pSoldier->GetPosition() != sf::Vector2f(-100,-100))
                {
                    g_bPlacingSoldier = false;
                }
            }
            else
            {
                pBoard->MoveTroop(*pSoldier, event, &window);
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
                        g_bPlacingSoldier = true;
                    }
                    // Archer
                    if (UIElements2[1].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    {

                    }
                    // Shield
                    if (UIElements2[2].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    {

                    }
                    // Scout
                    if (UIElements2[3].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    {

                    }
                    // Boat
                    if (UIElements2[4].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    {

                    }
                    // Giant
                    if (UIElements2[5].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    {

                    }
                    // idk
                    if (UIElements2[6].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    {

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