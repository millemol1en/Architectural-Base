#pragma once
#ifndef KEYS_H
#define KEYS_H

#include "../Model/World/World.h"
#include "../View/TransformedView.h"
#include "../Model/Constants/CONST_GAME.h"


struct Keys
{

private:
	bool m_isAppRunning;	// Is app running needs to be dependent on SDL and the success of SDL_Init...
	bool m_debugMode;
	bool m_devSnapShot;

	TransformedView* ptr_tvRef;
	World* ptr_worldRef;

public:

	Keys()  = default;
	~Keys() = default;

	void Keys_HandleKeyDown(const SDL_Event& event);
	void Keys_HandleKeyUp(const SDL_Event& event);


	void Keys_SetTVPtr(TransformedView* _tvPtr);
	void Keys_SetWorldPtr(World* _worldPtr);


	void Keys_CloseApp();			// "Close"	  :: Single run
	void Keys_ToggleDebugMode();		// "Toggle"   :: Switch
	void Keys_ActivateDevSnapshot();	// "Activate" :: Single run

	bool Keys_GetIsRunning() const;
	bool Keys_GetIsDebugModeActive() const;
	bool Keys_GetIsDevSnapshotActive() const;

	SDS_TYPE Keys_GetSDSType() const;
};

#endif