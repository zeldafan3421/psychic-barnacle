#include "application.h"

#include <array>

Application::Application() 
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(g_StartWidth, g_StartHeight, g_AppTitle);
}

void Application::loop()
{
    while (!WindowShouldClose())
    {
        m_MainScreen.update();
        render(m_MainScreen);
    }
}

void Application::render(const IScreen &screen) const
{
    BeginDrawing();
        ClearBackground(BLACK);
        screen.draw();
    EndDrawing();
}
