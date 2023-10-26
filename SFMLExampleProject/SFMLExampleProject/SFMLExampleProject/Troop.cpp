#include "Troop.h"

Troop::Troop(std::string _sFilePath)
{
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
                m_cCharArray[i][iLineCount] = loadFileString[i];
                std::cout << m_cCharArray[i][iLineCount];
            }
            iLineCount++;
            std::cout << std::endl;
        }
        loadFileStream.close();
    }
}
