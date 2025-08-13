#include "main_screen.h"
#include "raymath.h"

MainScreen::MainScreen() : 
    m_Player(), 
    m_Dummy(Vector2{50.0f, 50.0f}), 
    m_BgColor(WHITE)
{
}

void MainScreen::update()
{
    m_Player.update();
}

void MainScreen::draw() const
{
    ClearBackground(m_BgColor);
    m_Player.draw();
    m_Dummy.draw();
    DrawFPS(10, 10);
}
