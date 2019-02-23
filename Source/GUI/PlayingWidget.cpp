#include "PlayingWidget.h"
#include "SnakeGame.h"

Vector2b PlayingWidget::textureSize = Vector2b{ 8,  8};
Vector2b PlayingWidget::cellSize    = Vector2b{32, 32};
Vector2b PlayingWidget::fieldSize   = Vector2b{ 0,  0};


PlayingWidget::PlayingWidget(const Font& font, SnakeGame* game):
    font {font},
    game {game}
{
    bIsInitialized = false;
    initialize();
}

void PlayingWidget::initialize()
{
    if(bIsInitialized) return;

    texture.loadFromFile(textureFilename);

    spritesField = new Sprite*[fieldSize.x];
    for(Int8 x = 0; x < fieldSize.x; ++x)
    {
        spritesField[x] = new Sprite[fieldSize.y];

        for(Int8 y = 0; y < fieldSize.y; ++y)
        {
            Sprite& sprite = spritesField[x][y];
            sprite.setTexture(texture);

            Vector2f scale = {(float)cellSize.x / textureSize.x, (float)cellSize.x / textureSize.y};
            sprite.setScale(scale);
        }
    }

    snakeLengthText.setFont(font);
    snakeLengthText.setCharacterSize(50);
    snakeLengthText.setPosition(Vector2f{10.f, 0.f});
    snakeLengthText.setFillColor(Color(128, 128, 128));

    bIsInitialized = true;
}

void PlayingWidget::calculateFieldSize(Vector2i screenSize)
{
    fieldSize.x = screenSize.x / cellSize.x;
    fieldSize.y = (screenSize.y - 64) / cellSize.y;
}

void PlayingWidget::draw(RenderWindow* window)
{
    for(Int8 x = 0; x < fieldSize.x; ++x)
    {
        for(Int8 y = 0; y < fieldSize.y; ++y)
        {
            window->draw(spritesField[x][y]);
        }
    }

    window->draw(snakeLengthText);
}

void PlayingWidget::updateSnakeLength(Uint32 length, Uint32 maxLength)
{
    snakeLengthText.setString("Length: " + to_string(length) + "     Max length: " + to_string(maxLength));
}

void PlayingWidget::updateCell(CellData cell, Vector2b coords)
{
    Sprite& sprite = spritesField[coords.x][coords.y];

    setSpriteTexture(sprite, cell, coords);
    sprite.setPosition(float(coords.x * cellSize.x), float(coords.y * cellSize.y + 64.f));
    setSpriteRotation(sprite, cell, coords);
}

void PlayingWidget::setSpriteTexture(Sprite& sprite, CellData cell, Vector2b cellCoords)
{
    Vector2b texturePosition = {0, 0};

    switch(cell.type)
    {
    case CellType::EmptyCell:
        texturePosition = {0, 0};
        break;

    case CellType::Food:
        texturePosition = {8, 0};
        break;

    case CellType::Wall:
        texturePosition = {16, 0};
        break;

    case CellType::SnakeTail:
        texturePosition = {0, 8};
        break;

    case CellType::SnakeTailFood:
        texturePosition = {0, 16};
        break;

    case CellType::SnakeBodyFood:
        texturePosition = {0, 8};
        //break not needed

    case CellType::SnakeBody:
    {
        CellData prevCell = game->getPreviousCell(cellCoords);

        if((prevCell.type == CellType::SnakeBody ||
            prevCell.type == CellType::SnakeTail ||
            prevCell.type == CellType::SnakeBodyFood ||
            prevCell.type == CellType::SnakeTailFood) &&
            prevCell.direction == cell.direction)
        {
            texturePosition += {8, 8};
        }
        else texturePosition += {16, 8};
        break;
    }

    case CellType::SnakeHead:
        if(game->isSnakeHeadReversed())
        {
            texturePosition = {24, 8};
        }
        else texturePosition = {24, 0};
        break;
    }

    sprite.setTextureRect(IntRect(texturePosition.x, texturePosition.y, textureSize.x, textureSize.y));
}

void PlayingWidget::setSpriteRotation(Sprite& sprite, CellData cell, Vector2b cellCoords)
{
    float angle = 0.f;
    Vector2f offset = {0.f, 0.f};

    switch(cell.direction)
    {
    case Direction::Up:
        angle = -90.f;
        break;
    case Direction::Down:
        angle = 90.f;
        break;
    case Direction::Left:
        angle = 180.f;
        break;
    }

    if(cell.type == CellType::SnakeBody || cell.type == CellType::SnakeBodyFood)
    {
        CellData prevCell = game->getPreviousCell(cellCoords);
        Direction direction = relativeDirection(prevCell.direction, cell.direction);

        if(direction == Direction::Left)
        {
            angle -= 90.f;
        }
    }

    if(angle == -90.f)
    {
        offset = {0.f, (float)cellSize.y};
    }
    else if(angle == 180.f || angle == -180.f)
    {
        offset = {(float)cellSize.x, (float)cellSize.y};
    }
    else if(angle == 90.f)
    {
        offset = {(float)cellSize.x, 0.f};
    };

    sprite.setRotation(angle);
    sprite.move(offset);
}

const Vector2b& PlayingWidget::getFieldSize()
{
    return fieldSize;
}
