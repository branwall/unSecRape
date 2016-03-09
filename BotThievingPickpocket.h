#pragma once
#include "InterfaceStats.h"
#include "InterfaceInventory.h"

class BotThievingPickpocket
{
protected:
	InterfaceStats stat;
	InterfaceInventory inv;
	Mouse mouse;
	Area defaultRegion;

	//ENEMY COLOR LIST
	unsigned int VarrockEastGuardSkirt =  0xcc9c0c00;
	unsigned int VarrockEastGuardSkirt2 = 0x6b510500;
	unsigned int AdroKnight = 0x5c0dc600;
	unsigned int AdroKnight2 = 0x29055900;
	unsigned int Watchmen = 0x06086c00; // blue shoulder
	unsigned int Watchmen2 = 0x78181200; // red pants

	//FOOD LIST
	unsigned int monkfishMouth = 0xa6666300;
	unsigned int cake = 0xa6999800;
	unsigned int bread = 0x2e230200;
	unsigned int PineapplePizza = 0xa5a30900;

	unsigned int ThievingEXP = 0x00000100;
	unsigned int color, color2, food;

	int timeout= 35;
	int respawnTimeout = 75;

public:
	BotThievingPickpocket()
	{
		defaultRegion.x1 = 250; // 100; //250
		defaultRegion.y1 = 150;//  60;  //250
		defaultRegion.x2 = 1250;//  1500; //1300
		defaultRegion.y2 = 800;//  950; //800

		stat.SetMouseSpeed(0.5);
		color = Watchmen;  //==========================SET MEEEE===============================
		color2 = Watchmen2;
		food = bread;
	}

	//runs completely default
	void run()
	{
		while (1)
		{
			stat.HandleHotkeys();//ALWAYS BEGIN WITH THIS in loop

			if (stat.VerifyCombat() == 1)
				continue;

			if (stat.CheckExperienceCircle(ThievingEXP, 1))
				timeout = 35;

			if (respawnTimeout <= 0)//move to reset respawn of trapped guy
			{
				printf("time to twist up the spawn~!\n");
				Sleep(5000);
				mouse.MouseMoveArea(1550,110,1570,125);
				mouse.LeftClick();
				Sleep(500);
				respawnTimeout = 75;
			}

			if (timeout <= 0)
			{
				inv.Logout();
				break;
			}

			if (!inv.AttemptToEatAtHp(food,75))
			{
				printf("NO FOOOD FOUND!!\n");
				inv.Logout();
				break;
			}

			//stat.FindEnemy(color, 250, 250, 1300, 800);
			if (!stat.SearchEnemyBloom(color, defaultRegion.x1, defaultRegion.y1, defaultRegion.x2, defaultRegion.y2))
			{
				printf("Attempting second color bloom\n");
				stat.SearchEnemyBloom(color2, defaultRegion.x1, defaultRegion.y1, defaultRegion.x2, defaultRegion.y2);
			}
				printf("thiving tiem, TO: %2i\n", timeout);
			Sleep(400);
			if (stat.ChooseMenuOptionColorCheck(1, HOVER_NPC))
			{
				mouse.LeftClick();
				Sleep(400);
			}
			timeout--;
			respawnTimeout--;
			//std::cin.ignore();
		}
	}

	//runs given a color to search for
	void run(unsigned int _color)
	{
		while (1)
		{
			if (stat.CheckExperienceCircle(ThievingEXP, 1))
				timeout = 35;

			if (timeout <= 0)
				inv.Logout();

			if (!inv.AttemptToEatAtHp(cake, 25))
			{
				printf("NO FOOOD FOUND!!\n");
				inv.Logout();
				break;
			}

			//stat.FindEnemy(guardSkirt, 250, 250, 1300, 800);
			stat.SearchEnemyBloom(_color, defaultRegion.x1, defaultRegion.y1, defaultRegion.x2, defaultRegion.y2);
			printf("thiving tiem, TO: %2i\n", timeout);
			Sleep(400);
			if (stat.ChooseMenuOptionColorCheck(1, HOVER_NPC))
			{
				mouse.LeftClick();
				Sleep(400);
			}
			timeout--;

			//std::cin.ignore();
		}
	}

	//runs given a color and aregion
	void run(unsigned int _color,int x1, int y1,int x2, int y2)
	{
		while (1)
		{
			if (stat.CheckExperienceCircle(ThievingEXP, 1))
				timeout = 35;

			if (timeout <= 0)
				inv.Logout();

			if (!inv.AttemptToEatAtHp(cake, 25))
			{
				printf("NO FOOOD FOUND!!\n");
				inv.Logout();
				break;
			}

			//stat.FindEnemy(guardSkirt, 250, 250, 1300, 800);
			stat.SearchEnemyBloom(_color, x1, y1, x2, y2);
			printf("thiving tiem, TO: %2i\n", timeout);
			Sleep(400);
			if (stat.ChooseMenuOptionColorCheck(1, HOVER_NPC))
			{
				mouse.LeftClick();
				Sleep(400);
			}
			timeout--;

			//std::cin.ignore();
		}
	}
};
