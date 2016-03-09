#include <iostream>
#include "InterfaceInventory.h"
#include "BotThievingPickpocket.h"
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


	InterfaceInventory inv;
	PixelHandler pix;
	//pix.DEBUG();
	InterfaceStats stat;
	BotThievingPickpocket me;
	me.run();

	return 0;
}



/*


*/