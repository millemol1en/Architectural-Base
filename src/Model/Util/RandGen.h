#pragma once
#ifndef RAND_GEN_H
#define RAND_GEN_H

#include <cstdint>
#include <cstdlib>
#include <SDL.h>
#include "../Util/Vec2D.h"

struct RandGen
{ 
    static const int RandValInRange(const int _min, const int _max) 
    {
	    return std::rand() % (_max + 1 - _min) + _min;
    }

    static const Vec2f RandomVelocityGenerator(const int _min, const int _max)
    {
        float randVelX = std::rand() % (_max + 1 - _min) + _min;
        float randVelY = std::rand() % (_max + 1 - _min) + _min;

        return { randVelX, randVelY };
    }
    
    static const Vec2f RandomPositionGenerator(const int width, const int height) 
    {
        float randPosX = std::rand() % width;
        float randPosY = std::rand() % height;

        return { randPosX, randPosY };
    }

    static const int RandomRadiusGenerator(const int& maxRadius) 
    {
        int randRadius = rand() % maxRadius;
        randRadius = (randRadius < 4) ? 4 : randRadius;
        return randRadius;
    }

    static Uint32 RandomColorGenerator()
    {
        uint8_t r = std::rand() % 255;
        uint8_t g = std::rand() % 255;
        uint8_t b = std::rand() % 255;
        uint8_t a = std::rand() % 255;

        // Order is :: Alpha -> Red -> Green -> Blue
        Uint32 color = (a << 24) | (r << 16) | (g << 8) | b;

        return color;
    }
};

#endif // !RAND_GEN_H
