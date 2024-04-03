#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Mouse.h"
#include "Keys.h"

struct Controller
{
public:
	bool m_isAppRunning;
	bool m_debugMode;
	bool m_devSnapShot;
	// With this, and any other variables between "Application" and "Controller" which have a direct correlation 
	// to each other, we have 2 ways of dealing with this:
	//		02. Have Application.h constantly check for changes of its own correlated variables within Controller.h


public:
	// Local Variables:
	Mouse m_mouse;
	Keys m_key;


	// Foreign Variables:
	World* ptr_worldRef;
	TransformedView* ptr_tvRef;

	Controller() = default;
	Controller(World* _worldPtr, TransformedView* _tvPtr);
	~Controller() = default;

	// Ultimately, remove this and re-disperse it into the Keys and Mouse

	void HandleInput();
	void CloseApp();			// "Close"	  :: Single run
	void ToggleDebugMode();		// "Toggle"   :: Switch
	void ActivateDevSnapshot();	// "Activate" :: Single run

	bool GetIsRunning() const;
	bool GetIsDebugModeActive() const;

	SDS_TYPE GetSDSType() const;
};

#endif