#pragma once
#ifndef I_SPATIAL_ENTITY_H
#define I_SPATIAL_ENTITY_H

#include "../../Util/Vec2D.h"
#include "../../Util/BoundingBox.h"
#include "../../Constants/CONST_SDS_ENTITY_TYPE.h"
#include <vector>
#include <SDL_stdinc.h>

struct ISpatialEntity
{
public:
	// [0] Spatial Hash Grid:
	int m_gridIndex;
	int m_indexPosInCell;
	int m_queryID;

	// [1] Quad Tree:




	// [2] BVH:


	// [TODO] :: Make private and make Getters / Setters
public:
	// [0] Entity ID Number:
	int m_ID;
	
	// [1] Physics variables:
	float m_sumTorque	= 0.0f;
	Vec2f m_sumForces	= Vec2f(0, 0);
	Vec2f m_pos			= Vec2f(0, 0);
	Vec2f m_vel			= Vec2f(0, 0);
	Vec2f m_acc			= Vec2f(0, 0);
	Vec2f m_prevPos		= Vec2f(0, 0);
	Vec2f m_dir			= Vec2f(0, 0);

	float m_friction;
	float m_restitution;
	float m_mass;
	float m_invMass;
	float m_I;
	float m_invI;
	float m_rotation;
	float m_angularVel;
	float m_angularAcc;

	// [2] Dimensional variables:
	int m_width;
	int m_height;
	BoundingBox2D m_bb;		// [TODO] :: Remove this and replace with width & height like Simondev
	ENTITY_TYPE m_et;

	// [3] Styling:
	Uint32 m_color;

	bool m_isColliding   = false;
	bool m_isContainedIn = false;
	bool m_isOverlapping = false;

public:
	// [1] Simple Getters:
	Vec2f GetPos()	{ return m_pos; }
	Vec2f GetVel()	{ return m_vel; }
	Vec2f GetAcc()	{ return m_acc; }
	Vec2f GetDir()	{ return m_dir; }
	BoundingBox2D GetEntityBB()		{ return m_bb;	}
	ENTITY_TYPE GetEntityType()		{ return m_et;	}

	// [2] Simple Setters:
	void SetEntityVelocity(const Vec2f& _vel)		{ m_vel = _vel; }
	void SetEntityAcceleration(const Vec2f& _acc)	{ m_acc = _acc; }
	void SetEntityPosition(const Vec2f& _pos)		{ m_pos = _pos; }
	void SetEntityBB(const BoundingBox2D& _bb)		{ m_bb = _bb;	}
	void SetEntityType(const ENTITY_TYPE& _et)      { m_et = _et;	}
	void ClearForces()								{ m_sumForces = Vec2f(0.0, 0.0); }
	void ClearTorque()								{ m_sumTorque = 0.0; }
	void AddForce(const Vec2f& _force)				{ m_sumForces += _force; }
	void AddTorque(float _torque)					{ m_sumTorque += _torque; }


	// [3] 
	void  AddVelocityImpulse(const Vec2f& j) 
	{ 
		m_vel += (j * m_invMass);
	}

	// [2]
	void  AddAngularImpulse(const Vec2f& j, const Vec2f& r)
	{
		m_vel += j * m_invMass;
		m_angularVel += r.CrossProd(j) * m_invI;
	}

	// [3] Semi-implicit Euler integration:
	void EulerIntegration(float _dt)
	{
		m_acc = m_sumForces * m_invMass;

		m_vel += m_acc * _dt;

		Vec2f deltaVel = m_vel * _dt;

		m_pos += deltaVel;

		ClearForces();
	}

	void AngularEulerIntegration(float _dt)
	{
		m_angularAcc = m_sumTorque * m_invI;

		m_angularVel += m_angularAcc * _dt;

		m_rotation += m_angularVel * _dt;

		ClearTorque();
	}

	void VerletIntegration(float _dt)
	{
	}

	void AngularVerletIntegration(float _dt)
	{
	}

	////////////////////
	//
	//	INHERITED METHODS
	//
	/////////////////////

	virtual float GetMomentOfInertia() const = 0;
	virtual void  Update(float _dt, std::vector<ISpatialEntity*> _neighbourEntities, const BoundingBox2D& _worldBB) = 0;
	virtual void  HandleBorderCollision(const BoundingBox2D& _worldBB) = 0;
};

#endif 
