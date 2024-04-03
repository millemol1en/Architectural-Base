#include "./Font.h"

TTF_Font* Fonts::m_font = NULL;
std::string Fonts::m_fontURI = "";

bool Fonts::OpenFonts()
{
	// 01. Perform core initialization:
	if (TTF_Init() == -1)
	{
		std::cerr << "[Method --- OpenFonts()] Error calling TTF_Init(): " << TTF_GetError() << std::endl;
		return false;
	}

	// 02. Retrieve the path to the fonts folder:
	m_fontURI = FileHandler::GetAssetsPath("fonts\\RobotoThin.ttf");

	m_font = TTF_OpenFont(m_fontURI.c_str(), 200);
	if (m_font == nullptr)
	{
		// [TODO] :: Add this where needed
		ErrorHandler::LogSDLError(__func__, std::cerr, "TTF_OpenFont() returned a nullptr");
		//std::cerr << "[Method --- OpenFonts()] Error calling TTF_OpenFont(): " << TTF_GetError() << std::endl;
		return false;
	}

	return true;
}

bool Fonts::RenderFont(std::string _text, const Vec2i _pos, const Vec2i _dimensions, SDL_Color _fontColor, int _fontSize, SDL_Renderer* _sdlRenderer)
{
	SDL_Rect fontPos{};
	fontPos.x = _pos.x;
	fontPos.y = _pos.y;
	fontPos.w = _dimensions.x;
	fontPos.h = _dimensions.y;

	if (m_font == nullptr)
	{
		std::cerr << "[Method --- RenderFont()] TTF_Font* was a nullptr" << std::endl;
		return false;
	}

	SDL_Surface* surfaceText = TTF_RenderText_Solid(m_font, _text.c_str(), _fontColor);
	if (!surfaceText)
	{
		std::cerr << "[Method --- RenderFont()] SDL_Surface* was a nullptr" << std::endl;
		return false;
	}

	SDL_Texture* textureText = SDL_CreateTextureFromSurface(_sdlRenderer, surfaceText);
	if (!textureText)
	{
		std::cerr << "[Method --- RenderFont()] SDL_Texture* was a nullptr" << std::endl;
		return false;
	}

	SDL_FreeSurface(surfaceText);

	SDL_RenderCopy(_sdlRenderer, textureText, NULL, &fontPos);

	SDL_DestroyTexture(textureText);


	return true;
}

void Fonts::CloseFonts()
{
	TTF_CloseFont(m_font);
	TTF_Quit();
}

