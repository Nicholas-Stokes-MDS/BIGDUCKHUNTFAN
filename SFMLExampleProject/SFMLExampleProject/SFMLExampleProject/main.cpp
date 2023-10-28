#include "Object.h"
#include "Troop.h"
#include "LevelManager.h"
#include "Board.h"
#include "UIElement.h"
// ALWAYS BUILD IN RELEASE, AT LEAST ONCE A DAY. 

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game!");
    window.setFramerateLimit(60);

    sf::RenderWindow OptionsWindow(sf::VideoMode(400, 400), "Place troops");
    OptionsWindow.setVerticalSyncEnabled(true);

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
            pBoard->MoveTroop(*pSoldier, event, &window);
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
                        //pSoldier->PlaceTroop(event, &window);
                    }
                    // Archer
                    if (UIElements[1].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    {

                    }
                    // Shield
                    if (UIElements[2].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    {

                    }
                    // Scout
                    if (UIElements[3].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    {

                    }
                    // Boat
                    if (UIElements[4].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    {

                    }
                    // Giant
                    if (UIElements[5].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    {

                    }
                    // idk
                    if (UIElements[6].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    {

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

        
    }

    return 0;
}