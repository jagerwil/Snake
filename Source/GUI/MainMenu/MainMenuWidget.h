#pragma once
#include "Structures.h"

class StartGameButton;
class ExitButton;
class ChooseDifficultButton;
class BackToMainMenuButton;
class SnakeGraphics;


class MainMenuWidget
{
//Variables
protected:
    const string mainMenuBackgroundFilename = "Textures/background_back.png";
    const Vector2u& screenSize;
    const Font& font;

    Texture backgroundTexture;
    Sprite background;

    StartGameButton* startGameButton;
    ExitButton* exitButton;

    SnakeGraphics* graphics;

    bool isInitialized = false;

public:
    MainMenuWidget(Vector2u screenSize, const Font& font, SnakeGraphics* graphics);
    ~MainMenuWidget();

    void initialize();
    void unitialize();

    void draw(RenderWindow* window);
    void clickOnButton(Vector2i mouseCoords);
};
