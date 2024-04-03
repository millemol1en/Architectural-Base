#pragma once
#ifndef BOUNDINGBOX2D_H 
#define BOUNDINGBOX2D_H

#include "Vec2.h"


struct BoundingBox2D
{

public:
	float m_minX, m_minY, m_maxX, m_maxY;

	bool m_isBBColliding;
	bool m_isOnlyOverlapping;
	bool m_isOnlyContained;

	BoundingBox2D() = default;
	BoundingBox2D(int _radius, float _x, float _y);
	BoundingBox2D(float _x, float _y, float _width, float _height);
	BoundingBox2D(Vec2i topLeft, Vec2i bottomRight);
	BoundingBox2D(Vec2f topLeft, Vec2f bottomRight);
	~BoundingBox2D() = default;

	bool IsPointInside(const Vec2f& other) const;
	bool OnlyOverlaps(const BoundingBox2D& other) const;
	bool OnlyContains(const BoundingBox2D& other) const;
	bool OverlapsOrContains(const BoundingBox2D& other) const;
	void UpdateBoundingBox2D(float offsetX, float offsetY);
	void InitBoundingBox2D(int circleRadius, float circlePosX, float circlePosY);			// For Circle
	void InitBoundingBox2D(float _startX, float _startY, float _width, float _height);	// For Viewport
};

#endif