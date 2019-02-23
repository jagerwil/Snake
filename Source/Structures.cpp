#include "Structures.h"

Vector2b directionToCoords(Direction direction)
{
    Vector2b result = {0, 0};

    switch(direction)
    {
    case Direction::Up:
        result = {0, -1};
        break;
    case Direction::Down:
        result = {0, 1};
        break;
    case Direction::Left:
        result = {-1, 0};
        break;
    case Direction::Right:
        result = {1, 0};
        break;
    }

    return result;
}

Direction relativeDirection(Direction direction1, Direction direction2)
{
    Direction relativeDirection = Direction::None;

    if(direction1 == Direction::Up    && direction2 == Direction::Left  ||
       direction1 == Direction::Left  && direction2 == Direction::Down  ||
       direction1 == Direction::Down  && direction2 == Direction::Right ||
       direction1 == Direction::Right && direction2 == Direction::Up)
    {
        relativeDirection = Direction::Left;
    }
    else if (direction1 == Direction::Up    && direction2 == Direction::Right ||
             direction1 == Direction::Right && direction2 == Direction::Down  ||
             direction1 == Direction::Down  && direction2 == Direction::Left  ||
             direction1 == Direction::Left  && direction2 == Direction::Up)
    {
        relativeDirection = Direction::Right;
    }
    
    return relativeDirection;
}