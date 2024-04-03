#pragma once

#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <ostream>
#include <SDL_error.h>

enum ERROR_TYPE
{
	NULL_PTR,
	ARITHMETIC,
	OUT_OF_BOUNDS,
	NONE_SPECIFIC,
};

struct ErrorHandler
{
	// [TODO] :: Create a generalized try-catch to return a Discriminated Union to be used
	//			 when dealing with risky error potential methods.
	static void LogSDLError(std::string __funcName__, std::ostream& _os, const std::string& _msg)
	{
		_os << "[" << __funcName__ << "] - " << _msg << " error: " << SDL_GetError() << "\n";
	}

	static void LogError(std::string __funcName__, std::ostream& _os, ERROR_TYPE _errType)
	{
		std::string errMsg;

		switch (_errType)
		{
			case NULL_PTR:
				errMsg = " *variable name* was a NULLPTR";
				break;

			case ARITHMETIC:
				errMsg = " attempt to divide *variable name* by zero";
				break;

			case OUT_OF_BOUNDS:
				errMsg = " index was out of bounds for *variable name*";
				break;

			default:
				errMsg = "";
				break;
		}

		_os << "[" << __funcName__ << "] - " << errMsg << "\n";

	}
};

#endif 
