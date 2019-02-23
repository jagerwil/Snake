#pragma once
#include "Structures.h"
#include "SnakeGraphics.h"
#include "MainMenu/MainMenuWidget.h"
#include "MainMenu/ChooseMapWidget.h"
#include "MainMenu/ChooseDifficultWidget.h"


class Button : public RectangleShape
{
protected:
    float x;
    float y;
    float width;
    float height;
    Text text;

public:
    Button(Vector2f coords, Vector2f size)
    {
        x = coords.x;
        y = coords.y;
        setPosition(coords);

        width = size.x;
        height = size.y;
        setSize(size);

        setOutlineThickness(3);
        setOutlineColor(Color(90, 90, 90));
        setFillColor(Color(128, 128, 128));

        text.setFillColor(Color::Black);
    }

    Button(Vector2f coords, Vector2f size, const Font& font) :
        Button(coords, size)
    {
        text.setFont(font);
        text.setCharacterSize(50);
    }

    virtual void drawButton(RenderWindow* window)
    {
        window->draw(*this);
        window->draw(text);
    }

    bool isHovered(Vector2i mouseCoords)
    {
        if((mouseCoords.x >= x && mouseCoords.x <= x + width) && 
           (mouseCoords.y >= y && mouseCoords.y <= y + height))
        {
            return true;
        }
        else return false;
    }

    virtual void onClick(SnakeGraphics* graphics)
    {
    }
};


class StartGameButton : public Button
{
public:
    StartGameButton(Vector2f coords, Vector2f size, const Font& font)
        :Button(coords, size, font)
    {
        text.setPosition(coords + Vector2f{75.f, 15.f});
        text.setString("Start game");
    }

    void onClick(SnakeGraphics* graphics) override
    {
        graphics->setGameState(GameState::ChooseMap);
    }
};


class ExitButton : public Button
{
public:
    ExitButton(Vector2f coords, Vector2f size, const Font& font)
        :Button(coords, size, font)
    {
        text.setPosition(coords + Vector2f{150, 15.f});
        text.setString("Exit");
    }

    void onClick(SnakeGraphics* graphics) override
    {
        graphics->exitGame();
    }
};


class ChooseDifficultButton : public Button
{
protected:
    Difficult difficult;

public:
    ChooseDifficultButton(Vector2f coords, Vector2f size, const Font& font, Difficult difficult)
        :Button(coords, size, font),
        difficult {difficult}
    {
        switch(difficult)
        {
        case Difficult::Easy:
            text.setString("Easy");
            text.setPosition(coords + Vector2f{140.f, 15.f});
            break;

        case Difficult::Medium:
            text.setString("Medium");
            text.setPosition(coords + Vector2f{110.f, 15.f});
            break;

        case Difficult::Hard:
            text.setString("Hard");
            text.setPosition(coords + Vector2f{140.f, 15.f});
            break;

        case Difficult::Turbo:
            text.setString("Turbo");
            text.setPosition(coords + Vector2f{130.f, 15.f});
            text.setFillColor(Color(200, 0, 0));
            break;
        }
    }

    void onClick(SnakeGraphics* graphics) override
    {
        graphics->setDifficult(difficult);
        graphics->setGameState(GameState::Playing);
    }
};


class BackToMainMenuButton : public Button
{
protected:
    const string foregroundFilename = "Textures/arrow_back.png";

    Texture foregroundTexture;
    Sprite foregroundSprite;

public:
    BackToMainMenuButton(Vector2f coords, Vector2f size)
        :Button(coords, size)
    {
        foregroundTexture.loadFromFile(foregroundFilename);

        foregroundSprite.setTexture(foregroundTexture);
        foregroundSprite.setPosition(coords);
    }

    void onClick(SnakeGraphics* graphics) override
    {
        graphics->setGameState(GameState::MainMenu);
    }

    void drawButton(RenderWindow* window) override
    {
        Button::drawButton(window);
        window->draw(foregroundSprite);
    }
};


class BackToChooseMapButton : public BackToMainMenuButton
{
public:
    BackToChooseMapButton(Vector2f coords, Vector2f size):
        BackToMainMenuButton(coords, size)
    {
    }

    void onClick(SnakeGraphics* graphics) override
    {
        graphics->setGameState(GameState::ChooseMap);
    }
};


class RestartGameButton : public Button
{
protected:
    const string foregroundFilename = "Textures/restart_arrow.png";

    Texture foregroundTexture;
    Sprite foregroundSprite;

public:
    RestartGameButton(Vector2f coords, Vector2f size):
        Button(coords, size)
    {
        foregroundTexture.loadFromFile(foregroundFilename);

        foregroundSprite.setTexture(foregroundTexture);
        foregroundSprite.setPosition(coords);
    }

    void onClick(SnakeGraphics* graphics) override
    {
        graphics->setGameState(GameState::Playing);
    }

    void drawButton(RenderWindow* window) override
    {
        Button::drawButton(window);
        window->draw(foregroundSprite);
    }
};


class PreviousMapButton : public Button
{
protected:
    const string foregroundFilename = "Textures/arrow_prev.png";

    Texture foregroundTexture;
    Sprite foregroundSprite;

public:
    PreviousMapButton(Vector2f coords, Vector2f size):
        Button(coords, size)
    {
        foregroundTexture.loadFromFile(foregroundFilename);

        foregroundSprite.setTexture(foregroundTexture);
        foregroundSprite.setPosition(coords);

        setOutlineColor(Color(90, 90, 90, 0));
        setFillColor(Color(128, 128, 128, 0));
    }

    void onClick(SnakeGraphics* graphics) override
    {
        graphics->previousMap();
    }

    void drawButton(RenderWindow* window) override
    {
        Button::drawButton(window);
        window->draw(foregroundSprite);
    }
};


class NextMapButton : public Button
{
protected:
    const string foregroundFilename = "Textures/arrow_next.png";

    Texture foregroundTexture;
    Sprite foregroundSprite;

public:
    NextMapButton(Vector2f coords, Vector2f size):
        Button(coords, size)
    {
        foregroundTexture.loadFromFile(foregroundFilename);

        foregroundSprite.setTexture(foregroundTexture);
        foregroundSprite.setPosition(coords);

        setOutlineColor(Color(90, 90, 90, 0));
        setFillColor(Color(128, 128, 128, 0));
    }

    void onClick(SnakeGraphics* graphics) override
    {
        graphics->nextMap();
    }

    void drawButton(RenderWindow* window) override
    {
        Button::drawButton(window);
        window->draw(foregroundSprite);
    }
};
