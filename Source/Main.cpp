#include "SnakeGraphics.h"


int main()
{
    Vector2i screenSize = {1376, 768};
    SnakeGraphics* graphics = new SnakeGraphics(screenSize);

    while (graphics->isWindowOpen())
    {
        graphics->tick();
    }

    delete graphics;
    return 0;
}
