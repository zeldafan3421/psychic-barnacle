#pragma once
#include <raylib.h>
#include "screen.h"

class MainScreen : public IScreen
{
public:
    MainScreen();

    virtual void update() override;
    virtual void draw() const override;
private:
    static Color nextColor(Color last);
    double getTimePassed();

    constexpr static double g_PauseLength = 0.4;
    double m_LastUpdate;
    Color m_BgColor;
};