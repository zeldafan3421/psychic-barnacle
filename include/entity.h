#pragma once

#include "raylib.h"
#include "raymath.h"

struct Velocity
{
    Vector2 value;

    inline Vector2 normalized() const { return Vector2Normalize(value); }
    inline Vector2 raw() const { return value; }

    void reset() 
    {
        value.x = 0.0f;
        value.y = 0.0f;
    }

    Velocity& operator=(Vector2 v) { value = v; return *this; }
    operator Vector2() const { return value; }
};

struct EntityData
{
    EntityData() : position{0.0f, 0.0f}, velocity{0.0f, 0.0f} {}
    Vector2 position;
    Velocity velocity;

    inline void resetVelocity()
    {
        velocity.reset();
    }

    template <class T>
    inline void accumulatePosition(T& _Fn)
    {
        position += _Fn(velocity);
    }
};

struct PositionCalculation
{
    PositionCalculation(float speed) : moveSpeed(speed) 
    {
    }

    inline Vector2 operator()(const Velocity velocity) const
    {
        return velocity.normalized() * getSpeed() * GetFrameTime();
    }

    inline void setSpeed(float speed)
    {
        moveSpeed = speed;
    }

    inline float getSpeed() const
    {
        return moveSpeed;
    }

    float moveSpeed;
};

class Entity
{
public:
    Entity() : m_Data(), m_CalculatePosition(100.0f)
    {
    }

    inline void setMoveSpeed(float speed)
    {
        m_CalculatePosition.setSpeed(speed);
    }

    inline void setVelocity(Vector2 velocity)
    {
        m_Data.velocity = velocity;   
    }

    inline Vector2 getVelocity() const
    {
        return m_Data.velocity;
    }

    inline float getSpeed() const
    {
        return m_CalculatePosition.getSpeed();
    }

    inline Vector2 getPosition() const
    {
        return m_Data.position;
    }

    inline void update()
    {
        m_Data.accumulatePosition(m_CalculatePosition);

        m_Data.resetVelocity();
    }
private:
    EntityData m_Data;
    PositionCalculation m_CalculatePosition;
};
