#pragma once
#include "InterfaceInventory.h"

class CakeBot : public InterfaceInventory{
public:
	POINT Cake;
	bool Combat = false;
	unsigned int cake1 = 0xd2c48800;
	unsigned int cake2 = 0x674e0500;
	int timeout = 0;

	void run()
	{
		bool inventoryOpen = true;
		VerifyActiveInventory(); //turn on inventory if its not already on

		findCake();

		while(inventoryOpen)
		{

			if (pix.SearchPixelArea(0x00ff0000, 783, 377, 897, 419)) // if in combat
			{
				printf("combat found!\n");
				combat();
			}

			if (VerifyInventoryFull(0xd6d1d100) || VerifyInventoryFull(0x89680700) || VerifyInventoryFull(0x46300300)) //if full inventory
			{
				DropAllItems();	//drop all items
				findCake();
			}
			/*
			if (pix.SearchPixelArea(0xb8a65700, 800, 340, 980, 430, 10)) //if cake stall is full
			{

				if (VerifyHoverText(HOVER_ACTION) && VerifyTopLeftText(HOVER_ACTION)) //if mouse landed on cake stall
				{

					mouse.LeftClick();
					Sleep(2500);
				}
			}*/
			findCake();
			inventoryOpen = VerifyInventoryOpen(); //exit while loop if inventory closed for osme reason
		}
		return;
	}
	
	void combat()
	{
		Combat = true;
		printf(" in COMBat\n");
		while (Combat)
		{
			Combat = pix.SearchPixelArea(0x00ff0000, 750, 200, 950, 460, 25);
		}
		printf("combat resolved.\n");
	}

	void findCake()
	{
		while (1)
		{
			if (pix.SearchPixelArea(0x00ff0000, 750, 200, 950, 460,25)) // if in combat
			{
				printf("Mid Cake Combat\n");
				combat();

			}
			Cake = pix.SearchPixelAreaForPoint(cake1, 800, 340, 980, 430, 13);
			if (Cake.x != -1)
			{
				mouse.SetDeviation(10);
				mouse.ChangeSpeed(0.5);
				mouse.MouseMoveArea(Cake.x - 5, Cake.y - 27, Cake.x + 7, Cake.y - 10);
				Sleep(50);
			}
			else
			{
				Cake = pix.SearchPixelAreaForPoint(cake2, 800, 340, 980, 430, 13);
				if (Cake.x != -1)
				{
					mouse.SetDeviation(10);
					mouse.ChangeSpeed(0.5);
					mouse.MouseMoveArea(Cake.x - 5, Cake.y - 27, Cake.x + 7, Cake.y - 10);
					Sleep(50);
				}
			}

			if (timeout > 5)
			{
				Cake = pix.SearchPixelAreaForPoint(cake2, 800, 340, 980, 430, 13);
				if (Cake.x != -1)
				{
					mouse.SetDeviation(10);
					mouse.ChangeSpeed(0.5);
					mouse.MouseMoveArea(Cake.x - 5, Cake.y - 27, Cake.x + 7, Cake.y - 10);
					Sleep(50);
				}
			}


			if (VerifyHoverText(HOVER_ACTION) && VerifyTopLeftText(HOVER_ACTION)) //if mouse landed on cake stall
			{
				timeout = 0;
				mouse.LeftClick();
				Sleep(2500); //animation of stealing
				break;
			}

			timeout++;
		}
	}


};