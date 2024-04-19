#include "Graphics.h"

#include <iostream>

SDL_Window* Graphics::m_window = NULL;
SDL_Renderer* Graphics::m_renderer = NULL;
int Graphics::m_windowWidth = 0;
int Graphics::m_windowHeight = 0;

int Graphics::i_Width()
{
    return m_windowWidth;
}

int Graphics::i_Height()
{
    return m_windowHeight;
}

float Graphics::f_Width()
{
    return (float)m_windowWidth;
}

float Graphics::f_Height()
{
    return (float)m_windowHeight;
}

bool Graphics::OpenWindow()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error initializing SDL" << std::endl;
        return false;
    }

    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    m_windowWidth  = display_mode.w;
    m_windowHeight = display_mode.h;

    m_window = SDL_CreateWindow(NULL, 0, 0, m_windowWidth, m_windowHeight, SDL_WINDOW_BORDERLESS);
    //window = SDL_CreateWindow("Particle System", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_RESIZABLE);

    if (!m_window)
    {
        std::cerr << "Error creating SDL window" << std::endl;
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer)
    {
        std::cerr << "Error creating SDL renderer" << std::endl;
        return false;
    }
    else if (m_renderer)
    {
        std::cout << "Renderer is fine" << std::endl;
    }

    bool openFontsRes = Fonts::OpenFonts();

    if (!openFontsRes)
    {
        std::cerr << "[Method --- OpenWindow() :: Error with Fonts::OpenFonts()]" << std::endl;
        return false;
    }

    return true;
}

