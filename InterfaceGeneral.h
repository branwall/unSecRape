#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Pixel.h"
#include <iostream>


class InterfaceGeneral
{
protected: 
	Mouse mouse;
	PixelHandler pix;
	Keyboard key;

	int logTimeout;
	POINT MousePos;
	bool menu5Option = false;
	MSG msg; //for hotkey message recieving

public:
	InterfaceGeneral(); // constructor (sets hotkeys)

	~InterfaceGeneral(); // destructor (del hotkeys)

	//handles what hotkeys do
	virtual void HandleHotkeys();

	//verifies that hover text contains a specified color
	// !WARNING! hover text only works on items that have more than just a USE first option
	virtual bool VerifyHoverText(unsigned int color);

	//verifies the hover of something in the top-left corner is specified color
	virtual bool VerifyTopLeftText(unsigned int color);

	//checks the 3 static pixels are live
	virtual bool VerifyOSbuddy();

	//given an option choice(1,2,3...etc.), it will return the top left coordinate of that options hitbox
	//takes option choice on Zero Indexing (option 1 = optionChoice:0, option 2 = opChoice:1, etc.)
	virtual POINT GetMenuOptionCoords(int optionChoice);

	//takes option choice on Zero Indexing (option 1 = optionChoice:0, option 2 = opChoice:1, etc.)
	//!!WARNING!!! only handles 4 option items at bottom of the screen!
	void ChooseMenuOption(int optionChoice);

	//Chooses a menu option only if 'HOVER_xxx' exists on desired option
	bool ChooseMenuOptionColorCheck(int optionChoice, unsigned int color);

	//check if leveled up
	bool CheckLevelUp();

	//check if leveled up
	//modes ignore certain skill levels (like hp at mode 0)
	bool CheckLevelUp(int mode);

	//when all else fails. gtfo
	void Logout();

	//For when you just need to get out asap. keeps clicking until logged out
	void LogoutQuick();

	//checks for black background in health circle
	//amount should be some 1-100 value. 
	//returns true if health is there, false if not
	bool CheckHealthAmount(int amount);

	//sets mouse move speed 0.1-1.0 where lower is faster
	void SetMouseSpeed(float speed);

	//checks if loggedout or in process of logging in.
	//if false, it is logged out
	//if true, it is logged in
	bool CheckIfInGame();

	//after 6 hours it logs you out. this logs you back innnn
	bool HandleAutoLogOut();

};