#pragma once
#include "InterfaceInventory.h"

class BotRangeOgre : public InterfaceInventory
{
public:
	void run()
	{
		findOgre();
	}

	bool findOgre()
	{
		unsigned int OgreHead = 0xcbb89a00; //shiny ogre head color?
		unsigned int OgreSkirt = 0x3e371600; //shiny ogre head color?

		POINT Ogre;
		Ogre = pix.SearchPixelAreaForPoint(OgreSkirt, 140 + SCREEN, 100, 1440 + SCREEN, 460,10);
		if (Ogre.x == -1) //no ogre found
			return false;

		mouse.MouseMove(Ogre);
		if (VerifyTopLeftText(HOVER_NPC) || VerifyHoverText(HOVER_NPC))//confirm mouse on ogre
			mouse.LeftClick();

	}
};