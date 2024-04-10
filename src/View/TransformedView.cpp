#include "TransformedView.h"


TransformedView::TransformedView(const Vec2i& _screenArea, const Vec2i& _worldArea, const Vec2f& _pixelScale)
{
	SetViewArea(_screenArea);
	SetWorldScale(_pixelScale);
	SetWorldOffset(CalculateCenteringOffset(_screenArea, _worldArea));
	m_pixelScale = _pixelScale;
	m_RecipPixel.x = 1.0f / m_pixelScale.x;
	m_RecipPixel.y = 1.0f / m_pixelScale.y;
}

// This formula will always assume that both the screen and the world has their starting position to be at
// the TOP LEFT of the screen. If this is NOT the case, it must be changed such that the starting position 
// of the world is subtracted from the "_worldSize".
Vec2f TransformedView::CalculateCenteringOffset(const Vec2i& _screenSize, const Vec2i& _worldSize) {
	float offsetX = -(_screenSize.x - (_worldSize.x)) / 2.0f;
	float offsetY = -(_screenSize.y - (_worldSize.y)) / 2.0f;
	return { offsetX, offsetY };
}

void TransformedView::SetWorldOffset(const Vec2f& _offset)
{
	m_worldOffset = _offset;
}

void TransformedView::MoveWorldOffset(const Vec2f& _deltaOffset)
{
	m_worldOffset += _deltaOffset;
}

void TransformedView::SetWorldScale(const Vec2f& _scale)
{
	m_worldScale = _scale;
}

void TransformedView::SetWorldArea(const Vec2i& _worldArea)
{
	m_worldArea = _worldArea;
}

void TransformedView::SetViewArea(const Vec2i& _screenArea)
{
	m_viewArea = _screenArea;
}

Vec2f TransformedView::GetWorldTopLeft() const
{
	return ConvertScreenToWorld({ 0, 0 });
}

Vec2f TransformedView::GetWorldBottomRight() const
{
	return ConvertScreenToWorld(m_viewArea); // Graphics::Height() && Graphics::Width()
}

Vec2f TransformedView::GetWorldVisibleArea() const
{
	return GetWorldBottomRight() - GetWorldTopLeft();
}

void TransformedView::ZoomAtScreenPos(const float _deltaZoom, const Vec2i& _pos)
{
	std::cout << "Zoom '_deltaZoom' value: " << _deltaZoom << " and position: (" << _pos.x << ", " << _pos.y << "\n";

	Vec2f offsetBeforeZoom = ConvertScreenToWorld(_pos);
	m_worldScale *= _deltaZoom;
	Vec2f offsetAfterZoom = ConvertScreenToWorld(_pos);
	m_worldOffset += offsetBeforeZoom - offsetAfterZoom;
}

void TransformedView::SetZoom(const float _zoom, const Vec2i& _pos)
{
	Vec2f offsetBeforeZoom = ConvertScreenToWorld(_pos);
	m_worldScale = { _zoom, _zoom };
	Vec2f offsetAfterZoom = ConvertScreenToWorld(_pos);
	m_worldOffset += offsetBeforeZoom - offsetAfterZoom;
}

void TransformedView::StartPan(const Vec2i& _pos)
{
	m_isPanning = true;
	m_startPan = Vec2f(_pos.x, _pos.y);
}

void TransformedView::UpdatePan(const Vec2i& _pos)
{
	if (m_isPanning)
	{
		m_worldOffset -= (Vec2f(_pos.x, _pos.y) - m_startPan) / m_worldScale;
		m_startPan = Vec2f(_pos.x, _pos.y);
	}
}

void TransformedView::EndPan(const Vec2i& _pos)
{
	UpdatePan(_pos);
	m_isPanning = false;
}

const Vec2f& TransformedView::GetWorldOffset() const
{
	return m_worldOffset;
}

const Vec2f& TransformedView::GetWorldScale() const
{
	return m_worldScale;
}


