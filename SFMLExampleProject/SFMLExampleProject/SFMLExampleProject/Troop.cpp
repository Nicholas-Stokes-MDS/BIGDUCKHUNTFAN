#include "Troop.h"

Troop::Troop(std::string _sFilePath)
{
    bool bSpaceReached = false;
    std::string sLoadString = "";

    std::fstream loadFileStream;

    loadFileStream.open(_sFilePath, std::ios::in);

    /* Reminder to make sure file you are loading is the correct size */
    std::string loadFileString;
    int iLineCount = 0;

    if (loadFileStream.is_open())
    {
        while (std::getline(loadFileStream, loadFileString))
        {
            for (int i = 0; i < loadFileString.size(); i++)
            {
                m_cCharArray[iLineCount][i] = loadFileString[i];
                std::cout << m_cCharArray[iLineCount][i];

                // load name
                if (iLineCount == 0 && m_cCharArray[iLineCount][i] != ' ')
                {
                    if (!bSpaceReached)
                    {
                        m_sName += m_cCharArray[iLineCount][i];
                    }
                }
                // stop reading once space reached
                else if (m_cCharArray[iLineCount][i] == ' ')
                {
                    bSpaceReached = true;
                }

                // load HP
                if (iLineCount == 1 && m_cCharArray[iLineCount][i] >= 48 && m_cCharArray[iLineCount][i] <= 57)
                {
                    sLoadString += m_cCharArray[iLineCount][i];
                }
                else if (iLineCount == 1)
                {
                    m_iHealth = std::stof(sLoadString);
                }

                // load Damage
                if (iLineCount == 2 && m_cCharArray[iLineCount][i] >= 48 && m_cCharArray[iLineCount][i] <= 57)
                {
                    sLoadString += m_cCharArray[iLineCount][i];
                }
                else if (iLineCount == 2)
                {
                    m_iDamage = std::stof(sLoadString);
                }

                // load Range
                if (iLineCount == 3 && m_cCharArray[iLineCount][i] >= 48 && m_cCharArray[iLineCount][i] <= 57)
                {
                    sLoadString += m_cCharArray[iLineCount][i];
                }
                else if (iLineCount == 3)
                {
                    m_iAttackRange = std::stof(sLoadString);
                }

                // load Attack Range
                if (iLineCount == 4 && m_cCharArray[iLineCount][i] >= 48 && m_cCharArray[iLineCount][i] <= 57)
                {
                    sLoadString += m_cCharArray[iLineCount][i];
                }
                else if (iLineCount == 4)
                {
                     m_iRange = std::stof(sLoadString);
                }
            }
            iLineCount++;
            sLoadString = "";
            std::cout << std::endl;
        }
        loadFileStream.close();
    }
    SetType();
    SetPosition(sf::Vector2f(-100, -100));
}

void Troop::PrintStats()
{
    std::cout << std::endl;
    std::cout << m_sName << std::endl;
    std::cout << m_iHealth << std::endl;
    std::cout << m_iDamage << std::endl;
    std::cout << m_iRange << std::endl;
    std::cout << m_iAttackRange << std::endl;
}

void Troop::SetType()
{
    if (m_sName == "Soldier")
    {
        Type = Solider;
        SetSprite("Sprites/Soldier.bmp");
    }
    if (m_sName == "Giant")
    {
        Type = Giant;
        SetSprite("Sprites/Giant.bmp");
    }
    if (m_sName == "Archer")
    {
        Type = Archer;
        SetSprite("Sprites/Archer.bmp");
    }
    if (m_sName == "Shield")
    {
        Type = Shield;
        SetSprite("Sprites/Shield.bmp");
    }
    if (m_sName == "Boat")
    {
        Type = Boat;
        SetSprite("Sprites/Boat.bmp");
    }
    if (m_sName == "Scout")
    {
        Type = Scout;
        SetSprite("Sprites/Scout.bmp");
    }

    if (Type == None)
    {
        SetSprite("Sprites/Select.bmp");
    }
}

void Troop::SetSprite(sf::String _Path)
{
    m_TroopTexture.loadFromFile(_Path);
    m_TroopSprite.setTexture(m_TroopTexture);
}

void Troop::PlaceTroop(sf::Event _event, sf::RenderWindow* _WindowRef)
{
    if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left)
    {
        // divide mouse pos by 16 and round down to find current square then snap to that position
        float fXPos = sf::Mouse::getPosition(*_WindowRef).x;
        float fYPos = sf::Mouse::getPosition(*_WindowRef).y;

        fXPos = std::floor(fXPos/32);
        fYPos = std::floor(fYPos/32);

        SetPosition(sf::Vector2f(fXPos * 32, fYPos * 32));

        m_bTroopMoved = true;
    }
}

void Troop::SetPosition(sf::Vector2f _Pos)
{
    m_TroopSprite.setPosition(_Pos);
    m_TroopPosition = _Pos;

    //m_TroopSprite
}

sf::Sprite Troop::GetSprite()
{
    return m_TroopSprite;
}


