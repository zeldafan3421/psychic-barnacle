#pragma once

#include "renderer.h"

class Application
{
public:
    Application();

    void loop();
private:
    Renderer renderer;
};