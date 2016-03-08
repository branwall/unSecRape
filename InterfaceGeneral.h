#pragma once
#include "Mouse.h"
#include "Pixel.h"


class InterfaceGeneral
{
protected: 
	Mouse mouse;
	PixelHandler pix;
	POINT MousePos;
	bool menu5Option = false;

public:
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

	//when all else fails. gtfo
	void Logout();
};