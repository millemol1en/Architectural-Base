#include "Application.h"

std::string Application::m_baseRes = "";

bool Application::IsRunning()
{
    if (m_controller != nullptr) return m_controller->GetIsRunning();
    else std::cerr << "The controller variable 'm_controller' was a nullptr" << std::endl;

    return m_isRunning;
}

bool Application::IsDebugModeActive()
{
    return m_controller->GetIsDebugModeActive();
}

void Application::Setup()
{
    m_isRunning         = Graphics::OpenWindow();   // [TODO] :: Link this up properly with the controller class
    m_world             = new World(9.8, { 0, 0 }, { 1000, 1000 });
    m_transformedView   = new TransformedView({ Graphics::i_Width(), Graphics::i_Height() }, m_world->GetWorldSize());
    m_controller        = new Controller(m_world, m_transformedView); // Might encounter errors with no default constructor so prepare for that... 
    m_world->AddParticle();
}

void Application::Input()
{
    m_controller->HandleInput();
}

// [TODO] :: This entire method needs to be fixed - it is a confusing mess
void Application::Update()
{
    Graphics::ClearScreen(0xFF0F0721);

    auto start = std::chrono::system_clock::now();

    // Handle Time Blocks:
    static int timePreviousFrame;
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - timePreviousFrame);
    if (timeToWait > 0) SDL_Delay(timeToWait);

    float deltaTime(SDL_GetTicks() - timePreviousFrame / 1000.0f);
    if (deltaTime > 0.016) deltaTime = 0.016;

    timePreviousFrame = SDL_GetTicks();


    m_world->Update(deltaTime);

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<float> duration = end - start;
    float elapsedT = duration.count();

    // Handle elapsed Time:
    std::string elapsedTime = std::to_string(elapsedT);

    Graphics::RenderFont(elapsedTime, { 10, 10 }, { 200, 120 }, 12);


    Application::Render();
}

void Application::Render()
{
    // [TODO] CLEAN THIS UP
    // Potentially add this to a generalized Graphics Rendering class:
    std::vector<ISpatialEntity*>& entities = m_world->GetEntities();
    
    // [1]
    if (!entities.empty())
    {
        // [1.1]
        for (auto& entity : entities)
        {

            // [1.2]
            switch (entity->GetEntityType())
            {

                // [1.3]
                case ENTITY_TYPE::PARTICLE:

                    Particle* particle = (Particle*)entity;

                    m_transformedView->DrawFillCircle(particle->m_pos, particle->m_radius, particle->m_color);

                    if (IsDebugModeActive())
                    {
                        // 1.2: Draw each of the particle bounding boxes:
                        const BoundingBox2D& particleBB = particle->m_bb;

                        float bbMinX = particleBB.m_minX;
                        float bbMinY = particleBB.m_minY;
                        float bbMaxX = particleBB.m_maxX;
                        float bbMaxY = particleBB.m_maxY;

                        m_transformedView->DrawBoundingBox2D(bbMinX, bbMinY, bbMaxX, bbMaxY, ((particleBB.m_isOnlyOverlapping) ? 0xFF00FF55 : (particleBB.m_isOnlyContained) ? 0xFF00D5FF : 0x889966FF));

                        // Green  :: 0xFF00FF55
                        // Yellow :: 0xFF00D5FF
                        // Pink   :: 0xFF9966FF

                    }

                    break;



            }


        }


        // [TODO] :: This obviously needs to be incorporated into the for loop...
        auto locatedEntities = m_world->GetCurrSDS()->QueryNearestNeighbour(m_world->m_entities[0]);

        for (auto& entity : locatedEntities)
        {
            if (entity->GetEntityType() == ENTITY_TYPE::PARTICLE)
            {
                Particle* particle = (Particle*)entity;

                if (particle != nullptr)
                {
                    m_transformedView->DrawFillCircle(particle->m_pos, particle->m_radius, 0x88FF7711);
                }
            }
        }
    }

    // [5] Draw the current SDS:
    m_world->GetCurrSDS()->DrawSDS(m_transformedView);

    // [6] Draw the World's bounded region:
    const BoundingBox2D& worldBB = m_world->m_worldBoundingBox;

    int worldBBMinX = worldBB.m_minX;
    int worldBBMinY = worldBB.m_minY;
    int worldBBMaxX = worldBB.m_maxX;
    int worldBBMaxY = worldBB.m_maxY;

    m_transformedView->DrawBoundingBox2D(worldBBMinX, worldBBMinY, worldBBMaxX, worldBBMaxY, 0xFF66FFCC);

    Graphics::RenderFrame();
}

void Application::Destroy()
{
    delete m_controller;
    delete m_transformedView;
    delete m_world;
    Graphics::CloseWindow();
}