#include "Direction.h"
#include "Direction.h"
#include <stdexcept>

Direction opposite(Direction dir)
{
    switch (dir)
    {
    case Direction::UpHeadLeft:
        return Direction::DownHeadLeft;
    case Direction::DownHeadLeft:
        return Direction::UpHeadLeft;
    case Direction::Right:
        return Direction::Left;
    case Direction::Left:
        return Direction::Right;
    case Direction::Stay:
        return Direction::Stay;
    default:
        throw std::runtime_error("Unknown direction");
    }
}

sf::Vector2f toVector(Direction dir)
{
    switch (dir)
    {
    case Direction::UpHeadLeft:
        return { 0, -1 };
    case Direction::DownHeadLeft:
        return { 0, 1 };
    case Direction::Right:
        return { 1, 0 };
    case Direction::Left:
        return { -1, 0 };
    case Direction::Stay:
        return { 0, 0 };
    case Direction::UpLeft:
        return { -1, -1 };
    case Direction::UpRight:
        return { 1,-1 };
    case Direction::DownLeft:
        return { -1, 1 };
    case Direction::DownRight:
        return { 1,1 };
    case Direction::DownHeadRight:
        return { 0,1 };
    case Direction::UpHeadRight:
        return { 0,-1 };
    default:
        throw std::runtime_error("Unknown direction");
    }
}