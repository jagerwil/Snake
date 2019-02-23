#include "SnakeGame.h"
#include "SnakeGraphics.h"
#include "Snake.h"
#include "GUI/MapImage.h"
#include <cstdlib>
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::endl;
using std::ios;


SnakeGame::SnakeGame(SnakeGraphics* graphics):
    graphics {graphics}
{
    easyMaxLength   = 2;
    mediumMaxLength = 2;
    hardMaxLength   = 2;
    turboMaxLength  = 2;
    isNewRecord = false;

    wallsCount = 0;

    srand(static_cast<Uint32>(time(0)));
    fieldSize = graphics->getFieldSize();

    gameState = GameState::StartGame;
    setGameState(GameState::MainMenu);

    loadResult();
}

SnakeGame::~SnakeGame()
{
    delete snake;
    delete field;
}

void SnakeGame::initializePlaying()
{
    if(snake == nullptr)
    {
        snake = new Snake(this);
    }

    graphics->initializePlaying();

    if(field == nullptr)
    {
        field = new CellData*[fieldSize.x];

        for(Int8 x = 0; x < fieldSize.x; ++x)
        {
            field[x] = new CellData[fieldSize.y];
        }
    }

    setDifficult(difficult);
    loadMap();

    clock.restart(); 
    deltaTime = seconds(0.f);

    isNewRecord = false;
    spawnSnake();
    spawnNewFood();
}

void SnakeGame::initializeEndGame(bool isPlayerWinned)
{
    graphics->initializeEndGame(snake->getLength(), isNewRecord,  isPlayerWinned);
}

void SnakeGame::spawnSnake()
{
    snake->init({4, 2});
}

void SnakeGame::spawnNewFood()
{
    Vector2b foodCoords = {-1, -1};

    while(getCell(foodCoords).type != CellType::EmptyCell)
    {
        foodCoords.x = rand() % fieldSize.x;
        foodCoords.y = rand() % fieldSize.y;
    }

    setCellType(foodCoords, CellType::Food);
}

void SnakeGame::tick()
{
    if (gameState == GameState::MainMenu)
    {
        graphics->drawMainMenu();
    }
    else if(gameState == GameState::ChooseMap)
    {
        graphics->drawChooseMap();
    }
    if(gameState == GameState::ChooseDifficult)
    {
        graphics->drawChooseDifficult();
    }
    else if (gameState == GameState::Playing)
    {
        if(snake == nullptr)
        {
            return;
        }

        Time currentMoveTime = clock.getElapsedTime() + deltaTime;
        if (currentMoveTime >= timePerMove)
        {
            snake->turn();

            deltaTime = currentMoveTime - timePerMove;
            clock.restart();
        }

        graphics->drawPlaying();
    }
    else if (gameState == GameState::PlayerWinned ||
             gameState == GameState::PlayerLosed)
    {
        graphics->drawEndGame();
    }
}

void SnakeGame::inputMovement(Direction direction)
{
    if (gameState == GameState::Playing && snake != nullptr)
    {
        snake->inputMovement(direction);
    }
}

void SnakeGame::saveResult()
{
    ofstream saveFile;
    saveFile.open(saveGameFilename);

    saveFile << easyMaxLength << endl
        << mediumMaxLength << endl
        << hardMaxLength   << endl
        << turboMaxLength  << endl;

    saveFile.close();
}

void SnakeGame::loadResult()
{
    ifstream loadFile;
    loadFile.open(saveGameFilename, ios::_Nocreate);

    if(loadFile.is_open())
    {
        loadFile >> easyMaxLength
            >> mediumMaxLength
            >> hardMaxLength
            >> turboMaxLength;
    }
}

void SnakeGame::setMap(MapImage* newMap)
{
    map = newMap;
}

void SnakeGame::loadMap()
{
    CellType cellType;

    for(Int8 x = 0; x < fieldSize.x; ++x)
    {
        for(Int8 y = 0; y < fieldSize.y; ++y)
        {
            cellType = map->pixelToCellType({x, y});
            setCell(Vector2b{x, y}, cellType, Direction::None);
        }
    }
}

bool SnakeGame::isPreviousCell(Vector2b cellCoords, Vector2b prevCellCoords, Direction prevCellDirection)
{
    CellData previousCell = getCell(prevCellCoords);

    if(previousCell.type != CellType::Border && previousCell.direction == prevCellDirection)
    {
        return true;
    }
    else return false;
}

const CellData SnakeGame::getCell(Vector2b coords)
{
    if (coords.x >= fieldSize.x || coords.x < 0 ||
        coords.y >= fieldSize.y || coords.y < 0)
    {
        return CellData{CellType::Border};
    }

    CellData returnValue = field[coords.x][coords.y];

    return returnValue;
}

