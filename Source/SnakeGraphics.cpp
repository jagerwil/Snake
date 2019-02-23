#include "SnakeGraphics.h"
#include "SnakeGame.h"
#include "GUI/MainMenu/MainMenuWidget.h"
#include "GUI/MainMenu/ChooseMapWidget.h"
#include "GUI/MainMenu/ChooseDifficultWidget.h"
#include "GUI/PlayingWidget.h"
#include "GUI/GameResultWidget.h"
#include "GUI/MapImage.h"


SnakeGraphics::SnakeGraphics(Vector2i screenSize)
{
    window = new RenderWindow();
    window->create(VideoMode(screenSize.x, screenSize.y), "Snake", Style::Close);
    window->setFramerateLimit(60);

    PlayingWidget::calculateFieldSize(screenSize);
    game = new SnakeGame(this);

    font.loadFromFile(fontFilename);
}

SnakeGraphics::~SnakeGraphics()
{
    delete mainMenu;
    delete chooseMap;
    delete chooseDifficult;
    delete playing;
    delete game;
}

void SnakeGraphics::initializeMainMenu()
{
    delete chooseMap;
    chooseMap = nullptr;
    delete chooseDifficult;
    chooseDifficult = nullptr;

    mainMenu = new MainMenuWidget(window->getSize(), font, this);
}

void SnakeGraphics::initializeChooseMap()
{
    delete mainMenu;
    mainMenu = nullptr;
    delete chooseDifficult;
    chooseDifficult = nullptr;

    chooseMap = new ChooseMapWidget(window->getSize(), font, this);
}

void SnakeGraphics::initializeChooseDifficult()
{
    delete chooseMap;
    chooseMap = nullptr;

    chooseDifficult = new ChooseDifficultWidget(window->getSize(), font, this);
}

void SnakeGraphics::initializePlaying()
{
    delete chooseDifficult;
    chooseDifficult = nullptr;
    
    playing = new PlayingWidget(font, game);
}

void SnakeGraphics::initializeEndGame(Uint32 length, bool isNewRecord, bool bIsWin)
{
    Vector2f widgetCoords = {438.f, 250.f};
    Vector2f widgetSize = {400.f, 260.f};

    if(isNewRecord)
    {
        widgetCoords -= {0.f, 40.f};
        widgetSize += {0.f, 80.f};
    }
    gameResult = new GameResultWidget(widgetCoords, widgetSize, length, isNewRecord, font, this);
    

    if(bIsWin)
    {
        gameResult->setWinText();
    }
    else gameResult->setLoseText();
}

void SnakeGraphics::exitGame()
{
    window->close();
}

bool SnakeGraphics::isWindowOpen()
{
    return window->isOpen();
}

void SnakeGraphics::tick()
{
    if(window == nullptr) return;

    Event event;
    while(window->pollEvent(event))
    {
        if(event.type == Event::Closed)
        {
            window->close();
        }
        
        if(event.type == Event::KeyPressed ||
           event.type == Event::KeyReleased)
        {
            inputKeyboard(event);
        }
        
        if(event.type == Event::MouseButtonPressed ||
           event.type == Event::MouseButtonReleased)
        {
            inputMouse(event);
        }
    }

    window->clear();
    game->tick();
    window->display();
}

void SnakeGraphics::nextMap()
{
    if(chooseMap != nullptr)
    {
        chooseMap->nextMap();
    }
}

void SnakeGraphics::previousMap()
{
    if(chooseMap != nullptr)
    {
        chooseMap->previousMap();
    }
}

void SnakeGraphics::inputKeyboard(const Event& event)
{
    //Events for pressed buttons
    if(event.type == Event::KeyPressed)
    {
        switch(event.key.code)
        {
        case Keyboard::Escape:
            game->setGameState(GameState::MainMenu);
            break;

        case Keyboard::W:
        case Keyboard::Up:
            game->inputMovement(Direction::Up);
            break;

        case Keyboard::A:
        case Keyboard::Left:
            game->inputMovement(Direction::Left);
            previousMap();
            break;

        case Keyboard::S:
        case Keyboard::Down:
            game->inputMovement(Direction::Down);
            break;

        case Keyboard::D:
        case Keyboard::Right:
            game->inputMovement(Direction::Right);
            nextMap();
            break;

        case Keyboard::Enter:
            if(chooseMap != nullptr)
            {
                chooseMap->confirmChoice();
            }
        }
    }
}

void SnakeGraphics::inputMouse(const Event& event)
{
    Vector2i mousePosition = Mouse::getPosition(*window);

    if(event.type == Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == Mouse::Left)
        {
            if(mainMenu != nullptr)
            {
                mainMenu->clickOnButton(mousePosition);
            }
            else if(chooseMap != nullptr)
            {
                chooseMap->clickOnButton(mousePosition);
            }
            else if(chooseDifficult != nullptr)
            {
                chooseDifficult->clickOnButton(mousePosition);
            }
            else if(gameResult != nullptr)
            {
                gameResult->clickOnButton(mousePosition);
            }
        }
    }
}

void SnakeGraphics::drawMainMenu()
{
    if(mainMenu != nullptr)
    {
        mainMenu->draw(window);
    }
}

void SnakeGraphics::drawChooseMap()
{
    if(chooseMap != nullptr)
    {
        chooseMap->draw(window);
    }
}

void SnakeGraphics::drawChooseDifficult()
{
    if(chooseDifficult != nullptr)
    {
        chooseDifficult->draw(window);
    }
}

void SnakeGraphics::drawPlaying()
{
    if (playing != nullptr)
    {
        playing->draw(window);
    }
}

void SnakeGraphics::drawEndGame()
{
    drawPlaying();
    gameResult->draw(window);
}

void SnakeGraphics::updateCell(Vector2b coords)
{
    CellData cell = game->getCell(coords);
    playing->updateCell(cell, coords);
}

void SnakeGraphics::updateSnakeLength(Uint32 length, Uint32 maxLength)
{
    playing->updateSnakeLength(length, maxLength);
}

const Vector2b& SnakeGraphics::getFieldSize()
{
    return PlayingWidget::getFieldSize();
}

void SnakeGraphics::setGameState(GameState gameState)
{
    game->setGameState(gameState);
}

void SnakeGraphics::setDifficult(Difficult difficult)
{
    game->setDifficult(difficult);
}

void SnakeGraphics::setMap(MapImage* map)
{
    game->setMap(map);
}
