#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H

#include "../../../Util/BoundingBox.h"
#include "../../../../View/Graphics.h"
#include "../ISpatialEntity.h"
#include <SDL.h>
#include <cstdint>

struct Particle : public ISpatialEntity 
{	
	/////////////////////////////////////////////////////
	// RELEVANT ONLY TO THE PARTICLES STRUCT - FOR NOW //
	/////////////////////////////////////////////////////
	int m_radius;
	
	Vec2f m_sumForces;
	float m_sumTorque;

	float m_friction;
	float m_restitution;
	float m_mass;
	float m_invMass;
	float m_I;
	float m_invI;
	float m_rotation;
	float m_angularVel;
	float m_angularAcc;

	Uint32 m_color;

	Particle() = default;	// Remove this and make sure the other 2 constructors always have values for their attributes
	Particle(int _radius, float _x, float _y, int _ID, Uint32 _color);
	Particle(int _radius, float _x, float _y, int _ID, Uint32 _color, int _mass, int _friction, int _restitution);
	~Particle() = default;

	void ClearTorque();
	void ClearForces();

	void InitBoundingBox();
	void UpdateParticle(float _offsetX, float _offsetY);
	void UpdateBoundingBox(float _offsetX, float _offsetY);
	void AddVelocityImpulse(const Vec2f& _j);
	void AddAngularImpulse(const Vec2f& _j, const Vec2f& _r);
	void Update(float _dt);
	void LinearIntegration(float _dt);
	void AngularIntegration(float _dt);
	void AddForce(const Vec2f& _force);
	void AddTorque(float _torque);
	float GetMomentOfInertia() const;
	bool IsPointInParticle(const Vec2f _point) const;
	bool AreParticlesColliding(const Particle* _particle) const;

};

#endif // !1
