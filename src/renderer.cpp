#include "renderer.h"

RenderContext::RenderContext(const char *title, int width, int height)
    : title(title), ownsWindow(true)
{
    InitWindow(width, height, title);
}

RenderContext::RenderContext(RenderContext&& other)
{
    if (&other != this)
    {
        title = other.title;
        other.ownsWindow = false;
    }
}

RenderContext &RenderContext::operator=(RenderContext &&other)
{
    if (&other != this)
    {
        title = other.title;
        other.ownsWindow = false;
    }

    return *this;
}

bool RenderContext::ready() const
{
    return !WindowShouldClose() && IsWindowReady();
}

RenderContext::~RenderContext()
{
    if (ownsWindow)
        CloseWindow();
}


void WindowCanvas::beginDrawing()
{
    BeginDrawing();
}

void WindowCanvas::endDrawing()
{
    EndDrawing();
}

void WindowCanvas::clear(Color color)
{
    ClearBackground(color);
}

Renderer::Renderer()
    : context("app", 1280, 720), canvas(std::make_unique<WindowCanvas>())
{
}

bool Renderer::isAvailable() const
{
    return context.ready();
}

void Renderer::clearBackground(Color color)
{
    canvas->clear(color);
}
