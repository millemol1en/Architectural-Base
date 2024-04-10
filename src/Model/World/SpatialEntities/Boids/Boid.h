#pragma once
#ifndef BOID_H
#define BOID_H

#include "../../../Util/Vec2.h"
#include "../ISpatialEntity.h"
#include "../../../Util/Vec2D.h"
#include <cstdint>
#include <SDL.h>	// [TODO] Maybe necessary to remove!

struct Arrow
{
public:
	explicit Arrow(Vec2f _pos, Vec2f _dir, SDL_Color _color, float _h, float _w);
	
	void  SetDirection();
	Vec2f GetDirection();
	
	void	  SetColor();
	SDL_Color GetColor();

private:
	// convexshape arrow;

	float m_height;
	float m_width;
	Vec2f _pos;
	Vec2f _dir;
	SDL_Color _color;
};


struct Boid : public ISpatialEntity
{
public:
	// [0] Spatial Hash Grid:
	int m_gridIndex;
	int m_indexPosInCell;
	int m_queryID;

	// [1] Quad Tree:



	Boid();
	~Boid() = default;





};

#endif 
