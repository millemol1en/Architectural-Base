#include "./Particle.h"

Particle::Particle(int _radius, float _x, float _y, int _ID, Uint32 _color)
{
    m_mass          = 1.0;
    m_friction      = 0.5;
    m_restitution   = 0.5;
    m_et            = ENTITY_TYPE::PARTICLE;
    m_color         = _color;
    m_ID            = _ID;
    m_radius        = _radius;
    m_pos.x         = _x;
    m_pos.y         = _y;
    m_vel           = Vec2f(0, 0);
    m_acc           = Vec2f(0, 0);
    m_rotation      = 0.0;
    m_angularVel    = 0.0;
    m_angularAcc    = 0.0;
    m_sumForces     = Vec2f(0, 0);
    m_sumTorque     = 0.0;
    m_invMass       = (m_mass > 0.0) ? 1.0 / m_mass : 0.0;
    m_I             = Particle::GetMomentOfInertia() * m_mass;
    m_invI          = (m_I > 0.0) ? 1.0 / m_I : 0.0;
    m_bb            = BoundingBox2D(_radius, _x, _y);
}

Particle::Particle(int _radius, float _x, float _y, int _ID, Uint32 _color, int _mass, int _friction, int _restitution)
{
    m_et            = ENTITY_TYPE::PARTICLE;
    m_color         = _color;
    m_ID            = _ID;
    m_radius        = _radius;
    m_pos.x         = _x;
    m_pos.y         = _y;
    m_mass          = _mass;
    m_friction      = _friction;
    m_restitution   = _restitution;
    m_vel           = Vec2f(0, 0);
    m_acc           = Vec2f(0, 0);
    m_rotation      = 0.0;
    m_angularVel    = 0.0;
    m_angularAcc    = 0.0;
    m_sumForces     = Vec2f(0, 0);
    m_sumTorque     = 0.0;
    m_invMass       = (m_mass > 0.0) ? 1.0 / m_mass : 0.0;
    m_I             = Particle::GetMomentOfInertia() * m_mass;
    m_invI          = (m_I > 0.0) ? 1.0 / m_I : 0.0;
    m_bb            = BoundingBox2D(_radius, _x, _y);
}

// 01. Check to see whether or not a point (namely the mouse) is inside a circle:
bool Particle::IsPointInParticle(const Vec2f point) const
{
    float distX = (m_pos.x - point.x);       // a
    float distY = (m_pos.y - point.y);       // b
    float radiiSqrd = (m_radius * m_radius); // c

    return (fabs((distX * distX) + (distY * distY)) <= radiiSqrd);
}

// 02. Primitive method to check whether or not 2 circles are colliding:
bool Particle::AreParticlesColliding(const Particle* other) const
{
    float distX = (m_pos.x - other->m_pos.x);      // a
    float distY = (m_pos.y - other->m_pos.y);      // b
    float sumRadii = (m_radius + other->m_radius); // c

    return (fabs((distX * distX) + (distY * distY)) <= sumRadii * sumRadii);
}



// 03. Physics related methods:
float Particle::GetMomentOfInertia() const          { return 0.5 * (m_radius * m_radius); }


void Particle::Update(float _dt, std::vector<ISpatialEntity*> _neighbourEntities, const BoundingBox2D& _worldBB)
{
    // VerletIntegration(_dt);
    // AngularVerletIntegration(_dt);
    EulerIntegration(_dt);
    AngularEulerIntegration(_dt);
    HandleBorderCollision(_worldBB);
    InitBoundingBox();
    // CheckCollision();
}


// Update the position and dimensions of the Bounding Box in accordance to the _offsetX and _offsetY
void Particle::UpdateBoundingBox(float _offsetX, float _offsetY)
{
    m_bb.UpdateBoundingBox2D(_offsetX, _offsetY);
}

// 08. Initialize / Reset the Bounding Box:
void Particle::InitBoundingBox()
{
    m_bb.InitBoundingBox2D(m_radius, m_pos.x, m_pos.y);
}

void Particle::CalcAABB()
{
}

void Particle::HandleBorderCollision(const BoundingBox2D& _worldBB)
{
    // [0] Left:
    if (m_pos.x - m_radius <= _worldBB.m_minX) {
        m_pos.x = m_radius;
        m_vel.x *= -0.9;
    }
    // [1] Right:
    else if (m_pos.x + m_radius >= _worldBB.m_maxX) {
        m_pos.x = _worldBB.m_maxX - m_radius;
        m_vel.x *= -0.9;
    }

    // [2] Top:
    if (m_pos.y - m_radius <= _worldBB.m_minY) {
        m_pos.y = m_radius;
        m_vel.y *= -0.9;
    }
    // [3] Bottom:
    else if (m_pos.y + m_radius >= _worldBB.m_maxY) {
        m_pos.y = _worldBB.m_maxY - m_radius;
        m_vel.y *= -0.9;
    }
}