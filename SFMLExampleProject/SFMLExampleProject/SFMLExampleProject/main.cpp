#include "Object.h"
#include "Troop.h"

// ALWAYS BUILD IN RELEASE, AT LEAST ONCE A DAY. 

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game!");
    window.setFramerateLimit(60);

    Troop* pSoldier = new Troop("Troops/Soldier.txt");
    Troop* pGiant = new Troop("Troops/Giant.txt");

    pSoldier->PrintStats();
    pGiant->PrintStats();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            pSoldier->PlaceTroop(event, &window);
        }

        window.clear();

        window.display();
    }

    return 0;
}