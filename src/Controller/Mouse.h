#pragma once
#ifndef MOUSE_H
#define MOUSE_H

#include "../View/TransformedView.h"
#include "../Model/World/World.h"
#include "../Model/World/Particle.h"
#include "../Model/Util/BoundingBox.h"
#include "../Model/Util/Vec2.h"
#include "SDL.h"
#include <vector>
#include <string> // Change this later!!!!

struct Mouse
{
public:
    TransformedView* ptr_tvRef;
    World* ptr_worldRef;

    bool m_isLeftMouseBtnDown = false;
    bool m_isRightMouseBtnDown = false;

    // TODO: If possible, make the constructor take the 'TransformedView' ptr_ref as 
    //       all Handle methods require it.
    Mouse();
    ~Mouse() = default;

protected:
    Vec2f m_startPan;
    Vec2f m_startZoom;
    Vec2f m_currMousePos;
    Vec2f m_oldMousePos;



public:
    BoundingBox2D queryBoundary;

    void UpdateMousePos();
    void HandleMouseButtonUp(const SDL_Event& event, TransformedView* _ptr_tvRef);
    void HandleMouseButtonDown(const SDL_Event& event, TransformedView* _ptr_tvRef);
    void HandleMouseMotion(const SDL_Event& event, TransformedView* _ptr_tvRef);
    void HandleMouseWheel(const SDL_Event& event, TransformedView* _ptr_tvRef);

    bool GetMouseWheel(const SDL_Event& event);
    Vec2i GetMousePos(const SDL_Event& event);
    Vec2f CalculateMouseOffset();
};

#endif