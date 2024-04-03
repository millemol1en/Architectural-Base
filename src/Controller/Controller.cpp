#include "Controller.h"

Controller::Controller(World* _worldPtr, TransformedView* _tvPtr) : m_isAppRunning(true), m_debugMode(false), m_devSnapShot(false)
{
    ptr_worldRef = _worldPtr;
    ptr_tvRef = _tvPtr;

    // [TODO] :: Should they be parameters passed to the individual methods or actually assigned?
    m_mouse.ptr_tvRef    = _tvPtr;
    m_mouse.ptr_worldRef = _worldPtr;

    m_key.Keys_SetTVPtr(_tvPtr);
    m_key.Keys_SetWorldPtr(_worldPtr);
}

void Controller::HandleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_isAppRunning = false;
            break;
        case SDL_KEYDOWN:
            m_key.Keys_HandleKeyDown(event);
            break;

        case SDL_KEYUP:
            m_key.Keys_HandleKeyUp(event);
            break;

        case SDL_MOUSEWHEEL:
            m_mouse.HandleMouseWheel(event, ptr_tvRef);
            break;

        case SDL_MOUSEMOTION:
            m_mouse.HandleMouseMotion(event, ptr_tvRef);
            break;

        case SDL_MOUSEBUTTONDOWN:
            m_mouse.HandleMouseButtonDown(event, ptr_tvRef);
            break;

        case SDL_MOUSEBUTTONUP:
            m_mouse.HandleMouseButtonUp(event, ptr_tvRef);
            break;
        }


        // TODO :: if (!m_world->circles.empty()) m_world->circles[0]->AddVelocityImpulse(pushForce);

    }



}

//////////////////////////////
//                          //
//  TOGGLES && ACTIVATORS   //
//                          //
//////////////////////////////
void Controller::CloseApp()
{
    m_key.Keys_CloseApp();
}

void Controller::ToggleDebugMode()
{
    m_key.Keys_ToggleDebugMode();
}

void Controller::ActivateDevSnapshot()
{
    m_key.Keys_ActivateDevSnapshot();
}


//////////////////////
//                  //
//      GETTERS     //
//                  //
//////////////////////
bool Controller::GetIsRunning() const
{
    return m_key.Keys_GetIsRunning();
}

bool Controller::GetIsDebugModeActive() const
{
    return m_key.Keys_GetIsDebugModeActive();
}

SDS_TYPE Controller::GetSDSType() const
{
    if (ptr_worldRef != nullptr) return ptr_worldRef->m_SDS->GetSDSType();
    else std::cerr << "The 'ptr_worldRef' was a nullptr\n";

    return SDS_TYPE::NONE;
}