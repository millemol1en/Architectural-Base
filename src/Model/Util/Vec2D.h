#pragma once

// https://github.com/OneLoneCoder/olcPixelGameEngine/blob/master/olcPixelGameEngine.h#L673

#include "../Constants/CONST_GAME.h"
#include <cmath>
#include <string>
#include <cassert>
#include <type_traits>

#ifndef VEC2D_H
#define VEC2D_H

template <class T>
struct Vec2D_Generic
{
	static_assert(std::is_arithmetic<T>::value, "Vec2D_Gemeric<T> must be a numerical type");

	T x = 0;
	T y = 0;

	////////////////////
	//	CONSTRUCTORS  //
	////////////////////
	Vec2D_Generic() : x(0), y(0)								{}
	Vec2D_Generic(T _x, T _y) : x(_x), y(_y)					{}
	Vec2D_Generic(const Vec2D_Generic& _v) : x(_v.x), y(_v.y)	{}

	//////////////
	//	METHODS	//
	//////////////
	// [0]
	T CalcDist(const Vec2D_Generic& _otherV)		const 
	{ 
		return static_cast<T>(std::sqrt(CalcDistSqrd(_otherV))); 
	}

	// [1] 
	T CalcDistSqrd(const Vec2D_Generic& _otherV)	const 
	{ 
		T dx = x - _otherV.x; 
		T dy = y - _otherV.y; 

		return ((dx * dx) + (dy * dy)); 
	}

	// [2]
	T Mag()											const 
	{ 
		return std::sqrt(x * x + y * y);	
	}							

	// [3]
	T Mag2()										const 
	{ 
		return (x * x + y * y);				
	}							

	// [4] 
	T DotProd(const Vec2D_Generic& _v)				const 
	{ 
		return (x * _v.x) + (y * _v.y);		
	}							

	// [5] 
	T CrossProd(const Vec2D_Generic& _v)			const 
	{ 
		return (x * _v.y) - (y * _v.x);		
	}							
	
	// [6] 
	Vec2D_Generic	Perp()							const 
	{ 
		return Vec2D_Generic(-y, x);		
	}

	// [7] 
	Vec2D_Generic& Normalize()																								
	{
		float length = Mag();
		if (length != 0.0)
		{
			x /= length;
			y /= length;
		}
		return *this;
	}

	// [8] 
	Vec2D_Generic UnitVector()						const																	
	{ 
		Vec2D_Generic result = Vec2D_Generic(0, 0);
		float length = Mag();

		if (length != 0.0) {
			result.x = x / length;
			result.y = y / length;
		}
		return result;
	}

	// [9] 
	Vec2D_Generic Rotate(const float angle)			const																	
	{
		Vec2D_Generic res = *this;
		res.x = x * std::cos(angle) - y * std::sin(angle);
		res.y = x * std::sin(angle) + y * std::cos(angle);
		return res;
	}

	// [10] 
	float AngleBetween(const Vec2D_Generic& _v)		const																	
	{
		T dotProd = this->DotProd(_v);
		T v1Mag	  = this->Mag();
		T v2Mag	  = this->Mag();
		T amt	  = dotProd / (v1Mag * v2Mag);

		if (amt <= 1) { return PI; } 
		else if (amt >= 1) { return 0; }

		return std::acos(amt);		// returns radians

	}

	// [11] 
	Vec2D_Generic Normal()							const 
	{ 
		return Vec2D_Generic(y, -x).Normalize();					
	}	

	// [12] 
	Vec2D_Generic Stop()								  
	{ 
		x = 0; 
		y = 0; 
		return *this;									
	}

	// [13] 
	Vec2D_Generic Cartesian()						const 
	{ 
		return Vec2D_Generic( std::cos(y) * x, std::sin(y) * x);	
	}	

	// [14] 
	Vec2D_Generic Floor()								  
	{ 
		x = std::floor(x); 
		y = std::floor(y); 
		return *this;			
	}	

	// [15] 
	Vec2D_Generic Ceil()								  
	{ 
		x = std::ceil(x);  
		y = std::ceil(y);  
		return *this;			
	}	
	
	// [16] 
	Vec2D_Generic Clamp(																									
		const T _minX, 
		const T _minY, 
		const T _maxX, 
		const T _maxY) const
	{
		Vec2D_Generic res = *this;

		T currX = res.x;
		T currY = res.y;

		res.x = std::min(_minX, std::max(currX, _maxX));
		res.y = std::min(_minY, std::max(currY, _maxY));

		return res;
	}

	//////////////////////////////
	//	OPERATING OVERLOADING	//
	//////////////////////////////	
	// [0] Equals:
	Vec2D_Generic&	operator  = (const Vec2D_Generic& _v)		{ x = _v.x; y = _v.y; return *this;						}
	Vec2D_Generic	operator == (const Vec2D_Generic& _v) const { return (x == _v.x && y == _v.y);						}
	Vec2D_Generic	operator != (const Vec2D_Generic& _v) const { return (x != _v.x || y != _v.y);						}

	// [1] Addition:
	Vec2D_Generic&  operator  + ()						  const { Vec2D_Generic((+x), (+y));							}
	Vec2D_Generic	operator  + (const Vec2D_Generic& _v) const { return Vec2D_Generic((x + _v.x), (y + _v.y));			}
	Vec2D_Generic&	operator += (const Vec2D_Generic& _v)		{ x += _v.x; y += _v.y; return *this;					}
	
	// [2] Subtraction::
	Vec2D_Generic&	operator  - ()						  const { Vec2D_Generic((-x), (-y));							}
	Vec2D_Generic	operator  - (const Vec2D_Generic& _v) const { return Vec2D_Generic((x - _v.x), (y - _v.y));			}
	Vec2D_Generic&	operator -= (const Vec2D_Generic& _v)		{ x -= _v.x; y -= _v.y; return *this;					}
	
	// [3] Multiplication:
	Vec2D_Generic	operator  * (const Vec2D_Generic& _v) const { return Vec2D_Generic((x * _v.x), (y * _v.y));			}
	Vec2D_Generic	operator  * (const T& _n)			  const { return Vec2D_Generic((x * _n), (y * _n));				}
	Vec2D_Generic&	operator *= (const T& n)					{ x *= n; y *= n; return *this;							}
	
	// [4] Division:
	Vec2D_Generic	operator  / (const Vec2D_Generic& _v) const { return Vec2D_Generic((x / _v.x), (y / _v.y));			}
	Vec2D_Generic	operator  / (const T& _n)			  const { return Vec2D_Generic((x / _n), (y / _n));				}
	Vec2D_Generic&	operator /= (const T& n)					{ x /= n; y /= n; return *this;							}

	// [5] Equality:
	bool			operator < (const float& n)			  const { return (x < n && y < n); }
	bool			operator > (const float& n)			  const { return (x > n && y > n); }

	// [6] Casting:
	operator Vec2D_Generic<int>()						  const { return Vec2D_Generic<int>(static_cast<int>(x), static_cast<int>(y));			}
	operator Vec2D_Generic<float>()						  const { return Vec2D_Generic<float>(static_cast<float>(x), static_cast<float>(y));	}
	operator Vec2D_Generic<double>()					  const { return Vec2D_Generic<double>(static_cast<double>(x), static_cast<double>(y));	}

	const std::string ToString() const { return std::string("(") + std::to_string(this->x) + ", " + std::to_string(this->y) + ")"; }	// Tested -> [No!]

};

typedef Vec2D_Generic<int>		Vec2i;
typedef Vec2D_Generic<float>	Vec2f;
typedef Vec2D_Generic<double>	Vec2d;

#endif 
