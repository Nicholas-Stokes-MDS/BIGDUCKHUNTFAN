#include "Troop.h"

Troop::Troop(std::string _sFilePath)
{
    bool bSpaceReached = false;
    std::string sLoadString;

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
                    m_iRange = std::stof(sLoadString);
                }

                // load Attack Range
                if (iLineCount == 4 && m_cCharArray[iLineCount][i] >= 48 && m_cCharArray[iLineCount][i] <= 57)
                {
                    sLoadString += m_cCharArray[iLineCount][i];
                }
                else if (iLineCount == 4)
                {
                    m_iAttackRange = std::stof(sLoadString);
                }
            }
            iLineCount++;
            sLoadString = "";
            std::cout << std::endl;
        }
        loadFileStream.close();
    }
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
