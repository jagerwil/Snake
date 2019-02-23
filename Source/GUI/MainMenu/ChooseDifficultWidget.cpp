#include "ChooseDifficultWidget.h"
#include "GUI/Buttons.h"


ChooseDifficultWidget::ChooseDifficultWidget(Vector2u screenSize, const Font& font, SnakeGraphics* graphics):
    graphics{graphics},
    screenSize{screenSize},
    font{font}
{
    title.setFont(font);
    title.setFillColor(Color::Black);
    isInitialized = false;
    initialize();
}

ChooseDifficultWidget::~ChooseDifficultWidget()
{
    unitialize();
}

void ChooseDifficultWidget::initialize()
{
    if(!isInitialized)
    {
        title.setCharacterSize(120);
        title.setPosition(Vector2f{270.f, 50.f});
        title.setString("Choose difficult");

        Vector2f buttonSize = {400.f, 100.f};
        Vector2f buttonOffset = {0, buttonSize.y * (float)1.2};

        Vector2f easyButtonCoords = {/* x = */(screenSize.x - buttonSize.x) / 2,
            /* y = */ screenSize.x / 3 - buttonSize.y * 2};
        Vector2f mediumButtonCoords = easyButtonCoords + buttonOffset;
        Vector2f hardButtonCoords = mediumButtonCoords + buttonOffset;
        Vector2f turboButtonCoords = hardButtonCoords + buttonOffset;

        difficultEasyButton = new ChooseDifficultButton(easyButtonCoords, buttonSize, font, Difficult::Easy);
        difficultMediumButton = new ChooseDifficultButton(mediumButtonCoords, buttonSize, font, Difficult::Medium);
        difficultHardButton = new ChooseDifficultButton(hardButtonCoords, buttonSize, font, Difficult::Hard);
        difficultTurboButton = new ChooseDifficultButton(turboButtonCoords, buttonSize, font, Difficult::Turbo);

        Vector2f backToMenuButtonCoords = {33.f, screenSize.y - (64.f + 33.f)};
        Vector2f backToMenuButtonSize = {64.f, 64.f};

        backToMapButton = new BackToChooseMapButton(backToMenuButtonCoords, backToMenuButtonSize);

        backgroundTexture.loadFromFile(backgroundFilename);

        background.setTexture(backgroundTexture);
        background.setTextureRect(sf::IntRect(0, 0, screenSize.x, screenSize.y));

        isInitialized = true;
    }
}

void ChooseDifficultWidget::unitialize()
{
    if(isInitialized)
    {
        delete difficultEasyButton;
        difficultEasyButton = nullptr;

        delete difficultMediumButton;
        difficultMediumButton = nullptr;

        delete difficultHardButton;
        difficultHardButton = nullptr;

        delete difficultTurboButton;
        difficultTurboButton = nullptr;

        delete backToMapButton;
        backToMapButton = nullptr;

        isInitialized = false;
    }
}

void ChooseDifficultWidget::draw(RenderWindow* window)
{
    if(isInitialized)
    {
        window->draw(background);
        window->draw(title);

        difficultEasyButton->drawButton(window);
        difficultMediumButton->drawButton(window);
        difficultHardButton->drawButton(window);
        difficultTurboButton->drawButton(window);

        backToMapButton->drawButton(window);
    }
}

void ChooseDifficultWidget::clickOnButton(Vector2i mouseCoords)
{
    if(isInitialized)
    {
        if(difficultEasyButton->isHovered(mouseCoords))
        {
            difficultEasyButton->onClick(graphics);
        }
        else if(difficultMediumButton->isHovered(mouseCoords))
        {
            difficultMediumButton->onClick(graphics);
        }
        else if(difficultHardButton->isHovered(mouseCoords))
        {
            difficultHardButton->onClick(graphics);
        }
        else if(difficultTurboButton->isHovered(mouseCoords))
        {
            difficultTurboButton->onClick(graphics);
        }
        else if(backToMapButton->isHovered(mouseCoords))
        {
            backToMapButton->onClick(graphics);
        }
    }
}