const CellData SnakeGame::getPreviousCell(Vector2b cellCoords)
{
    Vector2b prevCellCoords;

    prevCellCoords = cellCoords - directionToCoords(Direction::Up);
    if(isPreviousCell(cellCoords, prevCellCoords, Direction::Up))
    {
        return getCell(prevCellCoords);
    }

    prevCellCoords = cellCoords - directionToCoords(Direction::Down);
    if(isPreviousCell(cellCoords, prevCellCoords, Direction::Down))
    {
        return getCell(prevCellCoords);
    }

    prevCellCoords = cellCoords - directionToCoords(Direction::Left);
    if(isPreviousCell(cellCoords, prevCellCoords, Direction::Left))
    {
        return getCell(prevCellCoords);
    }

    prevCellCoords = cellCoords - directionToCoords(Direction::Right);
    if(isPreviousCell(cellCoords, prevCellCoords, Direction::Right))
    {
        return getCell(prevCellCoords);
    }

    return CellData();
}

const Vector2b SnakeGame::getFieldSize()
{
    return fieldSize;
}

const Uint32 SnakeGame::getLengthToWin()
{
    return fieldSize.x * fieldSize.y - wallsCount;
}

bool SnakeGame::isSnakeHeadReversed()
{
    return snake->getIsHeadReversed();
}

void SnakeGame::setGameState(GameState newState)
{
    if(gameState == newState) return;
        
    gameState = newState;
    switch(gameState)
    {
    case GameState::MainMenu:
        graphics->initializeMainMenu();
        break;

    case GameState::ChooseMap:
        graphics->initializeChooseMap();
        break;

    case GameState::ChooseDifficult:
        graphics->initializeChooseDifficult();
        break;

    case GameState::Playing:
        initializePlaying();
        break;

    case GameState::PlayerWinned:
        initializeEndGame(true);
        break;
    
    case GameState::PlayerLosed:
        initializeEndGame(false);
        break;
    }
}

void SnakeGame::setDifficult(Difficult newDifficult)
{
    difficult = newDifficult;
    float secondsPerMove = 0.f;

    switch(newDifficult)
    {
    case Difficult::Easy:
        secondsPerMove = easySecondsPerMove;
        break;

    case Difficult::Medium:
        secondsPerMove = mediumSecondsTimePerMove;
        break;

    case Difficult::Hard:
        secondsPerMove = hardSecondsTimePerMove;
        break;

    case Difficult::Turbo:
        secondsPerMove = turboSecondsTimePerMove;
        break;
    }

    timePerMove = seconds(secondsPerMove);
}

void SnakeGame::setMaxLength(Uint32 length)
{
    Uint32 maxLength = 0;

    switch(difficult)
    {
    case Difficult::Easy:
        if (length > easyMaxLength)
        {
            easyMaxLength = length;
            saveResult();
            isNewRecord = true;
        }
        maxLength = easyMaxLength;
        break;

    case Difficult::Medium:
        if(length > mediumMaxLength)
        {
            mediumMaxLength = length;
            saveResult();
            isNewRecord = true;
        }
        maxLength = mediumMaxLength;
        break;

    case Difficult::Hard:
        if(length > hardMaxLength)
        {
            hardMaxLength = length;
            saveResult();
            isNewRecord = true;
        }
        maxLength = hardMaxLength;
        break;

    case Difficult::Turbo:
        if(length > turboMaxLength)
        {
            turboMaxLength = length;
            saveResult();
            isNewRecord = true;
        }
        maxLength = turboMaxLength;
        break;
    }

    graphics->updateSnakeLength(length, maxLength);
}

void SnakeGame::setCellType(Vector2b coords, CellType newType)
{
    if (coords.x < fieldSize.x || coords.y < fieldSize.y)
    {
        field[coords.x][coords.y].type = newType;
        graphics->updateCell(coords);
    }
}

void SnakeGame::setCellDirection(Vector2b coords, Direction newDirection)
{
    if (coords.x < fieldSize.x || coords.y < fieldSize.y)
    {
        field[coords.x][coords.y].direction = newDirection;
        graphics->updateCell(coords);
    }
}

void SnakeGame::setCell(Vector2b coords, CellType newType, Direction newDirection)
{
    if (coords.x < fieldSize.x || coords.y < fieldSize.y)
    {
        field[coords.x][coords.y].type = newType;
        field[coords.x][coords.y].direction = newDirection;
        graphics->updateCell(coords);
    }
}


