#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../../lib/SDL2_gfx/SDL2_gfxPrimitives.h"
#include "../Model/Util/Vec2D.h"
#include "../Model/Util/BoundingBox.h"
#include "Font.h"
#include <SDL.h>
#include <vector>

struct Graphics
{
    static int m_windowWidth;
    static int m_windowHeight;
    static SDL_Window* m_window;
    static SDL_Renderer* m_renderer;

    static int i_Width();
    static int i_Height();
    static float f_Width();
    static float f_Height();
    static bool OpenWindow();
    static void CloseWindow();
    static void ClearScreen(Uint32 color);
    static void RenderFrame();
    static void DrawLine(int x0, int y0, int x1, int y1, Uint8 thickness, Uint32 color);
    static void DrawCircle(int x, int y, int radius, float angle, Uint32 color);
    static void DrawFillCircle(int x, int y, int radius, Uint32 color);
    static void DrawSimpleFillCircle(int x, int y, int radius, Uint32 color);
    static void DrawFillCircleWithOutline(int x, int y, int radius, Uint32 color);
    static void DrawRect(int x, int y, int width, int height, Uint32 color);
    static void DrawFillRect(int x, int y, int width, int height, Uint32 color);
    static void DrawPolygon(int x, int y, const std::vector<Vec2f>& vertices, Uint32 color);
    static void DrawFillPolygon(int x, int y, const std::vector<Vec2f>& vertices, Uint32 color);
    static void DrawTexture(int x, int y, int width, int height, float rotation, SDL_Texture* texture);
    static void DrawBoundingBox2D(int minX, int minY, int maxX, int maxY, Uint8 thickness, Uint32 color);
    static void DrawBoundingBox2D(const BoundingBox2D* bb, const Uint32 color);
    static void RenderText(std::vector<std::pair<SDL_Texture*, SDL_Rect*>> _text);
    static void RenderFont(std::string _text, Vec2i _pos, Vec2i _dimensions, int _fontSize);
};

#endif