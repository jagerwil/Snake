#pragma once
#include "Structures.h"
#include <vector>
using std::vector;

class SnakeGraphics;
class MapImage;
class PreviousMapButton;
class NextMapButton;
class BackToMainMenuButton;

class ChooseMapWidget
{
protected:
    const string backgroundFilename = "Textures/background_choose_map.png";
    const string textureFilename  = "Textures/snake_sprite.png";
    const string mapsListFilename = "Maps/maps_list.txt";
    static Vector2b textureSize /* = { 8,  8} */;

    const Vector2u& screenSize;
    const Font& font;

    vector<MapImage*> maps;

    Int8 mapsCount;
    Int8 currentMapNumber;
    
    Texture backgroundTexture;
    Sprite background;
    Text title;
    Text mapInfo;

    Texture texture;
    Vector2b mapSize;
    Sprite** spritesMap;

    PreviousMapButton* previousMapButton;
    NextMapButton* nextMapButton;
    BackToMainMenuButton* backToMenuButton;

    SnakeGraphics* graphics;
    bool isInitialized;

public:
    ChooseMapWidget(Vector2u screenSize, const Font& font, SnakeGraphics* graphics);
    ~ChooseMapWidget();

    void initialize();
    void unitialize();
    void nextMap();
    void previousMap();
    void initializeMap();

    void draw(RenderWindow* window);
    void clickOnButton(Vector2i mouseCoords);
    void confirmChoice();
};

