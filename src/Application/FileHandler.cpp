#include "FileHandler.h"

std::string FileHandler::m_basePath = "";


std::string FileHandler::GetAssetsPath(const std::string& _subDir)
{
    if (m_basePath.empty())
    {
        char* basePath = SDL_GetBasePath();
        if (basePath) {
            m_basePath = basePath;
            SDL_free(basePath);
        }
        else {
            std::cerr << "[Method --- GetResourcePath] Error getting resource path: " << SDL_GetError() << std::endl;
            return "";
        }

        size_t pos = m_basePath.rfind("Debug");
        m_basePath = m_basePath.substr(0, pos) + "assets" + PATH_SEP;
    }


    // [TODO] Make it more flexible
    //        Originally, it was like this "return (_subDir.empty()) ? m_basePath : m_basePath + _subDir + PATH_SEP;"
    //        But the "PATH_SEP" had to be removed as we are dealing with an individual file.
    //        So add a bool variable called "isFile" to determine whether or not a PATH_SEP should be added at the end.

    return (_subDir.empty()) ? m_basePath : m_basePath + _subDir;
}
