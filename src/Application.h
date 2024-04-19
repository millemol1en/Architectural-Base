#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include "./View/Graphics.h"
#include "./Controller/Controller.h"
#include "./Model/World/World.h"
#include "./View/TransformedView.h"
#include "./Model/Constants/CONST_GAME.h"
#include "./Model/Constants/CONST_SDS_ENTITY_TYPE.h"
#include "./Application/FileHandler.h"


#include <vector>
#include <iostream>
#include <chrono>

class Application {


private:
    static std::string m_baseRes;
    bool m_devSnapShot  = false;     
    bool m_debugMode    = false;
    bool m_isRunning    = false;
    int idCounter       = 0;

    Controller* m_controller = nullptr;
    TransformedView* m_transformedView = nullptr;
    World* m_world = nullptr;
    // TextHandler* m_textHandler;


    /*std::list<Text*>::iterator elapsedTime_t;
    std::list<Text*>::iterator numCircles_t;
    std::list<Text*>::iterator clickedCell_t;*/

public:
    Application()  = default;
    ~Application() = default;
    void Setup();
    void Input();
    void Update();
    void Render();
    void Destroy();
    bool IsRunning();
    bool IsDebugModeActive();
};

#endif 