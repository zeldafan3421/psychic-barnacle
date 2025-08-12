#include "input.h"

InputHandler::InputHandler()
{
    m_KeyMap.fill(nullptr);
}

void InputHandler::bindCommand(int key, IInputCommand *cmd)
{
    m_KeyMap.at(key) = cmd;
}

void InputHandler::handleInput()
{
    for (int i = KEY_NULL; i < KEY_KP_EQUAL; i++)
    {
        if (IsKeyDown(i) && m_KeyMap.at(i) != nullptr)
        {
            m_KeyMap.at(i)->execute();
        }
    }
}
