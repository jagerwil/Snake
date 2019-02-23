#include "MapImage.h"


MapImage::MapImage(string mapName):
    mapName{mapName}
{
    isMapOpened = map.loadFromFile("Maps/" + mapName + ".png");
    mapSize = {(Int8)map.getSize().x, (Int8)map.getSize().y};
}

CellType MapImage::pixelToCellType(Vector2b coords)
{
    if(!isMapOpened)
    {
        return CellType::EmptyCell;
    }
    else if(coords.x >= mapSize.x || coords.y >= mapSize.y)
    {
        return CellType::EmptyCell;
    }
    else if(map.getPixel(coords.x, coords.y) == Color::Black)
    {
        return CellType::Wall;
    }
    else return CellType::EmptyCell;
}

string MapImage::getMapName()
{
    return mapName;
}

Vector2b MapImage::getSize()
{
    return mapSize;
}
