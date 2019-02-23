#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using std::string;
using std::to_string;

typedef Vector2<Int8> Vector2b; //char == byte

/*
 * Used for storing game state in SnakeGame
 */
enum class GameState
{
    StartGame,
    ChooseMap,
    ChooseDifficult,
    MainMenu,
    Playing,
    PlayerWinned,
    PlayerLosed
};

/*
 * Used for determine difficult in SnakeGame
 */
enum class Difficult
{
    Easy,
    Medium,
    Hard,
    Turbo
};

/*
 * Used for storing type of cell
 * If cell are invalid, equal to CellType::Border
 */
enum class CellType
{
    EmptyCell,
    Food,
    Wall,
    SnakeTail,
    SnakeTailFood,
    SnakeBody,
    SnakeBodyFood,
    SnakeHead,
    Border
};

/*
 * Used for storing move direction of cell (if cell belongs to snake),
 * Else equal to Direction::None
 */
enum Direction
{
    Up,
    Down,
    Left,
    Right,
    None
};

/*
 * Used for storing cells in game field
 */
struct CellData
{
    CellType type = CellType::EmptyCell;
    Direction direction = Direction::None;
};


Vector2b directionToCoords(Direction direction);

//Relative direction of first direction to second
//If directions equal or opposite, return Direction::None
Direction relativeDirection(Direction direction1, Direction direction2);