#pragma once
#include <raylib.h>
#include "screen.h"
#include "input.h"
#include "utility.h"
#include "player.h"
class MainScreen : public IScreen
{
public:
    MainScreen();

    virtual void update() override;
    virtual void draw() const override;
private:
    Player m_Player;
    Color m_BgColor;
};

