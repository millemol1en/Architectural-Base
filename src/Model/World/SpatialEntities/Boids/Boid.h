#pragma once
#ifndef BOID_H
#define BOID_H

#include "../../../Util/Vec2D.h"
#include "../ISpatialEntity.h"
#include "../../../Util/RandGen.h"
#include <vector>
#include <cstdint>
#include <SDL.h>	// [TODO] Maybe necessary to remove!
#include <iostream> // [TODO] Remove when finished testing


// [TODO] :: Change this to incorporate FOV.
//		  :: I guess this is assumed to be in pixels?
constexpr static int NN_RADIUS = 50;

struct Arrow
{
public:
	Arrow(Vec2f _pos, Vec2f _dir, SDL_Color _color, float _h, float _w);
	
	void  SetDirection();
	Vec2f GetDirection();
	
	void	  SetColor();
	SDL_Color GetColor();

private:
	// convexshape arrow;

	float m_height;
	float m_width;
	Vec2f m_pos;
	Vec2f m_dir;
	SDL_Color m_color;
};


struct Boid : public ISpatialEntity
{
public:

	bool m_showTrail;
	bool m_isPredator;
	float m_maxForce, m_maxSpeed;

	BoundingBox2D m_bb;

	Boid(int _ID, const float _x, const float _y, Uint32 _color, float _maxSpeed = 3.5f);
	~Boid() = default;

	// [Experimenting]	:: Idea is to keep track of n to m many previous positions the boid was in. Then use splines to trace a smooth path. 
	//					:: Then with some hope of maybe using it to create 
	std::vector<Vec2f> m_trail = std::vector<Vec2f>(10);


private:
	Vec2f Alignment(const std::vector<ISpatialEntity*>& _neighbouringBoids);
	Vec2f Separation(const std::vector<ISpatialEntity*>& _neighbouringBoids);
	Vec2f Cohesion(const std::vector<ISpatialEntity*>& _neighbouringBoids);

	void Flock(const std::vector<ISpatialEntity*>& _neighbouringBoids);
	bool InRange(const Vec2f& _v) const;
	
	float  GetDistance(const Vec2f& _v2) const;

	// [TODO] :: Only inherited methods should be public and or 
public:
	float GetMomentOfInertia() const override;
	void  Update(float _dt, std::vector<ISpatialEntity*> _neighbourEntities, const BoundingBox2D& _worldBB) override;
	void  HandleBorderCollision(const BoundingBox2D& _worldBB) override;
	void  CalcAABB() override;
};

#endif 
