#pragma once
#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <SDL_Error.h>
#include <SDL_filesystem.h>
#include <iostream> 

#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif

struct FileHandler
{
public:

	static std::string m_basePath;

	static std::string GetAssetsPath(const std::string& _subDir = "");
	// static std::string GetFontsPath(const std::string& _fontPath = "");
};

#endif 
