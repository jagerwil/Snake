#pragma once
#include "Structures.h"

class SnakeGame;
class MainMenuWidget;
class ChooseMapWidget;
class ChooseDifficultWidget;
class PlayingWidget;
class GameResultWidget;
class MapImage;


/*
 * Responsible for graphics of game:
 * Draw menu, game field, snake and etc
 * Handles events (and redirect them to SnakeGame)
 */
class SnakeGraphics
{
/////////////////////////
//Variables
protected:
    const string fontFilename = "Textures/cyrillic_font.ttf";

    SnakeGame* game;
    RenderWindow* window;

    MainMenuWidget* mainMenu;
    ChooseMapWidget* chooseMap;
    ChooseDifficultWidget* chooseDifficult;

    PlayingWidget* playing;
    GameResultWidget* gameResult;

    Font font;

/////////////////////////
//Functions

/* Initialization */
public:
    SnakeGraphics(Vector2i screenSize);
    ~SnakeGraphics();
    void initializeMainMenu();
    void initializeChooseMap();
    void initializeChooseDifficult();
    void initializePlaying();
    void initializeEndGame(Uint32 length, bool isNewRecord, bool bIsWin);

/* Mechanics */
public:
    void exitGame();

    //Called every frame
    void tick();

/* Graphics */
public:
    void drawMainMenu();
    void drawChooseMap();
    void drawChooseDifficult();
    void drawPlaying();
    void drawEndGame();

    void updateCell(Vector2b coords);
    void updateSnakeLength(Uint32 length, Uint32 maxlength);

/* Handling events */
public:
    void nextMap();
    void previousMap();

protected:
    void inputKeyboard(const Event& event);
    void inputMouse(const Event& event);

/* Getters & Setters */
public:
    const Vector2b& getFieldSize();
    bool isWindowOpen();

    void setGameState(GameState gameState);
    void setDifficult(Difficult difficult);
    void setMap(MapImage* map);
};

