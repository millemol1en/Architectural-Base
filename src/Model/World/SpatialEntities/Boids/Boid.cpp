#include "Boid.h"

Boid::Boid(const float _x, const float _y, Uint32 _color, float _maxSpeed)
{
	m_pos = { _x, _y };
	m_mass = 1.0;

	m_color = _color;
	m_et = ENTITY_TYPE::BOID;
}

// [1] Alignment 
//		-> This will make a Boid steer towards the average heading of local flockmates
//		-> As such, we calculate the sum velocity of the entire school.
//		-> Input is an "std::vector" of all the Boids located from performing a Nearest Neighbour query.
//  
Vec2f Boid::Alignment(const std::vector<Boid*>& _neighbouringBoids)
{
	if (!_neighbouringBoids.empty())
	{
		Vec2f sumVel      = { 0.0f, 0.0f };
		int numBoidsInFOV = 0;

		for (const auto& boid : _neighbouringBoids)
		{
			bool isInRange = Boid::InRange(boid->m_pos);

			if (isInRange)
			{
				sumVel += boid->m_vel;
				numBoidsInFOV++;
			}
		}
		
		// [TODO] :: Currently this just calculates the direction vector and puts a limiter on the Boids velocity.
		sumVel /= static_cast<float>(numBoidsInFOV);;
		sumVel.Normalize();
		sumVel *= m_maxSpeed;

		Vec2f steer;
		steer = sumVel - m_vel;
		steer.Clamp(0.1f, 0.1f, m_maxForce, m_maxForce);
		return steer;
	}

	return Vec2f{};
}

// [3] Takes all the Boids located from the Nearest Neighbour query and determines whether they are in FOV:
Vec2f Boid::Cohesion(const std::vector<Boid*>& _neighbouringBoids)
{
	if (!_neighbouringBoids.empty())
	{
		Vec2f avgPos     = { 0.0f, 0.0f };
		Vec2f desiredVel = { 0.0f, 0.0f };
		int   numBoidsInFOV = 0;

		for (const auto& boid : _neighbouringBoids)
		{
			bool isInRange = Boid::InRange(boid->m_pos);

			if (isInRange)
			{
				avgPos += boid->m_pos;
				numBoidsInFOV++;
			}
		}

		avgPos /= static_cast<float>(numBoidsInFOV);;
		desiredVel -= avgPos;
		desiredVel.Normalize();
		desiredVel *= m_maxSpeed;
		m_acc = desiredVel - m_vel;
		return m_acc.Clamp(0.1f, 0.1f, m_maxForce, m_maxForce);		// [CONSIDERATION] - Currently, the clamp is on all 3 attributes, this may allow for implementation of a primitive evolution system.
	}

	return Vec2f{};
}

// [3] Separation:
//		-> This makes the Boids away from others crowding local flockmates

Vec2f Boid::Separation(const std::vector<Boid*>& _neighbouringBoids)
{
	if (!_neighbouringBoids.empty())
	{
		Vec2f desiredVel = { 0.0f, 0.0f };
		int   numBoidsInFOV = 0;

		for (const auto& boid : _neighbouringBoids)
		{
			// [TODO] :: Add different types of boids like predator and prey:
			float dist = GetDistance(boid->m_pos);
			if (dist < 1e-2) continue;

			desiredVel += (m_pos - boid->m_pos) / (dist * dist);
		}
		desiredVel /= static_cast<float>(numBoidsInFOV);
		desiredVel.Normalize();
		desiredVel *= m_maxSpeed;
		desiredVel -= m_vel;
		return m_acc.Clamp(0.1f, 0.1f, m_maxForce, m_maxForce);		// [CONSIDERATION] - Currently, the clamp is on all 3 attributes, this may allow for implementation of a primitive evolution system.
	}

	return Vec2f{};
}

void Boid::Update(float _dt, std::vector<ISpatialEntity*> _neighbourEntities, const BoundingBox2D& _worldBB)
{

	VerletIntegration(_dt);
	AngularVerletIntegration(_dt);
}

void Boid::Flock(const std::vector<Boid*>& _neighbouringBoids)
{
	const Vec2f& sep = Separation(_neighbouringBoids);
	const Vec2f& ali = Alignment(_neighbouringBoids);
	const Vec2f& coh = Cohesion(_neighbouringBoids);

	AddForce(sep);
	AddForce(ali);
	AddForce(coh);
}

void Boid::HandleBorderCollision(const BoundingBox2D& _worldBB)
{
	if (m_pos.x < _worldBB.m_minX) m_pos.x += _worldBB.m_maxX;
	if (m_pos.y < _worldBB.m_minY) m_pos.y += _worldBB.m_maxY;
	if (m_pos.x > _worldBB.m_maxX) m_pos.x -= _worldBB.m_maxX;
	if (m_pos.y > _worldBB.m_maxY) m_pos.y -= _worldBB.m_maxY;
}

bool Boid::InRange(const Vec2f& _v) const
{
	float a = (m_pos.x - _v.x);
	float b = (m_pos.y - _v.y);
	float c = (NN_RADIUS * NN_RADIUS);

	return ((a * a) + (b * b) >= c);
}

float Boid::GetDistance(const Vec2f& _otherV) const
{
	float dx = m_pos.x - _otherV.x;
	float dy = m_pos.y - _otherV.y;
	
	return std::sqrt(((dx * dx) + (dy * dy)));
}

float Boid::GetMomentOfInertia() const
{

	// Implement rotational moment of inertia for boid

	return 0.5 * (1);
}