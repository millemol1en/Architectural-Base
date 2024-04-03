#include "World.h"

World::World(float _gravity, Vec2i _position, Vec2i _dimensions) : m_selectedParticle(nullptr), m_itemIDCounter(0)
{
    m_G = _gravity;
    m_worldBoundingBox = BoundingBox2D(float(_position.x), float(_position.y), float(_dimensions.x), float(_dimensions.y));
    m_worldSize = _dimensions;

    // Switch-case to handle the different types of Spatial Data Structures:
    m_SDS = SetCurrSDS(SDS_TYPE::SPATIAL_HASH_GRID);

    std::cout << "World constructor called\n";
}


World::~World()
{
    std::cout << "World destructor called\n";
    delete m_SDS;

    for (auto& particle : m_particles)
    {
        delete particle;
    }
}

//////////////////////////////
//                          //
//  PARTICLES || ENTITIES   //
//                          //
//////////////////////////////

void World::AddEntity()
{
    
}

void World::AddParticles()
{
    // [TESTING / REMOVE LATER]
    Particle* mainParticle = new Particle(12, Graphics::f_Width() / 2, Graphics::f_Height() / 2, m_itemIDCounter++, 0xFFFFFFFF);
    m_particles.push_back(mainParticle);
    m_SDS->Insert(mainParticle);

    for (int i = 0; i < 100; i++)
    {
        int randColor = Graphics::RandomColorGenerator();
        int randRadius = Graphics::RandomRadiusGenerator(12);
        Vec2f randPos = Graphics::RandomPositionGenerator(m_worldBoundingBox.m_maxX, m_worldBoundingBox.m_maxY);

        Particle* newParticle = new Particle(randRadius, randPos.x, randPos.y, m_itemIDCounter++, randColor);
        m_particles.push_back(newParticle);
        m_SDS->Insert(newParticle);
    }

}

void World::AddForce(const Vec2f& _force)
{
    m_forces.push_back(_force);
}

void World::AddTorque(float _torque)
{
    m_torques.push_back(_torque);
}

void World::Update(float _dt)
{
    if (!m_particles.empty())
    {
        //this->SHG.FindNearestForAllCells();
        // [TODO] Remove this and incorporate it with the loops above:
        for (auto particle : m_particles)
        {
            if (particle->m_ID == 0)
            {
                particle->AddVelocityImpulse(pushForce);
            }


            // [TODO] Create a generalize "Reset" function to reset all the parameters
            //        back to their default values - if required.
            particle->m_bb.m_isOnlyOverlapping = false;
            particle->m_bb.m_isOnlyContained = false;

            Vec2f friction = Force::GenerateFrictionForce(particle, 4.337 * 50);
            particle->AddForce(friction);

            // May only need to be called if they were previously part of the collidingCircles vector list:
            particle->Update(_dt);
            CheckIfHitBoundary(particle);

            // Core process of re-inserting this into particles back into the SHG
            m_SDS->Update(particle);

            // Shift this over to another section
            // TESTING!
            if (particle->m_ID != m_particles[0]->m_ID)
            {
                if (m_particles[0]->m_bb.OnlyOverlaps(particle->m_bb))
                {
                    m_particles[0]->m_bb.m_isOnlyOverlapping = true;
                    particle->m_bb.m_isOnlyOverlapping = true;
                }
                else if (m_particles[0]->m_bb.OnlyContains(particle->m_bb) || particle->m_bb.OnlyContains(m_particles[0]->m_bb))
                {
                    m_particles[0]->m_bb.m_isOnlyContained = true;
                    particle->m_bb.m_isOnlyContained = true;
                }
            }
        }
    }
}

void World::CheckIfHitBoundary(Particle* particle)
{
    // int LEFT, TOP, RIGHT, BOTTOM;

    /*WorldToScreen(this->worldBoundingBox->minX, this->worldBoundingBox->minY, LEFT, TOP);
    WorldToScreen(this->worldBoundingBox->maxX, this->worldBoundingBox->maxY, RIGHT, BOTTOM);*/

    if (particle->m_pos.x - particle->m_radius <= m_worldBoundingBox.m_minX) {
        particle->m_pos.x = particle->m_radius;
        particle->m_vel.x *= -0.9;
    }
    else if (particle->m_pos.x + particle->m_radius >= m_worldBoundingBox.m_maxX) {
        particle->m_pos.x = m_worldBoundingBox.m_maxX - particle->m_radius;
        particle->m_vel.x *= -0.9;
    }


    if (particle->m_pos.y - particle->m_radius <= m_worldBoundingBox.m_minY) {
        particle->m_pos.y = particle->m_radius;
        particle->m_vel.y *= -0.9;
    }
    else if (particle->m_pos.y + particle->m_radius >= m_worldBoundingBox.m_maxY) {
        particle->m_pos.y = m_worldBoundingBox.m_maxY - particle->m_radius;
        particle->m_vel.y *= -0.9;
    }
}

void World::HandleCollision()
{
    if (m_collidingParticle.empty()) return;
}

int World::GetNumParticles()
{
    return m_particles.size();
}

Vec2i World::GetWorldSize()
{
    return m_worldSize;
}

std::vector<Particle*>& World::GetParticles()
{
    return m_particles;
}

void World::SetSelectedEntity(Particle* _particle)
{
    m_selectedParticle = _particle;
}

Particle* World::GetSelectedEntity()
{
    return m_selectedParticle;
}

//////////////////////////////
//                          //
//  SPATIAL DATA STRUCTURE  //
//                          //
//////////////////////////////
ISDS* World::SetCurrSDS(const SDS_TYPE _sdsType)
{
    // 1st Param :: Dimensions of world
    // 2nd Param :: Size of Cell
    // 3rd Param :: Max number of objects

    switch (_sdsType)
    {
    case SDS_TYPE::BRUTE_FORCE:
        // [TODO] Make an optimized yet still shitty Brute Force Class
        std::cout << "Brute Force was chosen\n";
        return nullptr;

    case SDS_TYPE::SPATIAL_HASH_GRID:
        return new SpatialHashGrid(m_worldBoundingBox, 50, 200);

    case SDS_TYPE::QUAD_TREE:
        // [TODO]
        std::cout << "Quad Tree was chosen\n";
        return nullptr;
    default:
        return nullptr;
    }

}


ISDS*       World::GetCurrSDS()         { return m_SDS;                 }
SDS_TYPE    World::GetCurrSDSType()     { return m_SDS->GetSDSType();   }
ENTITY_TYPE World::GetCurrEntityType()  { return m_entityType;          }


BoundingBox2D* World::GetSDSComponent() { return &m_selectedSDSComponent; };
void World::SetSDSComponent(const BoundingBox2D _bb)  { m_selectedSDSComponent = _bb; }