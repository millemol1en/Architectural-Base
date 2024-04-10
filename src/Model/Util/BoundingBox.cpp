#include "BoundingBox.h"
#include <iostream>


// [0] Bounding Box created from Top-Left and Bottom-Right integer vectors:
BoundingBox2D::BoundingBox2D(Vec2i _topLeft, Vec2i _bottomRight) : m_isBBColliding(false), m_isOnlyOverlapping(false), m_isOnlyContained(false)
{
    m_minX = _topLeft.x;
    m_minY = _topLeft.y;
    m_maxX = _bottomRight.x;
    m_maxY = _bottomRight.y;
}

// [1] Bounding Box created from Top-Left and Bottom-Right float vectors
BoundingBox2D::BoundingBox2D(Vec2f _topLeft, Vec2f _bottomRight) : m_isBBColliding(false), m_isOnlyOverlapping(false), m_isOnlyContained(false)
{
    m_minX = _topLeft.x;
    m_minY = _topLeft.y;
    m_maxX = _bottomRight.x;
    m_maxY = _bottomRight.y;
}

// [2] Bounding Box specific for Circles:
BoundingBox2D::BoundingBox2D(int _radius, float _x, float _y) : m_isBBColliding(false), m_isOnlyOverlapping(false), m_isOnlyContained(false)
{
    InitBoundingBox2D(_radius, _x, _y);
}

// [3] Bounding Box for Rectangles:
BoundingBox2D::BoundingBox2D(float _startX, float _startY, float _width, float _height) : m_isBBColliding(false), m_isOnlyOverlapping(false), m_isOnlyContained(false)
{
    InitBoundingBox2D(_startX, _startY, _width, _height);
}

// [4] Check to see if 2 bounding boxes ONLY overlap and NOT contain one another - [TESTED]
bool BoundingBox2D::OnlyOverlaps(const BoundingBox2D& other) const
{
    return (
        (m_minX < other.m_maxX && m_maxX > other.m_minX) &&
        (m_minY < other.m_maxY && m_maxY > other.m_minY) &&
        !this->OnlyContains(other) && !other.OnlyContains(*this)
        );
}

// Check to see if 2 bounding boxes contains completely another one and doesn't overlap - [TESTED]
bool BoundingBox2D::OnlyContains(const BoundingBox2D& other) const
{
    return (
        m_minX <= other.m_minX &&
        m_minY <= other.m_minY &&
        m_maxX >= other.m_maxX &&
        m_maxY >= other.m_maxY
        );
}

// Check to see if 2 bounding boxes touch, both overlapping and or containment - [TESTED]
bool BoundingBox2D::OverlapsOrContains(const BoundingBox2D& other) const
{
    return !(
        m_minX >= other.m_maxX ||
        m_maxX <= other.m_minX ||
        m_minY >= other.m_maxY ||
        m_maxY <= other.m_minY
        );
}

void BoundingBox2D::UpdateBoundingBox2D(float offsetX, float offsetY)
{
    m_minX += offsetX; m_maxX += offsetX;
    m_minY += offsetY; m_maxY += offsetY;
}

// [TODO] Clean this up --- currently it has TOO many methods
void BoundingBox2D::InitBoundingBox2D(int radius, float _x, float _y)
{
    m_minX = _x - radius;
    m_minY = _y - radius;
    m_maxX = _x + radius;
    m_maxY = _y + radius;
}

void BoundingBox2D::InitBoundingBox2D(float _startX, float _startY, float _width, float _height)
{
    m_minX = _startX;
    m_minY = _startY;
    m_maxX = _startX + _width;
    m_maxY = _startY + _height;
}
