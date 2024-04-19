#pragma once
#ifndef CONST_GAME_H
#define CONST_GAME_H

constexpr int	FPS					= 60;
constexpr int	MILLISECS_PER_FRAME = 1000 / FPS;
constexpr int	PIXELS_PER_METER	= 50;
constexpr float DRAG_CONSTANT		= 0.03f;
constexpr float ZOOMOUT_THRESHOLD	= 0.5f;
constexpr float ZOOMIN_THRESHOLD	= 9.0f;
constexpr float PI					= 3.141592635f;
constexpr int	MAX_ENTITY_COUNT	= 1000000;

#endif 
