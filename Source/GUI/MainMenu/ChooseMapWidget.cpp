#include "ChooseMapWidget.h"
#include "SnakeGraphics.h"
#include "GUI/MapImage.h"
#include "GUI/Buttons.h"
#include <fstream>
using std::ifstream;
using std::getline;
using std::vector;


Vector2b ChooseMapWidget::textureSize = Vector2b{8,  8};


ChooseMapWidget::ChooseMapWidget(Vector2u screenSize, const Font& font, SnakeGraphics* graphics):
    graphics{graphics},
    screenSize{screenSize},
    font{font}
{
    mapInfo.setFont(font);
    mapInfo.setFillColor(Color::Black);
    title.setFont(font);
    title.setFillColor(Color::Black);

    mapsCount = 0;
    currentMapNumber = 0;
    isInitialized = false;
    initialize();
}

ChooseMapWidget::~ChooseMapWidget()
{
    unitialize();
}

void ChooseMapWidget::initialize()
{
    if(!isInitialized)
    {
        backgroundTexture.loadFromFile(backgroundFilename);
        background.setTexture(backgroundTexture);
        background.setTextureRect(sf::IntRect(0, 0, screenSize.x, screenSize.y));

        title.setCharacterSize(100);
        title.setPosition(Vector2f{425.f, 50.f});
        title.setString("Choose map");

        texture.loadFromFile(textureFilename);

        ifstream mapsList;
        mapsList.open(mapsListFilename);
        if(!mapsList.is_open()) return;

        string mapName = "";
        while(!mapsList.eof())
        {
            getline(mapsList, mapName, '\n');
            maps.push_back(new MapImage(mapName));

            ++mapsCount;
        }

        Vector2f backToMenuButtonCoords = {33.f, screenSize.y - (64.f + 33.f)};
        Vector2f backToMenuButtonSize = {64.f, 64.f};


        previousMapButton = new PreviousMapButton(Vector2f{260, 320}, {64, 128});
        nextMapButton = new NextMapButton(Vector2f{1050, 320}, {64, 128});
        backToMenuButton = new BackToMainMenuButton(backToMenuButtonCoords, backToMenuButtonSize);

        initializeMap();
    }
}

void ChooseMapWidget::unitialize()
{
    if(isInitialized)
    {
        delete spritesMap;
    }
}

void ChooseMapWidget::nextMap()
{
    if(currentMapNumber >= mapsCount - 1)
    {
        currentMapNumber = 0;
    }
    else ++currentMapNumber;

    initializeMap();
}

void ChooseMapWidget::previousMap()
{
    if(currentMapNumber <= 0)
    {
        currentMapNumber = mapsCount - 1;
    }
    else --currentMapNumber;

    initializeMap();
}

///Debug message
void ChooseMapWidget::initializeMap()
{
    if(currentMapNumber >= mapsCount) return;

    MapImage* map = maps[currentMapNumber];
    mapSize = map->getSize();

    CellType cellType;
    Vector2f spriteCoords = {344.f, 206.f};

    spritesMap = new Sprite*[mapSize.x];
    
    for(Int8 x = 0; x < mapSize.x; ++x)
    {
        spritesMap[x] = new Sprite[mapSize.y];

        for(Int8 y = 0; y < mapSize.y; ++y)
        {
            Sprite& sprite = spritesMap[x][y];
            cellType = map->pixelToCellType(Vector2b{x, y});
            
            sprite.setTexture(texture);
            sprite.setScale(2.f, 2.f);
            sprite.setPosition(spriteCoords + Vector2f{textureSize.x * x * 2.f, textureSize.y * y * 2.f});

            if(cellType == CellType::Wall)
            {
                sprite.setTextureRect(IntRect(16, 0, 8, 8));
            }
            else //if(cellType == CellType::EmptyCell)
            {
                sprite.setTextureRect(IntRect(0, 0, 8, 8));
            }
        }
    }

    Vector2f mapInfoCoords = {688.f, 568.f};
    mapInfo.setPosition(mapInfoCoords);
    mapInfo.setCharacterSize(40);

    string mapName = maps[currentMapNumber]->getMapName();
    mapInfo.setString(mapName);
    mapInfo.move(Vector2f{-20.85f * mapName.size() / 2.f, 0.f});
}

///Debug messages
void ChooseMapWidget::draw(RenderWindow* window)
{
    window->draw(background);
    window->draw(title);

    for(Int8 x = 0; x < mapSize.x; ++x)
    {
        for(Int8 y = 0; y < mapSize.y; ++y)
        {
            window->draw(spritesMap[x][y]);
        }
    }

    window->draw(mapInfo);
    previousMapButton->drawButton(window);
    nextMapButton->drawButton(window);
    backToMenuButton->drawButton(window);
}

void ChooseMapWidget::clickOnButton(Vector2i mouseCoords)
{
    if(previousMapButton->isHovered(mouseCoords))
    {
        previousMapButton->onClick(graphics);
    }
    else if(nextMapButton->isHovered(mouseCoords))
    {
        nextMapButton->onClick(graphics);
    }
    else if(backToMenuButton->isHovered(mouseCoords))
    {
        backToMenuButton->onClick(graphics);
    }
}

void ChooseMapWidget::confirmChoice()
{
    graphics->setMap(maps[currentMapNumber]);
    graphics->setGameState(GameState::ChooseDifficult);
}
