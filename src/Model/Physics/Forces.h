#pragma once
#ifndef FORCE_H
#define FORCE_H

#include "../Util/Vec2.h"
#include "../World/Particle.h"

struct Force
{
	static Vec2f GenerateFrictionForce(const Particle* _particle, float _k)
	{
		Vec2f fricForce = Vec2f(0.0, 0.0);

		Vec2f fricDirection = _particle->m_vel.UnitVector() * -1.0; // Friction goes in opp. direction to particles velocity

		float fricMagnitude = _k;

		fricForce = fricDirection * fricMagnitude;

		return fricForce;
	}
};

#endif 