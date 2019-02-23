#pragma once
#include "Structures.h"

class ChooseDifficultButton;
class BackToChooseMapButton;
class SnakeGraphics;


class ChooseDifficultWidget
{
protected:
    const string backgroundFilename = "Textures/background_choose_difficult.png";
    const Vector2u& screenSize;
    const Font& font;

    Texture backgroundTexture;
    Sprite background;
    
    Text title;
    bool isInitialized;

    ChooseDifficultButton* difficultEasyButton;
    ChooseDifficultButton* difficultMediumButton;
    ChooseDifficultButton* difficultHardButton;
    ChooseDifficultButton* difficultTurboButton;
    BackToChooseMapButton* backToMapButton;

    SnakeGraphics* graphics;
    
public:
    ChooseDifficultWidget(Vector2u screenSize, const Font& font, SnakeGraphics* graphics);
    ~ChooseDifficultWidget();

    void initialize();
    void unitialize();

    void draw(RenderWindow* window);
    void clickOnButton(Vector2i mouseCoords);
};

