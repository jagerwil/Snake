#include "MainMenuWidget.h"
#include "GUI/Buttons.h"


MainMenuWidget::MainMenuWidget(Vector2u screenSize, const Font& font, SnakeGraphics* graphics) :
    graphics {graphics},
    screenSize {screenSize},
    font {font}
{
    isInitialized = false;
    initialize();
}

MainMenuWidget::~MainMenuWidget()
{
    unitialize();
}

void MainMenuWidget::initialize()
{
    if(!isInitialized)
    {
        Vector2f buttonSize = {400.f, 100.f};
        Vector2f buttonOffset = {0, buttonSize.y * (float)1.3};

        Vector2f startButtonCoords = {/* x = */(screenSize.x - buttonSize.x) / 2,
            /* y = */(screenSize.x - buttonSize.y * 2) / 3};
        Vector2f exitButtonCoords = startButtonCoords + buttonOffset;

        startGameButton = new StartGameButton(startButtonCoords, buttonSize, font);
        exitButton = new ExitButton(exitButtonCoords, buttonSize, font);

        backgroundTexture.loadFromFile(mainMenuBackgroundFilename);

        background.setTexture(backgroundTexture);
        background.setTextureRect(sf::IntRect(0, 0, screenSize.x, screenSize.y));

        isInitialized = true;
    }
}

void MainMenuWidget::unitialize()
{
    if(isInitialized)
    {
        delete startGameButton;
        startGameButton = nullptr;

        delete exitButton;
        exitButton = nullptr;

        isInitialized = false;
    }
}
void MainMenuWidget::draw(RenderWindow* window)
{
    if(isInitialized)
    {
        window->draw(background);

        startGameButton->drawButton(window);
        exitButton->drawButton(window);
    }
}

void MainMenuWidget::clickOnButton(Vector2i mouseCoords)
{
    if(isInitialized)
    {
        if(startGameButton->isHovered(mouseCoords))
        {
            startGameButton->onClick(graphics);
        }
        else if(exitButton->isHovered(mouseCoords))
        {
            exitButton->onClick(graphics);
        }
    }
}