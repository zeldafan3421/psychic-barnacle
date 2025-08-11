#pragma once

class IScreen
{
public:
    virtual void update() = 0;
    virtual void draw() const = 0;
};