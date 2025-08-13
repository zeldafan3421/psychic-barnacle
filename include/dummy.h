#pragma once

#include "entity.h"

struct DummyGraphics
{
    DummyGraphics() : radius(20.0f), color(GREEN) {}

    float radius;
    Color color;

    void draw(Vector2 position) const
    {
        DrawCircleV(position, radius, color);
    }
};

class DummyEntity
{
public:
    class StatusLogger
    {
    public:
        StatusLogger(DummyEntity* target) : m_Target(target)
        {
            TraceLog(LOG_INFO, "DummyEntity@%p", target);
            TraceLog(LOG_INFO, "Created %.2f", GetTime());
        }
    private:
        DummyEntity* m_Target;
    };

    DummyEntity(Vector2 position) : m_Base(position), m_Graphics(), m_Logger(this)
    {
    }

    void update()
    {
    }

    void draw() const { m_Graphics.draw(m_Base.getPosition()); }
private:
    Entity m_Base;
    DummyGraphics m_Graphics;
    StatusLogger m_Logger;
};