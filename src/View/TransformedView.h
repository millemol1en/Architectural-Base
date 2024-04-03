#pragma once
#ifndef TRANSFORMED_VIEW_H
#define TRANSFORMED_VIEW_H

/////////////////////////////////////////////
// The idea with this struct is to add an additional layer prior to drawing.
// As the name would suggest, this layer transforms our objects between world and screen space.
// 
// 
// 
//




#include "../Model/Util/Vec2.h"
#include "../Model/Util/BoundingBox.h"
#include "./Graphics.h"
#include <cmath>
#include <cstdint>

#include <iostream> // [TODO] Remove when done

struct TransformedView
{

private:
	Vec2f m_worldOffset = { 0.0f, 0.0f };
	Vec2f m_worldScale = { 1.0f, 1.0f };
	Vec2f m_RecipPixel = { 1.0f, 1.0f };	// Reciprocal
	Vec2f m_pixelScale = { 1.0f, 1.0f };
	Vec2f m_startPan = { 0.0f, 0.0f };
	Vec2i m_viewArea;						// The area of the screen
	Vec2i m_worldArea;						// The area of the world

	bool m_isPanning = false;

public:
	TransformedView(const Vec2i& _screenArea = { Graphics::i_Width(), Graphics::i_Height() }, const Vec2i& _worldArea = { Graphics::i_Width(), Graphics::i_Height() }, const Vec2f& _pixelScale = { 1.0f, 1.0f });
	// void Init(const Vec2i& _viewArea = { Graphics::i_Width(), Graphics::i_Height() }, const Vec2f& _pixelScale = {1.0f, 1.0f});


	void SetWorldOffset(const Vec2f& _offset);
	void MoveWorldOffset(const Vec2f& _deltaOffset);
	void SetWorldScale(const Vec2f& _scale);
	void SetViewArea(const Vec2i& _screenArea);
	void SetWorldArea(const Vec2i& _screenArea);
	Vec2f GetWorldTopLeft() const;
	Vec2f GetWorldBottomRight() const;
	Vec2f GetWorldVisibleArea() const;

	void ZoomAtScreenPos(const float _deltaZoom, const Vec2i& _pos);
	void SetZoom(const float _zoom, const Vec2i& _pos);
	void StartPan(const Vec2i& _pos);
	void UpdatePan(const Vec2i& _pos);
	void EndPan(const Vec2i& _pos);

	const Vec2f& GetWorldOffset() const;
	const Vec2f& GetWorldScale() const;
	Vec2i ConvertWorldToScreen(const Vec2f& _objWorldPosition) const;
	Vec2f ConvertScreenToWorld(const Vec2i& _objScreenPosition) const;
	Vec2f ScaleToWorld(const Vec2f& _objScreenSize) const;
	Vec2i ScaleToScreen(const Vec2f& _objWorldSize) const;
	
	Vec2f CalculateCenteringOffset(const Vec2i& _screenSize, const Vec2i& _worldSize);

	bool IsPointVisible(const Vec2f& _point) const;
	bool IsBBVisible(const BoundingBox2D& _objBB) const;

	//////////////////////
	//					//
	//	   DRAWING		//
	//					//
	//////////////////////
	void DrawFillCircle(int _x, int _y, int _radius, Uint32 _color);
	void DrawLine(int _x0, int _y0, int _x1, int _y1, Uint8 thickness, Uint32 _color);
	void DrawBoundingBox2D(int _minX, int _minY, int _maxX, int _maxY, Uint32 _color);
};

#endif 
