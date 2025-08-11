#include "main_screen.h"

MainScreen::MainScreen()
{
    m_BgColor = BLACK;
}

void MainScreen::update()
{
    if (getTimePassed() > g_PauseLength)
    {
        m_BgColor = nextColor(m_BgColor);
        m_LastUpdate = GetTime();
    }
}

void MainScreen::draw() const
{
    ClearBackground(m_BgColor);
}

Color MainScreen::nextColor(Color last)
{
    unsigned char redChannel = last.r + GetRandomValue(0, 255);
    unsigned char greenChannel = redChannel + GetRandomValue(0, 255);
    unsigned char blueChannel = greenChannel + GetRandomValue(0, 255);

    return Color{redChannel, greenChannel, blueChannel, last.a};
}

double MainScreen::getTimePassed()
{
    return GetTime() - m_LastUpdate;
}
