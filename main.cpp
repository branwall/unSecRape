#include <iostream>
#include "InterfaceInventory.h"
#include "BotThievingPickpocket.h"
#include "BotThievingRogueChest.h"
#include "BotMagicCurse.h"
#include "BotMagicSuperheat.h"
#include "BotMeleeCow.h"
#include "InterfaceStats.h"
#include <stdio.h>

int main()
{
	/*
	//arguments Window, HK-ID, SPECIAL-KEYS, HOTKEY
	RegisterHotKey(NULL, 1, 0, ESCAPE); //Pause the program, (needs enter to resume)
	RegisterHotKey(NULL, 2, MOD_SHIFT, ESCAPE);

	MSG msg;
	GetMessage(&msg, NULL, 0, 0);

	//GetMessage(&msg, NULL, 0, 0);
	if (msg.message == WM_HOTKEY)
	{
		std::cout << msg.lParam << " - " << msg.wParam << std::endl;
		GetMessage(&msg, NULL, 0, 0);
	} */

	unsigned int ThievingEXP = 0x00000100;



	InterfaceInventory inv;
	PixelHandler pix;
	Keyboard key;
	//pix.DEBUG();
	InterfaceStats stat;

	//BotMagicCurse me;
	BotMagicSuperheat me;
	//BotThievingPickpocket me;
	//BotThievingRogueChest me;
	//BotMeleeCow me;

	//me.run(me.Paladin1, me.Paladin1, me.cake);
	//me.run(me.AdroKnight1,me.AdroKnight2,me.PineapplePizza);
	me.run();
	std::cin.ignore();
	return 0;
}



/*


*/