#include "./Particle.h"
#include "../../View/Graphics.h"

Particle::Particle(int _radius, float _x, float _y, int _ID, Uint32 _color) : m_mass(1.0), m_friction(0.5), m_restitution(0.5), m_isColliding(false) 
{
    m_color = _color;
    m_ID = _ID;
    m_radius = _radius;
    m_pos.x = _x;
    m_pos.y = _y;
    m_vel = Vec2f(0, 0);
    m_acc = Vec2f(0, 0);
    m_rotation = 0.0;
    m_angularVel = 0.0;
    m_angularAcc = 0.0;
    m_sumForces = Vec2f(0, 0);
    m_sumTorque = 0.0;
    m_invMass = (m_mass > 0.0) ? 1.0 / m_mass : 0.0;
    m_I = Particle::GetMomentOfInertia() * m_mass;
    m_invI = (m_I > 0.0) ? 1.0 / m_I : 0.0;
    m_bb = BoundingBox2D(_radius, _x, _y);
}

Particle::Particle(int _radius, float _x, float _y, int _ID, Uint32 _color, int _mass, int _friction, int _restitution)
{
    m_color = _color;
    m_ID = _ID;
    m_radius = _radius;
    m_pos.x = _x;
    m_pos.y = _y;
    m_mass = _mass;
    m_friction = _friction;
    m_restitution = _restitution;
    m_vel = Vec2f(0, 0);
    m_acc = Vec2f(0, 0);
    m_rotation = 0.0;
    m_angularVel = 0.0;
    m_angularAcc = 0.0;
    m_sumForces = Vec2f(0, 0);
    m_sumTorque = 0.0;
    m_invMass = (m_mass > 0.0) ? 1.0 / m_mass : 0.0;
    m_I = Particle::GetMomentOfInertia() * m_mass;
    m_invI = (m_I > 0.0) ? 1.0 / m_I : 0.0;
    m_bb = BoundingBox2D(_radius, _x, _y);
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
void  Particle::AddForce(const Vec2f& _force)       { m_sumForces += _force; }
void  Particle::AddTorque(float _torque)            { m_sumTorque += _torque; }
void  Particle::ClearForces()                       { m_sumForces = Vec2f(0.0, 0.0); }
void  Particle::ClearTorque()                       { m_sumTorque = 0.0; }
void  Particle::AddVelocityImpulse(const Vec2f& j)  { m_vel += j * m_invMass; }
void  Particle::AddAngularImpulse(const Vec2f& j, const Vec2f& r)
{
    m_vel += j * m_invMass;
    m_angularVel += r.Cross(j) * m_invI;
}

// 04. Basic Linear Integration:
void Particle::LinearIntegration(float _dt)
{
    // 04.1: Find the acceleration based on the forces that are being applied and the mass
    m_acc = m_sumForces * m_invMass;

    // 04.2: Integrate the acceleration to find the new velocity
    m_vel += m_acc * _dt;

    // 04.3: Integrate the velocity to find the new position
    Vec2f deltaVel = m_vel * _dt;

    m_pos += deltaVel;

    InitBoundingBox();

    // 04.4: Clear all the forces acting on the object before the next physics step
    ClearForces();
}

// 05. Verlet Integration 
// TODO!!!

// 06. Basic Angular Velocity Integration:
void Particle::AngularIntegration(float _dt)
{

    // 06.1: Find the angular acceleration based on the torque that is being applied and the moment of inertia
    m_angularAcc = m_sumTorque * m_invI;

    // 06.2: Integrate the angular acceleration to find the new angular velocity
    m_angularVel += m_angularAcc * _dt;

    // 06.3: Integrate the angular velocity to find the new rotation angle
    m_rotation += m_angularVel * _dt;

    // 06.4: Clear all the torque acting on the object before the next physics step
    ClearTorque();
}

void Particle::Update(float _dt)
{
    LinearIntegration(_dt);
    AngularIntegration(_dt);
}

void Particle::UpdateParticle(float _offsetX, float _offsetY)
{
    m_pos.x += _offsetX;
    m_pos.y += _offsetY;

    m_pos.x = (m_pos.x < Graphics::f_Width() ? m_pos.x : (m_pos.x < 0) ? 0 : m_pos.x);
    m_pos.y = (m_pos.y < Graphics::f_Height() ? m_pos.y : (m_pos.y < 0) ? 0 : m_pos.y);

    UpdateBoundingBox(_offsetX, _offsetY);
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