#include"Board.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

//constructor
Board::Board()
{

    //reading all the platforms coordinate that we will check the collision between them and the charactters
    std::ifstream file("StageOnePlatforms.txt"); // Replace "input.txt" with your file path
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<float> numbers = splitString(line);
        static std::vector<sf::Vector2f> duos;
        for (int i = 0; i < numbers.size(); i+=2)
        {
            duos.emplace_back(sf::Vector2f(numbers[i]*MAPSCALE, numbers[i + 1]*MAPSCALE));
        }
        m_platformsPoints.push_back(duos);
        duos.clear();
    }

    file.close();
}
//==================================
//spliting the sttring we got to points (x,y)
std::vector<float> Board::splitString(const std::string& line) {
    std::istringstream iss(line);
    float num;
    std::vector<float> numbers;
    while (iss >> num) {
        numbers.push_back(num);
    }
    return numbers;
}
//===================================
//creating the platforms
void Board::createPlatforms()
{
    for (int i = 0; i < m_platformsPoints.size(); i++)
    {
        m_platforms.emplace_back(Platform(m_platformsPoints[i]));
    }
}
//=====================================
//getting the platforms to draw we needed this to check it if its correct
std::vector<Platform> Board::getPlatformsToDraw() const
{
    return m_platforms;
}
//==========================================
//checking collision between two sprites 
bool Board::checkCollisionBetweenTwoSprites(sf::Sprite sp1, sf::Sprite sp2)
{

    if (sp1.getGlobalBounds().intersects(sp2.getGlobalBounds()))
        return true;

    return false;
}
//===========================================
//clearing the class vectors 
void Board::clearVec()
{
    m_currPlatforms.clear();
    m_platforms.clear();
    m_platformsPoints.clear();
    
}