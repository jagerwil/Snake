#pragma once
#include "Structures.h"

class SnakeGame;


class PlayingWidget
{
//Variables
protected:
    const std::string textureFilename = "Textures/snake_sprite.png";

    static Vector2b textureSize /* = { 8,  8} */;
    static Vector2b cellSize    /* = {32, 32} */;
    static Vector2b fieldSize;

    Texture texture;
    Sprite** spritesField;

    const Font& font;
    Text snakeLengthText;

    bool bIsInitialized;
    SnakeGame* game; ///Replace to SnakeGraphics

//Functions
public:
    PlayingWidget(const Font& font, SnakeGame* game);
    void initialize();

    static void calculateFieldSize(Vector2i screenSize);
    void draw(RenderWindow* window);

    void updateSnakeLength(Uint32 length, Uint32 maxLength);
    void updateCell(CellData cell, Vector2b coords);

    static const Vector2b& getFieldSize();

protected:
    void setSpriteTexture(Sprite& sprite, CellData cell, Vector2b cellCoords);
    void setSpriteRotation(Sprite& sprite, CellData cell, Vector2b cellCoords);
};