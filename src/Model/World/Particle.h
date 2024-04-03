#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H

#include "../Util/BoundingBox.h"
#include <SDL.h>
#include <cstdint>

struct Particle {
	// [TODO] Change the architecture to allow for different kinds of spatial entities:
	int m_gridIndex;
	int m_indexPosInCell;
	int m_queryID;



	
	/////////////////////////////////////////////////
	// PROPERTIES RELEVANT TO ALL SPATIAL ENTITIES //
	/////////////////////////////////////////////////
	int			  m_ID;
	Vec2f		  m_pos;
	BoundingBox2D m_bb;

	bool m_isColliding;
	bool m_showNeighbors;
	
	int m_queryRadius;
	BoundingBox2D m_queryBoundary;

	/////////////////////////////////////////////////////
	// RELEVANT ONLY TO THE PARTICLES STRUCT - FOR NOW //
	/////////////////////////////////////////////////////
	int m_radius;
	Vec2f m_vel;
	Vec2f m_acc;

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

	Particle() = default;
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
