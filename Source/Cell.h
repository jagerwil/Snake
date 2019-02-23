#pragma once
#include "Structures.h"

/*
 * Used for storing cells outside the game field
 */
class Cell : protected CellData
{
/////////////////////////
//Variables
protected:
    Vector2b coords;

/////////////////////////
//Functions

/* Initialization */
public:
    Cell();
    Cell(CellType type, Direction direction);

/* Mechanics */
public:
    //Coords of next cell in movement direction 
    //[Used only for snake cell]
    Vector2b nextCellCoords(const Vector2b& fieldSize);

/* Getters & Setters */
public:
    CellType getType();
    Direction getDirection();
    Vector2b getCoords();

    void setType(CellType newType);
    void setDirection(Direction newDirection);
    void setCoords(Vector2b newCoords);
};