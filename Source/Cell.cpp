#include "Cell.h"


Cell::Cell()
{
}

Cell::Cell(CellType type, Direction direction):
    CellData{type, direction}
{
}

Vector2b Cell::nextCellCoords(const Vector2b& fieldSize)
{
    Vector2b nextCellCoords = coords + directionToCoords(direction);
    
    if(nextCellCoords.x >= fieldSize.x)
    {
        nextCellCoords.x = 0;
    }
    else if(nextCellCoords.x < 0)
    {
        nextCellCoords.x = fieldSize.x - 1;
    }

    if(nextCellCoords.y >= fieldSize.y)
    {
        nextCellCoords.y = 0;
    }
    else if(nextCellCoords.y < 0)
    {
        nextCellCoords.y = fieldSize.y - 1;
    }

    return nextCellCoords;
}

CellType Cell::getType()
{
    return type;
}

Direction Cell::getDirection()
{
    return direction;
}

Vector2b Cell::getCoords()
{
    return coords;
}

void Cell::setType(CellType newType)
{
    type = newType;
}

void Cell::setDirection(Direction newDirection)
{
    direction = newDirection;
}

void Cell::setCoords(Vector2b newCoords)
{
    coords = newCoords;
}
