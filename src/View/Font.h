#pragma once
#ifndef FONT_H
#define FONT_H

#include <SDL_ttf.h>
#include <iostream>
#include "../Model/Util/Vec2D.h"
#include "../Application/FileHandler.h"
#include "../Application/ErrorHandler.h"


struct Fonts
{
	static TTF_Font* m_font;
	static std::string m_fontURI;

	static bool OpenFonts();
	static void CloseFonts();

	static bool RenderFont(std::string _text, const Vec2i _pos, const Vec2i _dimensions, SDL_Color _fontColor, int _fontSize, SDL_Renderer* _sdlRenderer);
};


#endif