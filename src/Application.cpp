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
    m_world->AddParticles();
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

    //Graphics::RenderFont(elapsedTime, { 10, 10 }, { 200, 120 }, 12);


    Application::Render();
}

void Application::Render()
{
    // [TODO] CLEAN THIS UP
    std::vector<Particle*>& particles = m_world->GetParticles();

    // 1. Drawing Entities and anything related to them:
    if (!particles.empty())
    {
        // [TODO] :: Add a check to make sure only the particles in view are drawn...
        // 1.1: Draw each particle:
        for (auto particle : particles)
        {
            m_transformedView->DrawFillCircle(particle->m_pos.x, particle->m_pos.y, particle->m_radius, particle->m_color);

            if (IsDebugModeActive())
            {
                // 1.2: Draw each of the particle bounding boxes:
                int bbMinX = particle->m_bb.m_minX;
                int bbMinY = particle->m_bb.m_minY;
                int bbMaxX = particle->m_bb.m_maxX;
                int bbMaxY = particle->m_bb.m_maxY;

                m_transformedView->DrawBoundingBox2D(bbMinX, bbMinY, bbMaxX, bbMaxY, ((particle->m_bb.m_isBBColliding) ? 0xFF7722FF : 0x88FF6699));
            }
        }

        // 1.2: Perform nearest neighbor query for a given entity:
        // [TODO] :: This obviously needs to be incorporated into the for loop...
        auto locatedParticles = m_world->GetCurrSDS()->QueryNearestNeighbour(m_world->m_particles[0]);

        for (const Particle* particle : locatedParticles)
        {
            if (particle != nullptr)
            {
                m_transformedView->DrawFillCircle(particle->m_pos.x, particle->m_pos.y, particle->m_radius, 0x88FF7711);
            }
        }
    }

    // 2. Drawing the SDS and related components:
    m_world->GetCurrSDS()->DrawSDS(m_transformedView);

    // 2.1:
    BoundingBox2D* selectedSDSComponent = m_world->GetSDSComponent();
    if (selectedSDSComponent != nullptr)
    {
        m_transformedView->DrawBoundingBox2D(selectedSDSComponent->m_minX, selectedSDSComponent->m_minY, selectedSDSComponent->m_maxX, selectedSDSComponent->m_maxY, 0xFFBB66FF);
    }


    // 3. Drawing the Bounded Region surrounding the world:
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