#pragma once
#include "Cell.h"

class SnakeGame;

/*
 * Used for represents Snake in SnakeGame
 * Minimal length: 2 (head and tail)
 */
class Snake
{
/////////////////////////
//Variables
protected:
    Uint32 length;
    Uint32 lengthToWin;
    SnakeGame* game;

    Cell head;
    Cell tail;
    Direction rotateDirection;

    //Variables for correct snake display
    bool hasFoodBeenEaten;
    bool isHeadReversed;

/////////////////////////
//Functions

/* Initialization */
public:
    Snake(SnakeGame* game);
    void init(Vector2b headCoords);

/* Mechanics */
public:
    void inputMovement(Direction direction);
    void turn();
    
protected:
    void rotate(Direction direction);
    void moveForward(Vector2b nextHeadCoords, bool isSnakeGrowing);
    void moveForwardHead(Vector2b headCoords);
    void moveForwardTail();

/* Graphics */
protected:
    void checkHeadReverse();

/* Getters */
public:
    bool getIsHeadReversed();
    Uint32 getLength();
};
