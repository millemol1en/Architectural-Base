#pragma once
#ifndef MOUSE_H
#define MOUSE_H

#include "../View/TransformedView.h"
#include "../Model/World/World.h"
#include "../Model/World/SpatialEntities/Particles/Particle.h"	// [TODO] :: CHANGE TO PARENT TYPE
#include "../Model/Util/BoundingBox.h"
#include "../Model/Util/Vec2D.h"
#include "SDL.h"
#include <vector>
#include <string> // Change this later!!!!

struct Mouse
{
protected:
    Vec2f m_startPan;
    Vec2f m_startZoom;
    Vec2f m_currMousePos;
    Vec2f m_oldMousePos;



public:
    TransformedView* ptr_tvRef;
    World* ptr_worldRef;

    bool m_isLeftMouseBtnDown = false;
    bool m_isRightMouseBtnDown = false;

    Mouse();
    ~Mouse() = default;

    BoundingBox2D queryBoundary;

    void UpdateMousePos();
    void HandleMouseButtonUp(const SDL_Event& event);
    void HandleMouseButtonDown(const SDL_Event& event);
    void HandleMouseMotion(const SDL_Event& event);
    void HandleMouseWheel(const SDL_Event& event);

    bool GetMouseWheel(const SDL_Event& event);
    Vec2i GetMousePos(const SDL_Event& event);
    Vec2f CalculateMouseOffset();

    void Mouse_SetTVPtr(TransformedView* _ptr_tvRef);
    void Mouse_SetWorldPtr(World* _worldPtr);
};

#endif