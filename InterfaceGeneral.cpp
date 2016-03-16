#include "InterfaceGeneral.h"


InterfaceGeneral::InterfaceGeneral() // constructor (sets hotkeys)
{
	//arguments Window, HK-ID, SPECIAL-KEYS, HOTKEY
	RegisterHotKey(NULL, 1, 0, ESCAPE); //Pause the program, (needs enter to resume)
	RegisterHotKey(NULL, 2, MOD_SHIFT, ESCAPE);

	logTimeout = 4;

	//PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);
	//GetMessage(&msg, 0, 0, 0); //set to receive

}


InterfaceGeneral::~InterfaceGeneral() // Destructor (delets hotkeys on program exit)
{
	UnregisterHotKey(NULL, 1);
	UnregisterHotKey(NULL,2);

	//HandleHotkeys();
}

//handles what hotkeys do
void InterfaceGeneral::HandleHotkeys()
{
	PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	if (msg.message == WM_HOTKEY)
	{
		if (msg.wParam == 1) //1st hotkey
		{
			printf("================ Program Paused - Press ENTER to continue ==================\n");
			std::cin.ignore(); //pause until enter is pressed
		}

		if (msg.wParam == 2) //2nd hotkey
		{
			printf("================ Program EXITING ==================\n");
			exit(0); //exit porgram
		}


		msg.message = 0; //reset the message so that it resume;
		return;
	}
}


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

//Check if maybe a level up perhaps
bool InterfaceGeneral::CheckLevelUp()
{
	bool check = false;
	check = pix.SearchPixelArea(0x00008000, 290, 908, 466, 935, 10);
	if (check)
	{
		printf("LEVELED uppppp\n");
		mouse.MouseMoveArea(160,970,340,990);
		mouse.LeftClick();
	}
	return check;
}

//Check if maybe a level up perhaps
// mode '0' ignores hitpoints levels
bool InterfaceGeneral::CheckLevelUp(int mode)
{
	bool check = false;
	check = pix.SearchPixelArea(0x00008000, 290, 908, 466, 935, 10);
	if (check)
	{
		if (mode == 0) //skip hp levels
		{
			if (pix.SearchPixelArea(0xb6145000, 37, 895, 180, 980, 20)) //if found hp
				check = false;
		}
		printf("LEVELED uppppp\n");
		mouse.MouseMoveArea(160, 970, 340, 990);
		mouse.LeftClick();
	}
	return check;
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

//checks for black background in health circle
//amount should be some 1-100 value. 
//returns true if health is there
bool InterfaceGeneral::CheckHealthAmount(int amount)
{
	bool result = true; //assumes you ahve the health
	unsigned int HealthBGBlack1 = 0x13131300; //colors of the background blacki in teh circles
	unsigned int HealthBGBlack2 = 0x0b0b0b00;

	if (amount >= 90)
	{
		if ((pix.VerifyPixelColor(HealthBGBlack1, 1471, 85)) || (pix.VerifyPixelColor(HealthBGBlack2, 1471, 85))) //90 % pixel
			result = false;
	}

	else if (amount >= 70 && amount < 90)
	{
		if ((pix.VerifyPixelColor(HealthBGBlack1, 1462, 90)) || (pix.VerifyPixelColor(HealthBGBlack2, 1462, 90)))
			result = false;
	}

	else if (amount >= 50 && amount < 70)
	{
		if ((pix.VerifyPixelColor(HealthBGBlack1, 1462, 95)) || (pix.VerifyPixelColor(HealthBGBlack2, 1462, 95)))
			result = false;
	}

	else if (amount >= 35 && amount < 50)
	{
		if ((pix.VerifyPixelColor(HealthBGBlack1, 1464, 100)) || (pix.VerifyPixelColor(HealthBGBlack2, 1464, 100)))
			result = false;
	}
	else if (amount >= 25 && amount < 35)
	{
		if ((pix.VerifyPixelColor(HealthBGBlack1, 1464, 103)) || (pix.VerifyPixelColor(HealthBGBlack2, 1464, 103)))
			result = false;
	}



	return result;
}


//sets mouse move speed 0.1-1.0 where lower is faster
void InterfaceGeneral::SetMouseSpeed(float speed)
{
	mouse.ChangeSpeed(speed);
	return;
}


//checks if loggedout or in process of logging in.
//if false, it is logged out
//if true, it is logged in
bool InterfaceGeneral::CheckIfInGame()
{
	unsigned int blackBorder = 0x00000000;
	bool Check = true;

	//checks left side
	Check &= pix.VerifyPixelColor(blackBorder, 300 + SCREEN, 50);
	Check &= pix.VerifyPixelColor(blackBorder, 300 + SCREEN, 350);
	Check &= pix.VerifyPixelColor(blackBorder, 300 + SCREEN, 550);

	//bottom section
	Check &= pix.VerifyPixelColor(blackBorder, 700 + SCREEN, 700);

	//checks right side
	Check &= pix.VerifyPixelColor(blackBorder, 1250 + SCREEN, 50);
	Check &= pix.VerifyPixelColor(blackBorder, 1250 + SCREEN, 350);
	Check &= pix.VerifyPixelColor(blackBorder, 1250 + SCREEN, 550);

	//inverse as currently its checking for the black
	return !Check;
}

//after 6 hours it logs you out. this logs you back innnn
bool InterfaceGeneral::HandleAutoLogOut()
{
	const int passwordLen = sizeof(password);
	char pass[passwordLen];
	strncpy_s(pass, password, passwordLen);

	if (!CheckIfInGame()) //confirmed logout
	{

		if (logTimeout <= 0)
			exit(0);

		printf("======================= Auto Logout Detected ==============================\n");
		if (pix.VerifyPixelColor(0xf1f2a000, 700 + SCREEN, 130)) //yellow sword crossguard
		{
			printf("Logout screen sword glint\n");
			mouse.MouseMoveArea(784+SCREEN, 302, 810+SCREEN, 307); //move login
			Sleep(100);
			mouse.LeftClick();
			key.Type(pass,passwordLen);//type dat password yo
			key.GenerateKey(VK_RETURN, false, false); //send enter
			Sleep(10000);
		}

		if (pix.VerifyPixelColor(0xab837f00, 713 + SCREEN, 326)) //red buttons border highlight
		{
			printf("Loggin screen red button\n");
			mouse.MouseMoveArea(713+SCREEN,327,930+SCREEN, 400); //move to red button
			Sleep(100);
			mouse.LeftClick();
			Sleep(3000);
			logTimeout--;
		}
	}

	return false;
}