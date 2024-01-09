#ifndef _DIRECTION
#define _DIRECTION

#include<SFML/Graphics.hpp>

//enum class Direction
enum class Direction
{
        UpHeadLeft,
        DownHeadLeft,
        Right,
        Left,
        Stay,
        UpLeft,
        UpRight,
        DownLeft,
        DownRight,
        DownHeadRight,
        UpHeadRight,
        Max,



};
Direction opposite(Direction dir);
sf::Vector2f toVector(Direction dir);
#endif