#include "Vec2.h"
#include <math.h>
#include <iostream>

//////////////////////
//					//
//	2D Float Vector	//
//					//
//////////////////////
Vec2f::Vec2f()					: x(0.0f), y(0.0f)	{}
Vec2f::Vec2f(float x, float y)	: x(x), y(y)		{}
Vec2f::Vec2f(Vec2i v)			: x(v.x), y(v.y)	{}


void Vec2f::Add(const Vec2f& v)
{
	x += v.x;
	y += v.y;
}

void Vec2f::Subtract(const Vec2f& v)
{
	x -= v.x;
	y -= v.y;
}

void Vec2f::Scale(const float n)
{
	x *= n;
	y *= n;
}

void Vec2f::Stop()
{
	x = 0.0f;
	y = 0.0f;
}

Vec2f Vec2f::Rotate(const float angle) const
{
	Vec2f res = *this;
	res.x = x * cos(angle) - y * sin(angle);
	res.y = x * sin(angle) + y * cos(angle);
	return res;
}

Vec2i Vec2f::Floor() const
{
	return { std::floor(x), std::floor(y) };
}

float Vec2f::Magnitude() const
{
	return sqrtf(x * x + y * y);
}

Vec2f& Vec2f::Normalize()
{
	float length = Magnitude();
	if (length != 0.0) {
		x /= length;
		y /= length;
	}
	return *this;
}

Vec2f Vec2f::UnitVector() const
{
	Vec2f result = Vec2f(0, 0);
	float length = Magnitude();

	if (length != 0.0) {
		result.x = x / length;
		result.y = y / length;


	}
	return result;
}

Vec2f Vec2f::Normal() const
{
	return Vec2f(y, -x).Normalize();
}

float Vec2f::Dot(const Vec2f& v) const
{
	return (x * v.x) + (y * v.y);
}

float Vec2f::Cross(const Vec2f& v) const
{
	return (x * v.y) - (y * v.x);
}

Vec2f& Vec2f::operator = (const Vec2f& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

bool Vec2f::operator == (const Vec2f& v) const
{
	return x == v.x && y == v.y;
}

bool Vec2f::operator != (const Vec2f& v) const
{
	return !(*this == v);
}

bool Vec2f::operator < (const float& n) const
{
	if (this->x < n && this->y < n) return true;
	else return false;
}

bool Vec2f::operator > (const float& n) const
{
	if (this->x > n && this->y > n) return true;
	else return false;
}

Vec2f Vec2f::operator + (const Vec2f& v) const
{
	Vec2f result;
	result.x = x + v.x;
	result.y = y + v.y;
	return result;
}

Vec2f Vec2f::operator - (const Vec2f& v) const
{
	Vec2f result;
	result.x = x - v.x;
	result.y = y - v.y;
	return result;
}

Vec2f Vec2f::operator * (const float n) const
{
	Vec2f result;
	result.x = x * n;
	result.y = y * n;
	return result;
}

Vec2f Vec2f::operator * (const Vec2f& v) const
{
	Vec2f result;
	result.x = x * v.x;
	result.y = y * v.y;
	return result;
}

Vec2f Vec2f::operator / (const float n) const
{
	Vec2f result;
	result.x = x / n;
	result.y = y / n;
	return result;
}

Vec2f Vec2f::operator / (const Vec2f& v) const
{
	Vec2f result;
	result.x = x / v.x;
	result.y = y / v.y;
	return result;
}

Vec2f& Vec2f::operator += (const Vec2f& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vec2f& Vec2f::operator -= (const Vec2f& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vec2f& Vec2f::operator *= (const float n)
{
	x *= n;
	y *= n;
	return *this;
}

Vec2f& Vec2f::operator /= (const float n)
{
	x /= n;
	y /= n;
	return *this;
}

Vec2f Vec2f::operator - ()
{
	Vec2f result;
	result.x = x * -1;
	result.y = y * -1;
	return result;
}


//
// 
// VEC2i INTEGER
// 
//
Vec2i::Vec2i()				     : x(0), y(0)		{}
Vec2i::Vec2i(int _x, int _y)	 : x(_x), y(_y)		{}
Vec2i::Vec2i(float _x, float _y) : x(_x), y(_y)	    {}

bool Vec2i::operator == (const Vec2i& v) const
{
	return x == v.x && y == v.y;
}

bool Vec2i::operator!=(const Vec2i& v) const
{
	return x != v.x || y != v.y;
}

Vec2i Vec2i::operator+(const Vec2i& v) const
{
	Vec2i result;
	result.x = x + v.x;
	result.y = y + v.y;
	return result;
}

Vec2i Vec2i::operator-(const Vec2i& v) const
{
	Vec2i result;
	result.x = x - v.x;
	result.y = y - v.y;
	return result;
}

