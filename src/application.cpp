#include "application.h"

#include <array>
#include <cstdlib>
#include "utility.h"
#include "input.h"
#include <memory>

Application::Application() 
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(g_StartWidth, g_StartHeight, g_AppTitle);
    
    utility::SmallDataArena arena;

    auto count = arena.make_ptr<int>(6);
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
