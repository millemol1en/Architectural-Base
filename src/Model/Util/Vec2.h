#pragma once
#pragma once
#ifndef VEC2_H
#define VEC2_H

struct Vec2i
{
    int x;
    int y;

    Vec2i();
    Vec2i(int x, int y);
    Vec2i(float x, float y);
    ~Vec2i() = default;

    bool operator == (const Vec2i& v) const;
    bool operator != (const Vec2i& v) const;
    Vec2i operator + (const Vec2i& v) const;
    Vec2i operator - (const Vec2i& v) const;

};

struct Vec2f
{
    float x;
    float y;

    Vec2f();
    Vec2f(float x, float y);
    Vec2f(Vec2i v);
    ~Vec2f() = default;

    void Add(const Vec2f& v);
    void Subtract(const Vec2f& v);
    void Scale(const float n);
    void Stop();
    Vec2f Rotate(const float angle) const;
    Vec2i Floor() const;

    Vec2f& Normalize();
    Vec2f UnitVector() const;
    Vec2f Normal() const;

    float Magnitude() const;
    float Dot(const Vec2f& v) const;
    float Cross(const Vec2f& v) const;

    Vec2f& operator = (const Vec2f& v);
    bool operator == (const Vec2f& v) const;
    bool operator != (const Vec2f& v) const;
    bool operator < (const float& n) const;
    bool operator > (const float& n) const;

    Vec2f operator + (const Vec2f& v) const;
    Vec2f operator - (const Vec2f& v) const;
    Vec2f operator * (const float n) const;
    Vec2f operator * (const Vec2f& v) const;
    Vec2f operator / (const float n) const;
    Vec2f operator / (const Vec2f& v) const;
    Vec2f operator - ();

    Vec2f& operator += (const Vec2f& v);
    Vec2f& operator -= (const Vec2f& v);
    Vec2f& operator *= (const float n);
    Vec2f& operator /= (const float n);
};

#endif