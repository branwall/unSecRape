#include <iostream>
#include "InterfaceInventory.h"
#include "BotRangeOgre.h"
#include "InterfaceStats.h"
#include <stdio.h>

int main()
{
	PixelHandler pix;
	Mouse mouse;
	InterfaceInventory inv;
	InterfaceStats stat;
	bool combat = true;
	while (combat)
	{
		//pix.DEBUG();
		//BotRangeOgre me;
		//me.run();
		//inv.ChooseMenuOption(1);

		combat = stat.Fight(0xcbb89a00, 140 + SCREEN, 100, 1440 + SCREEN, 460);
		if (!combat)
		{
			stat.Logout();
			std::cin.ignore();
		}
		//else
		//	printf("nope\n");
		//inv.VerifyActiveInv();
		//pix.SearchPixelArea(0xffdf6f00, 1553, 25, 1553, 25,10);
		//std::cin.ignore();
	}
	return 0;
}
