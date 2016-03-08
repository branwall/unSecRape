#include "InterfaceGeneral.h"

//verifies that hover text contains a specified color
bool InterfaceGeneral::VerifyHoverText(unsigned int color) 
{
	int hoverTLX, hoverTLY, hoverBRX, hoverBRY;
	POINT cursor;
	cursor = mouse.GetPosition();

	//hover box starts [Top Left] (18,3) pixels from the cursor
	//hover box ends [Bottom Right] (63,18) pixels from its start
	hoverTLX = cursor.x + 18;
	hoverTLY = cursor.y + 3;
	hoverBRX = hoverTLX + 100;
	hoverBRY = hoverTLY + 18;
	bool result = pix.SearchPixelArea(color, hoverTLX, hoverTLY, hoverBRX, hoverBRY);
	//if cant find box on the right side
	if (!result)  //the hover box flips sides when far right side of osbuddy, depends on text box size though...
	{
		hoverTLX = cursor.x - 100;
		hoverTLY = cursor.y + 3;
		hoverBRX = cursor.x - 18;
		hoverBRY = hoverTLY + 18;
		result = pix.SearchPixelArea(color, hoverTLX, hoverTLY, hoverBRX, hoverBRY);
	}
	return result;
}

//can trigger on "Level Color" of both monsters and players. Extremely recommend use in conjunction with verifyhovertext.
bool InterfaceGeneral::VerifyTopLeftText(unsigned int color)
{
	POINT topLeft;
	topLeft.x = 2 + SCREEN;
	topLeft.y = 33;
	//uses a shade tolerance of 55. this is important cause top-left hover text is semi transparent and changes given background. 55 is good.
	return pix.SearchPixelArea(color, topLeft.x, topLeft.y, topLeft.x+180, topLeft.y+18,65);
}

bool InterfaceGeneral::VerifyOSbuddy()
{
	bool OSbuddy = false;

	OSbuddy = pix.VerifyPixelColor(pixStats);
	OSbuddy &= pix.VerifyPixelColor(pixChat);
	OSbuddy &= pix.VerifyPixelColor(pixInv);

	return OSbuddy;
}

//takes option choice on Zero Indexing (option 1 = optionChoice:0, option 2 = opChoice:1, etc.)
POINT InterfaceGeneral::GetMenuOptionCoords(int optionChoice)
{
	int offset;
	POINT cursor, Menu;
	cursor = mouse.GetPosition();

	Menu.x = cursor.x - (MENU_MINWIDTH/2);
	Menu.y = cursor.y + MENU_HEADER + (MENU_OPTION*optionChoice);

	//HANDLE WHEN MENU IS AT BOTTOM OF THE SCREEEEEN
	if (menu5Option)
		offset = cursor.y + MENU_HEADER + (MENU_OPTION * 5); //ONLY HANDLES MENUS WITH 5 OPTIONS
	else
		offset = cursor.y + MENU_HEADER + (MENU_OPTION * 4); //ONLY HANDLES MENUS WITH 4 OPTIONS

	offset = offset - 1038; //1037 is bottom of the screen where teh menu can maximally exist
	if (offset > 0)
	{// changes and realigns the menu box
		Menu.x = cursor.x - MENU_MINWIDTH;
		Menu.y = cursor.y-offset + MENU_HEADER + (MENU_OPTION*optionChoice);
		//printf("Menu: (%4i, %4i)", Menu.x, Menu.y);
	}
	return Menu;
}

//takes option choice on Zero Indexing (option 1 = optionChoice:0, option 2 = opChoice:1, etc.)
void InterfaceGeneral::ChooseMenuOption(int optionChoice)
{
	POINT option = GetMenuOptionCoords(optionChoice);
	//uses custom deviation as to not close the menu by moving mouse too far
	mouse.SetDeviation(25);//smaller deviation going from menu to option
	mouse.MouseMoveArea(option.x, option.y+5, option.x + MENU_MINWIDTH, option.y + MENU_OPTION - 3); //the 3's are buffer to accouunt for error
	mouse.SetDeviation(250); //reset deviation
	return;
}

//Chooses a menu option only if 'HOVER_xxx' exists on the desired option, Zero indexing
bool InterfaceGeneral::ChooseMenuOptionColorCheck(int optionChoice, unsigned int color)
{
	POINT option = GetMenuOptionCoords(optionChoice);
	//uses custom deviation as to not close the menu by moving mouse too far
	if (!pix.SearchPixelArea(color, option.x, option.y + 5, option.x + MENU_MINWIDTH, option.y + MENU_OPTION - 3))
		return false;
	mouse.SetDeviation(7);//smaller deviation going from menu to option
	mouse.MouseMoveArea(option.x, option.y + 5, option.x + MENU_MINWIDTH, option.y + MENU_OPTION - 3); //the 3's are buffer to accouunt for error
	mouse.SetDeviation(250); //reset deviation
	return true;
}

//when all else fails. gtfo
void InterfaceGeneral::Logout()
{
	Area doorButton(1509 + SCREEN, 1004, 1532 + SCREEN, 1033);
	Area Logout(1459+SCREEN,942,1584+SCREEN,965);
	mouse.MouseMoveArea(doorButton);
	Sleep(400);
	mouse.LeftClick();
	Sleep(400);
	mouse.MouseMoveArea(Logout);
	Sleep(400);
	mouse.LeftClick();
	return;
}