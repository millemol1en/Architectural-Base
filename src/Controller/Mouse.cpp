#include "Mouse.h"

Mouse::Mouse() 
{
    m_startPan      = Vec2f(0, 0);
    m_startZoom     = Vec2f(0, 0);
    m_currMousePos  = Vec2f(0, 0);
    m_oldMousePos   = Vec2f(0, 0);
}

void Mouse::UpdateMousePos()
{
}

void Mouse::HandleMouseButtonUp(const SDL_Event& event, TransformedView* _ptr_tvRef)
{
    _ptr_tvRef->EndPan(GetMousePos(event));

    m_isLeftMouseBtnDown = false;
    m_isRightMouseBtnDown = false;
}

void Mouse::HandleMouseButtonDown(const SDL_Event& event, TransformedView* _ptr_tvRef)
{
    ISDS* SDSRef = ptr_worldRef->GetCurrSDS();

    if (event.button.button == SDL_BUTTON_LEFT)
    {
        Vec2f screenToWorldMousePos = _ptr_tvRef->ConvertScreenToWorld(GetMousePos(event));

        Particle* locatedParticle = SDSRef->QueryForSpecificUsingMouse(screenToWorldMousePos);

        if (locatedParticle != nullptr)
        {
            ptr_worldRef->SetSelectedEntity(locatedParticle);
            std::cout << "Located Particle has ID :: " << locatedParticle->m_ID << "\n";
        }
        else
        {
            ptr_worldRef->SetSDSComponent(SDSRef->HighlightSDSComponent(screenToWorldMousePos));
        }
    }
    else if (event.button.button == SDL_BUTTON_RIGHT)
    {
        _ptr_tvRef->StartPan(GetMousePos(event));
    }
}

void Mouse::HandleMouseMotion(const SDL_Event& event, TransformedView* _ptr_tvRef)
{
    _ptr_tvRef->UpdatePan(GetMousePos(event));

    m_currMousePos.x = event.motion.x;
    m_currMousePos.y = event.motion.y;

    Vec2f mouseOffset = CalculateMouseOffset();

    m_oldMousePos.x = m_currMousePos.x;
    m_oldMousePos.y = m_currMousePos.y;
}

void Mouse::HandleMouseWheel(const SDL_Event& event, TransformedView* _ptr_tvRef)
{
    if (GetMouseWheel(event))
    {
        _ptr_tvRef->ZoomAtScreenPos(1.0109f, GetMousePos(event));
    }
    else
    {
        _ptr_tvRef->ZoomAtScreenPos(0.9887f, GetMousePos(event));
    }
}

// Used in conjunction with object moving (Particles) to determine the offset 
// so as to be able to move the object by that amount.
Vec2f Mouse::CalculateMouseOffset()
{
    Vec2f mouseDelta = m_currMousePos - m_oldMousePos;
    Vec2f mouseOffset = Vec2f(0, 0);

    // X:
    if (mouseDelta.x < 0)
    {
        mouseOffset.x -= fabs(mouseDelta.x);
    }
    else if (mouseDelta.x > 0)
    {
        mouseOffset.x += fabs(mouseDelta.x);
    }

    // Y:
    if (mouseDelta.y < 0)
    {
        mouseOffset.y -= fabs(mouseDelta.y);
    }
    else if (mouseDelta.y > 0)
    {
        mouseOffset.y += fabs(mouseDelta.y);
    }

    return mouseOffset;
}

////////////////
// PAN & ZOOM //
////////////////
Vec2i Mouse::GetMousePos(const SDL_Event& event)
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    return { x, y };
}

// [TODO] For safety reasons change this to use an Enum localized to be within the mouse.
bool Mouse::GetMouseWheel(const SDL_Event& event)
{
    if (event.wheel.y > 0)      { return true;  }
    else if (event.wheel.y < 0) { return false; }
    return false;
    // Create an Option type - kind like in F#, which allows for the possibility of a 3rd return "Nothing" type.
}