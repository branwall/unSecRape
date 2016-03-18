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
		if (inv.CheckSpellRunes(MAGIC_HEAT, 4, 3))
			printf("Active SUPERHEAT!\n");
		else
			printf("nuttin\n");
		std::cin.ignore();
		}
	}

};