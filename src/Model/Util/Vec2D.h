#pragma once

// https://github.com/OneLoneCoder/Javidx9/blob/master/PixelGameEngine/BiggerProjects/SavingSedit/olcPixelGameEngine.h

#ifndef VEC2D_H
#define VEC2D_H

template <class T>
struct Vec2D_Generic
{
	T x = 0;
	T y = 0;

	inline Vec2D_Generic() : x(0), y(0) {}
	inline Vec2D_Generic(T _x, T _y) : x(_x), y(_y) {}
	inline Vec2D_Generic(const Vec2D_Generic& v) : x(v.x), y(v.y)	{}
	inline T Mag() const											{ return sqrt(x * x + y * y); }
	inline Vec2D_Generic Norm() const { return Vec2D_Generic(this->y, this->-x).Normalize(); }
	inline Vec2D_Generic Perp() const {}
	inline Vec2D_Generic Rotate() const {}
	inline Vec2D_Generic DotProd(const Vec2D_Generic& v)   const { return (this->x * v.x) + (this->y * v.y); }
	inline Vec2D_Generic CrossProd(const Vec2D_Generic& v) const { return (this->x * v.y) - (this->y * v.x); }
	inline Vec2D_Generic Normalize() const 
	{ 
		float length = Mag();
		if (length != 0.0)
		{
			x /= length; 
			y /= length; 
		}
		return *this;
	}
	inline Vec2D_Generic UnitVector() const 
	{ 
		Vec2D_Generic result = Vec2D_Generic(0, 0);
		float length = Mag();

		if (length != 0.0) {
			result.x = x / length;
			result.y = y / length;


		}
		return result;
	}
	

	inline Vec2D_Generic operator - ()						  const { return Vec2D_Generic((this->x * -1), (this->y * -1)) }
	inline Vec2D_Generic operator = (const Vec2D_Generic& v)  const { x = v.x; y = v.y; return *this; }
	inline Vec2D_Generic operator == (const Vec2D_Generic& v) const { return (this->x == v.x && this->y == v.y); }
	inline Vec2D_Generic operator != (const Vec2D_Generic& v) const { return !(*this == v);  }

	inline Vec2D_Generic operator + (const Vec2D_Generic& v)  const { return Vec2D_Generic((this->x + v.x), (this->y + v.y)); }
	inline Vec2D_Generic operator - (const Vec2D_Generic& v)  const { return Vec2D_Generic((this->x - v.x), (this->y - v.y)); }
	inline Vec2D_Generic operator += (const Vec2D_Generic& v) const { this->x += v.x; this->y += v.y; return *this; }
	inline Vec2D_Generic operator -= (const Vec2D_Generic& v) const { this->x -= v.x; this->y -= v.y; return *this; }
	
	inline Vec2D_Generic operator * (const Vec2D_Generic& v)  const { return Vec2D_Generic((this->x / v.x), (this->y / v.y)); }
	inline Vec2D_Generic operator * (const T& n)			  const { return Vec2D_Generic((this->x / x), (this->y / y)); }
	inline Vec2D_Generic operator / (const Vec2D_Generic& v)  const { return Vec2D_Generic((this->x / v.x), (this->y / v.y)); }
	inline Vec2D_Generic operator / (const T& n)			  const { return Vec2D_Generic((this->x / x), (this->y / y)); }

	inline Vec2D_Generic operator *= (const T& n) const { x *= n; y *= n; return *this; }
	inline Vec2D_Generic operator /= (const T& n) const { x /= n; y /= n; return *this; }

	inline Vec2D_Generic operator < (const Vec2D_Generic& v) const {
		if (this->x < n && this->y < n) return true;
		else return false;
	}
	inline Vec2D_Generic operator > (const Vec2D_Generic& v) {
		if (this->x > n && this->y > n) return true;
		else return false;
	}

};

#endif 
