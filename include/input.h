#pragma once

#include <array>
#include <memory>
#include <cstring>
#include <stdexcept>
#include <new>
#include "raylib.h"

struct IInputCommand
{
    virtual void execute() = 0;
};

class TestCommand : public IInputCommand
{
public:
    TestCommand() : IInputCommand()
    {
    }

    virtual void execute()
    {
        TraceLog(LOG_INFO, "works");
    }

    ~TestCommand()
    {
        TraceLog(LOG_INFO, "test command destructor");

    }
};

class InputHandler
{
public:
    InputHandler();

    void bindCommand(int key, IInputCommand* cmd);

    void handleInput();
private:
    std::array<IInputCommand*, KEY_KP_EQUAL> m_KeyMap;
};