///////////////////////////////
// WORLD-&-SCREEN CONVERSION //
///////////////////////////////
Vec2i TransformedView::ConvertWorldToScreen(const Vec2f& _objWorldPosition) const
{
	Vec2f convertedPos = ((_objWorldPosition - m_worldOffset) * m_worldScale);
	return convertedPos.Floor();
}

Vec2f TransformedView::ConvertScreenToWorld(const Vec2i& _objScreenPosition) const
{
	Vec2f objScreenPosFloat;
	objScreenPosFloat.x = _objScreenPosition.x;

	return (Vec2f(_objScreenPosition) / m_worldScale) + m_worldOffset;
}


/////////////
// SCALING //
/////////////
Vec2f TransformedView::ScaleToWorld(const Vec2f& _objScreenSize) const
{
	return (_objScreenSize / m_worldScale) + m_worldOffset;
}

Vec2i TransformedView::ScaleToScreen(const Vec2f& _objWorldSize) const
{
	Vec2f scaledObj = _objWorldSize * m_worldScale;
	return scaledObj.Floor();
}

bool TransformedView::IsPointVisible(const Vec2f& _point) const
{
	Vec2i pointScreenPos = ConvertWorldToScreen(_point);
	return (pointScreenPos.x >= 0 && pointScreenPos.x < m_viewArea.x && pointScreenPos.y >= 0 && pointScreenPos.y < m_viewArea.y);
}


/*
bool BoundingBox2D::OverlapsOrContains(const BoundingBox2D& other) const
{
	return !(
		m_minX >= other.m_maxX ||
		m_maxX <= other.m_minX ||
		m_minY >= other.m_maxY ||
		m_maxY <= other.m_minY
		);
}
*/

bool TransformedView::IsBBVisible(const BoundingBox2D& _objBB) const
{
	Vec2i objTL	= ConvertWorldToScreen({ _objBB.m_minX, _objBB.m_minY });
	Vec2i objBR = ConvertWorldToScreen({ _objBB.m_maxX, _objBB.m_maxY });

	Vec2i size = { static_cast<int>(_objBB.m_maxX * m_worldScale.x), static_cast<int>(_objBB.m_maxY * m_worldScale.y) };

	std::cout << "Object Bounding Box: " <<
		"\n   -> Top Left   :: (" << objTL.x << ", " << objTL.y << ")" <<
		"\n   -> Btm Right  :: (" << objBR.x << ", " << objBR.y << ")" <<
		"\n   -> Size Value :: (" << size.x << ", " << size.y << ")\n";

	return (
		objTL.x <= m_viewArea.x &&
		objBR.x >= 0 &&
		objTL.y <= m_viewArea.y &&
		objBR.y >= 0
		);
}

void TransformedView::DrawFillCircle(const Vec2f& _pos, const float& _radius, Uint32 _color)
{
	Vec2i circleScreenPos = ConvertWorldToScreen(_pos);

	Graphics::DrawFillCircle(circleScreenPos.x, circleScreenPos.y, int32_t(_radius * m_worldScale.x), _color);
}

void TransformedView::DrawLine(const Vec2f& _p0, const Vec2f& _p1, Uint8 _thickness, Uint32 _color)
{
	Vec2i p1Screen = ConvertWorldToScreen(_p0);
	Vec2i p2Screen = ConvertWorldToScreen(_p1);

	// [TODO] :: Handle thickness
	Graphics::DrawLine(p1Screen.x, p1Screen.y, p2Screen.x, p2Screen.y, _thickness, _color);
}

void TransformedView::DrawBoundingBox2D(float _minX, float _minY, float _maxX, float _maxY, Uint32 _color)
{
	Vec2i minScreen = ConvertWorldToScreen({ _minX, _minY });
	Vec2i maxScreen = ConvertWorldToScreen({ _maxX, _maxY });

	// [TODO] :: Handle thickness
	Graphics::DrawBoundingBox2D(minScreen.x, minScreen.y, maxScreen.x, maxScreen.y, 1, _color);
}
