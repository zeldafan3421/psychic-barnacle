#pragma once

#include <raylib.h>
#include <raymath.h>
#include <type_traits>
#include <memory>

class RenderContext 
{
public:
    RenderContext(const char* title, int width, int height);
    RenderContext(const RenderContext& other) = delete;
    RenderContext(RenderContext&& other);

    RenderContext& operator=(const RenderContext& other) = delete;
    RenderContext& operator=(RenderContext&& other);

    bool ready() const;
    ~RenderContext();
private:
    const char* title;
    bool ownsWindow;
};

class ICanvas
{
public:
    virtual void beginDrawing() = 0;
    virtual void endDrawing() = 0;
    virtual void clear(Color color) = 0;
};

class WindowCanvas : public ICanvas
{ 
public: 
    WindowCanvas() = default;
    virtual void beginDrawing() override;
    virtual void endDrawing() override;
    virtual void clear(Color color) override;
};

template <class B, class E>
class Promise
{
public:
    Promise(B onStart, E onEnd) :
        end(onEnd)
    {
        onStart();
    }

    ~Promise()
    {
        end();
    }
private:
    E end;
};

class Renderer
{
public:
    Renderer();

    bool isAvailable() const;

    void clearBackground(Color color);

    inline auto prepare()
    {
        auto start = [this](){ canvas->beginDrawing(); };
        auto end = [this](){ canvas->endDrawing(); };

        return Promise(start, end);
    }

private:
    RenderContext context;
    std::unique_ptr<ICanvas> canvas;
};