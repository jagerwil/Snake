#pragma once
#include "Structures.h"

class MapImage
{
protected:
    string mapName;
    Image map;
    Vector2b mapSize;
    bool isMapOpened;

public:
    MapImage(string mapName);

    CellType pixelToCellType(Vector2b coords);
    string getMapName();
    Vector2b getSize();
};

