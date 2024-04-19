#include "World.h"

World::World(float _gravity, Vec2i _position, Vec2i _dimensions) : m_selectedParticle(nullptr), m_itemIDCounter(0)
{
    m_G = _gravity;
    m_worldBoundingBox = BoundingBox2D(float(_position.x), float(_position.y), float(_dimensions.x), float(_dimensions.y));
    m_worldSize = _dimensions;

    m_SDS = SetCurrSDS(SDS_TYPE::SPATIAL_HASH_GRID);
}


World::~World()
{
    delete m_SDS;

    for (auto& entity : m_entities)
    {
        delete entity;
    }
}

//////////////////////////////
//                          //
//  PARTICLES || ENTITIES   //
//                          //
//////////////////////////////

void World::AddEntity()
{
    for (int i = 0; i < 100; i++)
    {
        Uint32 color = 0xFF665588;
        Vec2f randPos = RandGen::RandomPositionGenerator(m_worldBoundingBox.m_maxX, m_worldBoundingBox.m_maxY);

        Boid* newBoid = new Boid(randPos.x, randPos.y, color);

        // [TODO] Pack this into an insertion method:
        m_entities.push_back(newBoid);
        m_SDS->Insert(newBoid);
    }
}

// [TODO] Remove this and make use of a switch-case / if-statement:
void World::AddParticle()
{
    // [TESTING / REMOVE LATER]
    Particle* mainParticle = new Particle(12, Graphics::f_Width() / 2, Graphics::f_Height() / 2, m_itemIDCounter++, 0xFFFFFFFF);
    m_entities.push_back(mainParticle);
    m_SDS->Insert(mainParticle);

    for (int i = 0; i < 100; i++)
    {
        int randColor  = RandGen::RandomColorGenerator();
        int randRadius = RandGen::RandomRadiusGenerator(12);
        Vec2f randPos  = RandGen::RandomPositionGenerator(m_worldBoundingBox.m_maxX, m_worldBoundingBox.m_maxY);

        Particle* newParticle = new Particle(randRadius, randPos.x, randPos.y, m_itemIDCounter++, randColor);
        m_entities.push_back(newParticle);
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
    if (!m_entities.empty())
    {
        for (auto& entity : m_entities)
        {
            ////////////////////TESTING//////////////////////////////////////////////
            entity->m_bb.m_isOnlyOverlapping = false;
            entity->m_bb.m_isOnlyContained = false;

            if (entity->m_ID != m_entities[0]->m_ID)
            {
                if (m_entities[0]->m_bb.OnlyOverlaps(entity->m_bb))
                {
                    m_entities[0]->m_bb.m_isOnlyOverlapping = true;
                    entity->m_bb.m_isOnlyOverlapping = true;
                }
                else if (m_entities[0]->m_bb.OnlyContains(entity->m_bb) || entity->m_bb.OnlyContains(m_entities[0]->m_bb))
                {
                    m_entities[0]->m_bb.m_isOnlyContained = true;
                    entity->m_bb.m_isOnlyContained = true;
                }
            }
            //////////////////////////////////////////////////////////////////////////


            std::vector<ISpatialEntity*> neighbours = m_SDS->QueryNearestNeighbour(entity);

            switch(entity->GetEntityType())
            {
                case ENTITY_TYPE::PARTICLE:
                {
                    // [TODO] Clean this up so all of these methods are in particle and "World" only calls 1 methods
                    Particle* particle = static_cast<Particle*>(entity);

                    if (particle->m_ID == 0)
                    {
                        particle->AddVelocityImpulse(pushForce);
                    }

                    Vec2f friction = Force::GenerateFrictionForce(particle, 4.337 * 50);
                    particle->AddForce(friction);

                    // [TODO] Make so that potentially colliding circles are mashed together into a vector, whereby we can handle them from there
                    particle->Update(_dt, neighbours, m_worldBoundingBox);

                    // Core process of re-inserting this into particles back into the SHG
                    m_SDS->Update(particle);

                    break;
                }

                case ENTITY_TYPE::BOID:
                {
                    Boid* boid = static_cast<Boid*>(entity);

                    boid->Update(_dt, neighbours, m_worldBoundingBox);

                    m_SDS->Update(boid);

                    break;
                }
            }
        }        
    }
}



void World::HandleCollision()
{
    if (m_collidingParticle.empty()) return;
}

int World::GetNumParticles()
{
    return m_entities.size();
}

Vec2i World::GetWorldSize()
{
    return m_worldSize;
}

std::vector<ISpatialEntity*>& World::GetEntities()
{
    return m_entities;
}

void World::SetSelectedEntity(ISpatialEntity* _particle)
{
    m_selectedParticle = _particle;
}

ISpatialEntity* World::GetSelectedEntity()
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


BoundingBox2D* World::GetSDSComponent() { return &m_selectedSDSComponent; };
void World::SetSDSComponent(const BoundingBox2D _bb)  { m_selectedSDSComponent = _bb; }