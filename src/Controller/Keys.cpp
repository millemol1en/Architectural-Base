#include "Keys.h"

void Keys::Keys_HandleKeyDown(const SDL_Event& event)
{
    Sint32 key = event.key.keysym.sym;

    if (key == SDLK_ESCAPE)    Keys_CloseApp();
    if (key == SDLK_d)         Keys_ToggleDebugMode();
    if (key == SDLK_UP)        ptr_worldRef->pushForce.y = -1.2 * PIXELS_PER_METER;
    if (key == SDLK_DOWN)      ptr_worldRef->pushForce.y =  1.2 * PIXELS_PER_METER;
    if (key == SDLK_LEFT)      ptr_worldRef->pushForce.x = -1.2 * PIXELS_PER_METER;
    if (key == SDLK_RIGHT)     ptr_worldRef->pushForce.x =  1.2 * PIXELS_PER_METER;

    if (key == SDLK_t)
    {
        std::cout << "Performing Test\n";

        if (ptr_worldRef != nullptr && ptr_tvRef != nullptr)
        {
            int numVisibleItems = 0;

            auto& particlesRef = ptr_worldRef->GetParticles();

            if (!particlesRef.empty())
            {
                std::cout << "Passed 'nullptr' check\n";
                for (auto p : particlesRef)
                {
                    if (ptr_tvRef->IsBBVisible(p->m_bb))
                    {
                        numVisibleItems++;
                    }
                }
            }

            std::cout << "Num. visible items :: " << numVisibleItems << "\n";
        }
    }

    if (key == SDLK_0)
    {
        ptr_worldRef->SetSelectedEntity(nullptr);
    }
}

void Keys::Keys_HandleKeyUp(const SDL_Event& event)
{
    Sint32 key = event.key.keysym.sym;

    if (key == SDLK_UP)    ptr_worldRef->pushForce.y = 0;
    if (key == SDLK_DOWN)  ptr_worldRef->pushForce.y = 0;
    if (key == SDLK_LEFT)  ptr_worldRef->pushForce.x = 0;
    if (key == SDLK_RIGHT) ptr_worldRef->pushForce.x = 0;

}

void Keys::Keys_SetTVPtr(TransformedView* _tvPtr)
{
    ptr_tvRef = _tvPtr;
}

void Keys::Keys_SetWorldPtr(World* _worldPtr)
{
    ptr_worldRef = _worldPtr;
}

void Keys::Keys_CloseApp()
{
    m_isAppRunning = false;
}

void Keys::Keys_ToggleDebugMode()
{
    m_debugMode = !m_debugMode;
}

void Keys::Keys_ActivateDevSnapshot()
{
    m_devSnapShot = true;
}

bool Keys::Keys_GetIsRunning() const
{
    return m_isAppRunning;
}

bool Keys::Keys_GetIsDebugModeActive() const
{
    return m_debugMode;
}

bool Keys::Keys_GetIsDevSnapshotActive() const
{
    return m_devSnapShot;
}

SDS_TYPE Keys::Keys_GetSDSType() const
{
	return SDS_TYPE();
}
