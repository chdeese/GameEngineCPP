#include "Window.h"
#include "raylib.h"

GameGraphics::Window::Window(int width, int height, const char* title)
    : m_width(width), m_height(height), m_title(title)
{
}

bool GameGraphics::Window::shouldClose()
{
    return RAYLIB_H::WindowShouldClose();
}

int GameGraphics::Window::getFrameRate()
{
    return RAYLIB_H::GetFPS();
}

void GameGraphics::Window::setTargetFrameRate(int fps)
{
    RAYLIB_H::SetTargetFPS(fps);
}

void GameGraphics::Window::open()
{
    RAYLIB_H::InitWindow(m_width, m_height, m_title);
}

void GameGraphics::Window::beginDrawing()
{
    RAYLIB_H::BeginDrawing();
    RAYLIB_H::ClearBackground(RAYLIB_H::BLACK);
}

void GameGraphics::Window::endDrawing()
{
    RAYLIB_H::EndDrawing();
}

void GameGraphics::Window::close()
{
    RAYLIB_H::CloseWindow();
}
