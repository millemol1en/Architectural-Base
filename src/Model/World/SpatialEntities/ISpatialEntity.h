#pragma once
#ifndef I_SPATIAL_ENTITY_H
#define I_SPATIAL_ENTITY_H

#include "../../Util/Vec2D.h"
#include "../../Util/BoundingBox.h"
#include "../../Constants/CONST_SDS_ENTITY_TYPE.h"

struct ISpatialEntity
{
public:
	// [0] Spatial Hash Grid:
	int m_gridIndex;
	int m_indexPosInCell;
	int m_queryID;

	// [1] Quad Tree:




public:
	int m_ID;
	Vec2f m_pos;
	BoundingBox2D m_bb;
	Vec2f m_vel;
	Vec2f m_acc;
	ENTITY_TYPE m_et;

	bool m_isColliding   = false;	// Fastest
	bool m_isContainedIn = false;
	bool m_isOverlapping = false;


	
public:
	Vec2f GetEntityPosition()		{ return m_pos; }
	Vec2f GetEntityVelocity()		{ return m_vel; }
	Vec2f GetEntityAcceleration()	{ return m_acc; }
	BoundingBox2D GetEntityBB()		{ return m_bb;	}
	ENTITY_TYPE GetEntityType()		{ return m_et;	}

	void SetEntityVelocity(const Vec2f& _vel)		{ m_vel = _vel; }
	void SetEntityAcceleration(const Vec2f& _acc)	{ m_acc = _acc; }
	void SetEntityPosition(const Vec2f& _pos)		{ m_pos = _pos; }
	void SetEntityBB(const BoundingBox2D& _bb)		{ m_bb = _bb;	}
	void SetEntityType(const ENTITY_TYPE& _et)      { m_et = _et;	}
};

#endif 
