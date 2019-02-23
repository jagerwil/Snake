#pragma once
#include "Structures.h"

class Snake;
class SnakeGraphics;
class MapImage;

/*
 * Responsible for all game mechanics:
 * Snake movement, Spawn food, game speed and etc
 */
class SnakeGame
{
/////////////////////////
//Variables
protected:
    const string saveGameFilename = "save.txt";

    //SecondsPerMove for different difficults
    const float easySecondsPerMove       = 0.08f;
    const float mediumSecondsTimePerMove = 0.06f;
    const float hardSecondsTimePerMove   = 0.04f;
    const float turboSecondsTimePerMove  = 0.02f;

    Uint32 easyMaxLength;
    Uint32 mediumMaxLength;
    Uint32 hardMaxLength;
    Uint32 turboMaxLength;
    bool isNewRecord;
    Uint32 wallsCount;

    Vector2b fieldSize;
    GameState gameState;
    Difficult difficult;

    Snake* snake;
    CellData** field;
    SnakeGraphics* graphics;
    MapImage* map;

    Clock clock;
    Time timePerMove;
    Time deltaTime;

/////////////////////////
//Functions

/* Initialization */
public:
    SnakeGame(SnakeGraphics* graphics);
    ~SnakeGame();
    
    void initializePlaying();
    void initializeEndGame(bool isPlayerWinned);

/* Mechanics */
public:
    void spawnSnake();
    void spawnNewFood();

    //Called every frame
    void tick();
    void inputMovement(Direction direction);

    void saveResult();
    void loadResult();

    void setMap(MapImage* newMap);
    void loadMap();
    
protected:
    bool isPreviousCell(Vector2b cellCoords, Vector2b prevCellCoords, Direction prevCellDirection);

/* Getters & Setters */
public:
    const CellData getCell(Vector2b coords);
    const CellData getPreviousCell(Vector2b cellCoords);
    const Vector2b getFieldSize();
    const Uint32 getLengthToWin();

    //Getter from Snake to SnakeGraphics
    bool isSnakeHeadReversed();

    void setGameState(GameState newState);
    void setDifficult(Difficult newDifficult);
    void setMaxLength(Uint32 length);

    void setCellType(Vector2b coords, CellType newType);
    void setCellDirection(Vector2b coords, Direction newDirection);
    void setCell(Vector2b coords, CellType newCellType, Direction newDirection);
};

