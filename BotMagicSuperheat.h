#pragma once
#include "InterfaceInventory.h"

class BotMagicSuperheat
{
private:
	InterfaceInventory inv;
	POINT Superheat; // x,y coords in spell book

public:
	BotMagicSuperheat()
	{
		Superheat.x = 4;
		Superheat.y = 3;
	}

	void run()
	{
		while (1)
		{
			if (inv.PrepareSpell(TELEBLOCK))
			{
				printf("SUCCESS\n");
			}
			else
				printf("nothing to do\n");
			std::cin.ignore(); //pause loop
		}
	}

};