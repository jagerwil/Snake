#pragma once
#include "Structures.h"

class RestartGameButton;
class SnakeGraphics;


class GameResultWidget : public RectangleShape
{
protected:
    Uint32 length;
    Uint32 maxLength;
    RestartGameButton* restartButton;

    Text titleText;
    Text resultText;
    Text newRecord;

    SnakeGraphics* graphics;

public:
    GameResultWidget(Vector2f coords, Vector2f size, Uint32 length, bool isNewRecord, 
                     const Font& font, SnakeGraphics* graphics);
    void setWinText();
    void setLoseText();
    void clickOnButton(Vector2i mouseCoords);

    void draw(RenderWindow* window);
};