#include "Boid.h"

Boid::Boid(int _ID, const float _x, const float _y, Uint32 _color, float _maxSpeed)
{
	// Inherited:
	m_ID			= _ID;
	m_pos			= { _x, _y };
	m_mass			= 1.0;
	m_friction		= 0.5;
	m_restitution	= 0.5;
	m_rotation		= 0.0;
	m_angularVel	= 0.0;
	m_angularAcc	= 0.0;
	m_invMass		= (m_mass > 0.0) ? 1.0 / m_mass : 0.0;
	m_color = _color;
	m_et = ENTITY_TYPE::BOID;
	m_vel = Vec2f(RandGen::RandValInRange(2.0, 6.0), RandGen::RandValInRange(2.0, 6.0));

	// Local:
	m_maxForce = 3.0;
	m_maxSpeed = _maxSpeed;

}

// [1] Alignment 
//		-> This will make a Boid steer towards the average heading of local flockmates
//		-> As such, we calculate the sum velocity of the entire school.
//		-> Input is an "std::vector" of all the Boids located from performing a Nearest Neighbour query.
//  
Vec2f Boid::Alignment(const std::vector<ISpatialEntity*>& _neighbouringBoids)
{
	if (!_neighbouringBoids.empty())
	{
		Vec2f sumVel      = { 0.0f, 0.0f };
		int numBoidsInFOV = 0;

		for (const auto& boid : _neighbouringBoids)
		{
			bool isInRange = Boid::InRange(boid->m_pos);

			if (true)
			{
				sumVel += boid->m_vel;
				numBoidsInFOV++;
			}
		}
		
		// [TODO] :: Currently this just calculates the direction vector and puts a limiter on the Boids velocity.
		sumVel /= static_cast<float>(numBoidsInFOV);;
		sumVel.Normalize();
		sumVel *= m_maxSpeed;

		return sumVel;

		//Vec2f steer;
		//steer = sumVel - m_vel;
		//return steer; // .Clamp(0.1f, 0.1f, m_maxForce, m_maxForce);
	}

	return Vec2f{};
}

// [3] Takes all the Boids located from the Nearest Neighbour query and determines whether they are in FOV:
Vec2f Boid::Cohesion(const std::vector<ISpatialEntity*>& _neighbouringBoids)
{
	if (!_neighbouringBoids.empty())
	{
		Vec2f avgPos     = { 0.0f, 0.0f };
		Vec2f desiredVel = { 0.0f, 0.0f };
		int   numBoidsInFOV = 0;

		for (const auto& boid : _neighbouringBoids)
		{
			bool isInRange = Boid::InRange(boid->m_pos);

			if (true)
			{
				avgPos += boid->m_pos;
				numBoidsInFOV++;
			}
		}

		avgPos /= static_cast<float>(numBoidsInFOV);;
		desiredVel -= avgPos;
		desiredVel.Normalize();
		desiredVel *= m_maxSpeed;

		return desiredVel;

		//m_acc = desiredVel - m_vel;
		//return m_acc; // .Clamp(0.1f, 0.1f, m_maxForce, m_maxForce);
	}

	return Vec2f{};
}

// [3] Separation:
//		-> This makes the Boids away from others crowding local flockmates

Vec2f Boid::Separation(const std::vector<ISpatialEntity*>& _neighbouringBoids)
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

			desiredVel += (m_pos - boid->m_pos) / (dist * dist);	// [TODO] Change this to utilize vector operations
		}
		desiredVel /= static_cast<float>(numBoidsInFOV);
		desiredVel.Normalize();
		desiredVel *= m_maxSpeed;

		return desiredVel;
		//desiredVel -= m_vel;
		//return m_acc; // .Clamp(0.1f, 0.1f, m_maxForce, m_maxForce);
	}

	return Vec2f{};
}

void Boid::Update(float _dt, std::vector<ISpatialEntity*> _neighbourEntities, const BoundingBox2D& _worldBB)
{
	// Flock(_neighbourEntities);

	// AddVelocityImpulse(RandGen::RandomVelocityGenerator(2, 4));
	EulerIntegration(_dt);
	AngularEulerIntegration(_dt);
}

void Boid::Flock(const std::vector<ISpatialEntity*>& _neighbouringBoids)
{
	const Vec2f& sep = Separation(_neighbouringBoids);
	const Vec2f& ali = Alignment(_neighbouringBoids);
	const Vec2f& coh = Cohesion(_neighbouringBoids);

	std::cout << "Sep Force :: " << sep.ToString() << "\n";
	std::cout << "Ali Force :: " << ali.ToString() << "\n";
	std::cout << "Coh Force :: " << coh.ToString() << "\n";

	if (sep > 0.001f) AddVelocityImpulse(sep);
	if (ali > 0.001f) AddVelocityImpulse(ali);
	if (coh > 0.001f) AddVelocityImpulse(coh);
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


//////////////////////////
//						//
//	INHERITED METHODS	//
//						//
//////////////////////////

void Boid::CalcAABB()
{
}

float Boid::GetMomentOfInertia() const
{

	// Implement rotational moment of inertia for boid

	return 0.5 * (1);
}