void Graphics::CloseWindow(void)
{
    Fonts::CloseFonts();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Graphics::ClearScreen(Uint32 color)
{
    SDL_SetRenderDrawColor(m_renderer, color >> 16, color >> 8, color, 255);
    SDL_RenderClear(m_renderer);
}

void Graphics::RenderText(std::vector<std::pair<SDL_Texture*, SDL_Rect*>> _textTexture)
{
    for (auto& t : _textTexture)
    {
        SDL_RenderCopy(m_renderer, t.first, NULL, t.second);
        if (t.first != nullptr) SDL_DestroyTexture(t.first);
    }
}

void Graphics::RenderFrame()
{
    // Info on "SDL_RenderPresent" VS "SDL_UpdateWindowSurface" - [https://stackoverflow.com/questions/33402909/sdl-renderpresent-vs-sdl-updatewindowsurface]
    SDL_RenderPresent(m_renderer);
}

void Graphics::DrawLine(int x0, int y0, int x1, int y1, Uint8 thickness, Uint32 color)
{
    thickLineColor(m_renderer, x0, y0, x1, y1, thickness, color);
}

void Graphics::DrawCircle(int x, int y, int radius, float angle, Uint32 color)
{
    circleColor(m_renderer, x, y, radius, color);
    lineColor(m_renderer, x, y, x + cos(angle) * radius, y + sin(angle) * radius, color);
}

void Graphics::DrawFillCircle(int x, int y, int radius, Uint32 color)
{
    if (/*zoomLevel < ZOOMOUT_THRESHOLD*/ false)
    {
        DrawSimpleFillCircle(x, y, radius, color);
    }
    else
    {
        filledCircleColor(m_renderer, x, y, radius, color);
    }

}

void Graphics::DrawSimpleFillCircle(int x, int y, int radius, Uint32 color)
{
    // Render a simplified filled circle with fewer points
    // Figure out how this works cuz its fucking genius!
    for (int dy = -radius; dy <= radius; dy++)
    {
        for (int dx = -radius; dx <= radius; dx++)
        {
            if (dx * dx + dy * dy <= radius * radius)
            {
                Uint8 alpha = (color >> 24) & 0xFF;
                Uint8 red = (color >> 16) & 0xFF;
                Uint8 green = (color >> 8) & 0xFF;
                Uint8 blue = color & 0xFF;

                SDL_SetRenderDrawColor(m_renderer, red, green, blue, alpha);

                SDL_RenderDrawPoint(m_renderer, x + dx, y + dy);
            }
        }
    }
}

void Graphics::DrawFillCircleWithOutline(int x, int y, int radius, Uint32 color)
{
    circleColor(m_renderer, x, y, (radius * 1.012), 0xFFFFFFFF);
    filledCircleColor(m_renderer, x, y, radius, color);
}

void Graphics::DrawRect(int x, int y, int width, int height, Uint32 color)
{
    thickLineColor(m_renderer, x - width / 2.0, y - height / 2.0, x + width / 2.0, y - height / 2.0, 4, color);
    thickLineColor(m_renderer, x + width / 2.0, y - height / 2.0, x + width / 2.0, y + height / 2.0, 4, color);
    thickLineColor(m_renderer, x + width / 2.0, y + height / 2.0, x - width / 2.0, y + height / 2.0, 4, color);
    thickLineColor(m_renderer, x - width / 2.0, y + height / 2.0, x - width / 2.0, y - height / 2.0, 4, color);
}

void Graphics::DrawBoundingBox2D(const BoundingBox2D* bb, const Uint32 color)
{
    if (bb == nullptr) return;

    int minX = bb->m_minX; // MinX
    int minY = bb->m_minY; // MinY
    int maxX = bb->m_maxX; // MaxX
    int maxY = bb->m_maxY; // MaxY

    DrawBoundingBox2D(minX, minY, maxX, maxY, 1.0, color);
}

void Graphics::DrawBoundingBox2D(int minX, int minY, int maxX, int maxY, Uint8 thickness, Uint32 color)
{
    thickLineColor(m_renderer, minX, minY, maxX, minY, thickness, color); // Top-Left     |>  Top-Right
    thickLineColor(m_renderer, maxX, minY, maxX, maxY, thickness, color); // Top-Right    |>  Bottom-Right
    thickLineColor(m_renderer, maxX, maxY, minX, maxY, thickness, color); // Bottom-Right |>  Bottom-Left
    thickLineColor(m_renderer, minX, maxY, minX, minY, thickness, color); // Bottom-Left  |>  Top-Left
}

void Graphics::DrawFillRect(int startX, int startY, int width, int height, Uint32 color)
{
    boxColor(m_renderer, startX, startY, width, height, color);
}

void Graphics::DrawPolygon(int x, int y, const std::vector<Vec2f>& vertices, Uint32 color)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        int currIndex = i;
        int nextIndex = (i + 1) % vertices.size();
        lineColor(m_renderer, vertices[currIndex].x, vertices[currIndex].y, vertices[nextIndex].x, vertices[nextIndex].y, color);
    }
    filledCircleColor(m_renderer, x, y, 1, color);
}

void Graphics::DrawFillPolygon(int x, int y, const std::vector<Vec2f>& vertices, Uint32 color)
{
    std::vector<short> vx;
    std::vector<short> vy;
    for (int i = 0; i < vertices.size(); i++)
    {
        vx.push_back(static_cast<int>(vertices[i].x));
    }
    for (int i = 0; i < vertices.size(); i++)
    {
        vy.push_back(static_cast<int>(vertices[i].y));
    }
    filledPolygonColor(m_renderer, &vx[0], &vy[0], vertices.size(), color);
    filledCircleColor(m_renderer, x, y, 1, 0xFF000000);
}

void Graphics::DrawTexture(int x, int y, int width, int height, float rotation, SDL_Texture* texture)
{
    SDL_Rect dstRect = { x - (width / 2), y - (height / 2), width, height };
    float rotationDeg = rotation * 57.2958;
    SDL_RenderCopyEx(m_renderer, texture, NULL, &dstRect, rotationDeg, NULL, SDL_FLIP_NONE);
}

void Graphics::RenderFont(std::string _text, Vec2i _pos, Vec2i _dimensions, int _fontSize)
{
    Fonts::RenderFont(_text, _pos, _dimensions, {255, 255, 255}, _fontSize, m_renderer);
}