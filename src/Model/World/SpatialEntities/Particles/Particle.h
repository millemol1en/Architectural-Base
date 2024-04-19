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
	
	// LOCAL
	Particle() = default;	// Remove this and make sure the other 2 constructors always have values for their attributes
	Particle(int _radius, float _x, float _y, int _ID, Uint32 _color);
	Particle(int _radius, float _x, float _y, int _ID, Uint32 _color, int _mass, int _friction, int _restitution);
	~Particle() = default;

	bool  IsPointInParticle(const Vec2f _point) const;
	bool  AreParticlesColliding(const Particle* _particle) const;


	void  InitBoundingBox();
	void  UpdateBoundingBox(float _offsetX, float _offsetY);

	// INHERITED


	void  Update(float _dt, std::vector<ISpatialEntity*> _neighbourEntities, const BoundingBox2D& _worldBB) override;
	float GetMomentOfInertia() const override;
	void  CalcAABB() override;
	void  HandleBorderCollision(const BoundingBox2D& _worldBB) override;


};

#endif // !1
