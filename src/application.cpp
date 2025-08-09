#include "application.h"

Application::Application() 
{
}

void Application::loop()
{
    while (renderer.isAvailable())
    {
        Promise drawing = renderer.prepare();

        renderer.clearBackground(WHITE);
    }
}
