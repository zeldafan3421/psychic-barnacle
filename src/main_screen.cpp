#include "main_screen.h"
#include "raymath.h"

MainScreen::MainScreen() : m_BgColor(WHITE)
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
    DrawFPS(10, 10);
}
