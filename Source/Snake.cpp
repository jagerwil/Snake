#include "Snake.h"
#include "SnakeGame.h"


Snake::Snake(SnakeGame* game):
    game{game}
{
    lengthToWin = game->getLengthToWin();
}

void Snake::init(Vector2b headCoords)
{
    length = 2; //head and tail
    game->setMaxLength(length);

    head.setCoords(headCoords);
    head.setType(CellType::SnakeHead);
    head.setDirection(Direction::Right);
    game->setCell(headCoords, CellType::SnakeHead, Direction::Right);

    Vector2b tailCoords = headCoords + Vector2b{-1, 0};
    tail.setCoords(tailCoords);
    tail.setType(CellType::SnakeTail);
    tail.setDirection(Direction::Right);
    game->setCell(tailCoords, CellType::SnakeTail, Direction::Right);

    rotateDirection = Direction::Right;

    hasFoodBeenEaten = false;
    isHeadReversed = false;
}

void Snake::inputMovement(Direction direction)
{
    rotateDirection = direction;
}

void Snake::turn()
{
    rotate(rotateDirection);
    checkHeadReverse();

    Vector2b nextHeadCoords = head.nextCellCoords(game->getFieldSize());

    CellData cell = game->getCell(nextHeadCoords);
    bool isSnakeGrowing = false;
    bool isSnakeDied = false;

    if (cell.type == CellType::Food)
    {
        isSnakeGrowing = true;
    }
    else if (cell.type != CellType::EmptyCell)
    {
        isSnakeDied = true;
    }

    if (isSnakeDied)
    {
        game->setGameState(GameState::PlayerLosed);
    }
    else
    {
        moveForward(nextHeadCoords, isSnakeGrowing);
    }
}

void Snake::rotate(Direction direction)
{
    //If relative direction are Left or Right
    if(relativeDirection(direction, head.getDirection()) != Direction::None)
    {
        head.setDirection(direction);
        game->setCellDirection(head.getCoords(), direction);
    }
    else
    {
        rotateDirection = head.getDirection();
    }
}

void Snake::moveForward(Vector2b nextHeadCoords, bool isSnakeGrowing)
{
    moveForwardHead(nextHeadCoords);
    moveForwardTail();

    if(isSnakeGrowing)
    {
        hasFoodBeenEaten = true;

        ++length;
        game->setMaxLength(length);

        if(length >= lengthToWin)
        {
            game->setGameState(GameState::PlayerWinned);
        }
        else game->spawnNewFood();
    }
    
}

void Snake::moveForwardHead(Vector2b headCoords)
{
    Vector2b headPrevCoords = head.getCoords();
    CellType bodyType = CellType::SnakeBody;

    if(hasFoodBeenEaten)
    {
        bodyType = CellType::SnakeBodyFood;
        hasFoodBeenEaten = false;
    }

    game->setCellType(headPrevCoords, bodyType);

    head.setCoords(headCoords);
    game->setCell(headCoords, CellType::SnakeHead, head.getDirection());
}

void Snake::moveForwardTail()
{
    Vector2b tailPrevCoords = tail.getCoords();
    Vector2b tailNextCoords = tail.nextCellCoords(game->getFieldSize());

    if(tail.getType() == CellType::SnakeTailFood)
    {
        tail.setType(CellType::SnakeTail);
        game->setCellType(tailPrevCoords, CellType::SnakeTail);
    }
    else
    {
        game->setCell(tailPrevCoords, CellType::EmptyCell, Direction::None);

        CellData tailCell = game->getCell(tailNextCoords);
        tail.setCoords(tailNextCoords);
        tail.setDirection(tailCell.direction);
        
        if(game->getCell(tailNextCoords).type == CellType::SnakeBodyFood)
        {
            tail.setType(CellType::SnakeTailFood);
        }

        game->setCellType(tailNextCoords, tail.getType());
    }
}

void Snake::checkHeadReverse()
{
    if(head.getDirection() == Direction::Left)
    {
        isHeadReversed = true;
    }
    else if(head.getDirection() == Direction::Right)
    {
        isHeadReversed = false;
    }
}

bool Snake::getIsHeadReversed()
{
    return isHeadReversed;
}

Uint32 Snake::getLength()
{
    return length;
}
