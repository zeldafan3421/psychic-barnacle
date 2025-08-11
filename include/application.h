#pragma once

#include "screen.h"
#include "main_screen.h"
#include <raylib.h>

class Application
{
public:
    Application();

    [[noreturn]]void loop();

private:
    void render(const IScreen& screen) const;

private:
    MainScreen m_MainScreen;
    constexpr static int g_StartWidth = 1280;
    constexpr static int g_StartHeight = 720;
    const char* g_AppTitle = "My Application";
};