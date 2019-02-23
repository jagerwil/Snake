#include "GameResultWidget.h"
#include "SnakeGraphics.h"
#include "Buttons.h"


GameResultWidget::GameResultWidget(Vector2f coords, Vector2f size, Uint32 length, 
                                   bool isNewRecord, const Font& font, SnakeGraphics* graphics)
    :length {length},
    graphics {graphics}
{
    setPosition(coords);
    setSize(size);

    setOutlineThickness(3);
    setOutlineColor(Color(90, 90, 90));
    setFillColor(Color(128, 128, 128));

    titleText.setFont(font);
    titleText.setCharacterSize(60);

    resultText.setFont(font);
    resultText.setFillColor(Color::Black);
    resultText.setCharacterSize(40);
    resultText.setPosition(coords + Vector2f{40.f, 90.f});
    resultText.setString("Length: " + to_string(length));

    if(isNewRecord)
    {
        newRecord.setFont(font);
        newRecord.setFillColor(Color(200, 200, 0));
        newRecord.setCharacterSize(50);
        newRecord.setPosition(coords + Vector2f{70.f, 165.f});
        newRecord.setString("New Record!");
    }

    Vector2f buttonCoords = coords + Vector2f{(size.x - 64.f) / 2, (size.y - 80.f)};
    restartButton = new RestartGameButton(buttonCoords, {64.f, 64.f});
}

void GameResultWidget::setWinText()
{
    titleText.setString("You win!");
    titleText.setFillColor(Color(0, 150, 0));
    titleText.setPosition(getPosition() + Vector2f{95.f, 5.f});
}

void GameResultWidget::setLoseText()
{
    titleText.setString("You lose!");
    titleText.setFillColor(Color(200, 0, 0));
    titleText.setPosition(getPosition() + Vector2f{80.f, 5.f});
}

void GameResultWidget::clickOnButton(Vector2i mouseCoords)
{
    if(restartButton->isHovered(mouseCoords))
    {
        restartButton->onClick(graphics);
    }
}

void GameResultWidget::draw(RenderWindow* window)
{
    window->draw(*this);
    window->draw(titleText);
    window->draw(resultText);
    window->draw(newRecord);
    
    restartButton->drawButton(window);
}
