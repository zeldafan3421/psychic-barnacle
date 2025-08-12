#pragma once

#include "utility.h"
#include "input.h"
#include "raylib.h"
#include "raymath.h"
#include "entity.h"

struct PlayerGraphics
{
    PlayerGraphics() : rectangleSize{100.0f, 100.0f}, color{RED} {}

    Vector2 rectangleSize;
    Color color;
};

class Player 
{
public:
    Player();

    void update();

    void draw() const;

    operator Entity();
private:
    InputHandler m_Controller;
    Entity m_Base;
    PlayerGraphics m_Graphics;
    utility::SmallDataArena<1024> m_CommandData;
};

struct PlayerInputCommand : public IInputCommand
{
    PlayerInputCommand(Entity *data) : playerData(data) {}

    Entity* playerData;
};

struct PlayerMoveCommand : public PlayerInputCommand
{
    constexpr static Vector2 UP    = {  0, -1 };
    constexpr static Vector2 DOWN  = {  0,  1 };
    constexpr static Vector2 LEFT  = { -1,  0 };
    constexpr static Vector2 RIGHT = {  1,  0 };
    
    PlayerMoveCommand(Entity* data, Vector2 dir) : 
        PlayerInputCommand(data), 
        direction(dir) 
    {
    }

    virtual void execute() override 
    { 
        playerData->setVelocity(playerData->getVelocity() + direction); 
    }

    Vector2 direction;
};