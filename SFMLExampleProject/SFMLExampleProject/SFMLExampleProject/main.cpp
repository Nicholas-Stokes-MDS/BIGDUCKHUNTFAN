#include "Object.h"
#include "Troop.h"
#include "LevelManager.h"
#include "Board.h"
#include "UIElement.h"
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
    PlacingTroop TroopPlaced = PlacingNone;
    bool g_bPlacingSoldier = true;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game!");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    sf::RenderWindow OptionsWindow(sf::VideoMode(400, 400), "Place troops");
    OptionsWindow.setVerticalSyncEnabled(true);

    Board* pBoard = new Board();

    Troop* pSoldier = new Troop("Troops/Soldier.txt");
    Troop* pGiant = new Troop("Troops/Giant.txt");
    Troop* pArcher = new Troop("Troops/Archer.txt");
    Troop* pScout = new Troop("Troops/Scout.txt");
    Troop* pShield = new Troop("Troops/Shield.txt");
    Troop* pBoat = new Troop("Troops/Boat.txt");

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
                    window.create(sf::VideoMode(640, 480), "Game!");
                }

                else if (event.key.code == sf::Keyboard::Num8)
                {
                    window.create(sf::VideoMode(800, 600), "Game!");
                }

                else if (event.key.code == sf::Keyboard::Num9)
                {
                    window.create(sf::VideoMode(1920, 1080), "Game!");
                }



                break;
            default:
                break;

            }

            switch (TroopPlaced)
            {
            case None:
                pBoard->MoveTroop(*pSoldier, event, &window);
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
                    if (UIElements[0].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    {
                        TroopPlaced = PlacingSoldier;
                    }
                    // Archer
                    if (UIElements[1].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    {
                        TroopPlaced = PlacingArcher;
                    }
                    // Shield
                    if (UIElements[2].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    {
                        TroopPlaced = PlacingShield;
                    }
                    // Scout
                    if (UIElements[3].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    {
                        TroopPlaced = PlacingScout;
                    }
                    // Boat
                    if (UIElements[4].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    {
                        TroopPlaced = PlacingBoat;
                    }
                    // Giant
                    if (UIElements[5].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    {
                        TroopPlaced = PlacingGiant;
                    }
                    // idk
                    if (UIElements[6].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    {
                        TroopPlaced = PlacingNone;
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

        
    }

    return 0;
}