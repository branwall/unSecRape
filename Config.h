#pragma once
#include "Password.h" //runescape password for logging in

/*
/		Coordinates assume running OSBuddy runscape client FULLSCREEN on a 1920x1080 monitor
/
/		!WARNING! - all derived classes' coordinates are derived from the three Coordinates declared below (pixStats, pixChat, pixInv)
/		MAKE SURE THESE COORDINATES ARE VALID!!
/
/		Additionally, for multiple monitor use set your SCREEN variable as either LEFT_SCREEN or RIGHT_SCREEN
/		If only using one monitor, set SCREEN to LEFT_SCREEN.
*/

#ifndef _CONFIG_H_
#define _CONFIG_H_

#define RIGHT_SCREEN 1920
#define LEFT_SCREEN 0


//==========SET ME!============
const int SCREEN = LEFT_SCREEN;
// sets the horizontal distance of coordinate systems

//HOTKEY THINGS
const int ESCAPE = 0x1b; //escape hotkey in hex  
#define PAUSE_PROGRAM 1
#define EXIT_PROGRAM 2

struct Area {
	int x1;
	int x2;
	int y1;
	int y2;

	Area()
	{
		x1 = x1 = y1 = y2 = 0;
	}
	Area(int _x1, int _y1, int _x2, int _y2)
	{
		x1 = _x1;
		x2 = _x2;
		y1 = _y1;
		y2 = _y2;
	}
};

struct Pixel {
	unsigned int _color;   //assign colors in HEX (RR GG BB AA)  -  RGBA format (typically alpha is 00)
	int _x;
	int _y;

	Pixel()
	{
		_x = _y = _color = 0;
	}
	Pixel(unsigned int color, int x, int y)
	{
		_x = x;
		_y = y;
		_color = color;
	}
}; // ============= MAKE SURE THESE ARE VALID ===========
// pixStats(0xf1f5f600,1483 + SCREEN,55), pixChat(0x4a5a6000,25 + SCREEN,877), pixInv(0xeaeafb00,1489 + SCREEN,720);
static const Pixel pixStats(0xf6f5f100, 1483 + SCREEN, 55);
static const Pixel pixChat(0x605a4a00, 25 + SCREEN, 877); 
static const Pixel pixInv(0xfbeaea00, 1489 + SCREEN, 720);


//Create STATS pixel to verify window (uses center white pixel on compass)
//Create INVENTORY pixel to verify inv. (uses center whtie pixel on quests icon)
//Create CHAT pixel to verify chat window (uses dark pixel on stud in top left corner arrow on chat window - hard to see)

#define HOVER_NPC  0xffff0000//monster hover text color - YELLOW
#define HOVER_ITEM 0xff904000 //item hover text color - ORANGE
#define HOVER_ACTION  0x00ffff00//action hover text color - BLUE
#define HOVER_MAGIC 0x00ff0000//Magic Spell hover text color - GREEN

#define MENU_HEADER 20//pixel height of "choose option"
#define MENU_OPTION 15//pixel height of each option
#define MENU_MINWIDTH 50//minimum pixel width of half the menu. mouse starts in center above choose option

#define INV_ITEM_HEIGHT 32//height of an item
#define INV_ITEM_WIDTH 32 //width of an item
#define INV_ITEM_HORIZ_SPACER 10//pizel difference horizontally between items
#define INV_ITEM_VERT_SPACER 4//pixel difference vertical between items
#define INV_MAGIC_SPELL_HEIGHT 24 //height of a spell
#define INV_MAGIC_SPELL_WIDTH 24 //height of a spell

#define MAGIC_TELE 0x8e8df300 //color of teleport ringsi n every tele spell
#define MAGIC_ALCH 0xbcc2c000 //color of green bottle in high alch
#define MAGIC_HEAT 0xb0100200 //color of red fire part in superheat spell
#define MAGIC_ENTANGLE 0x04af0400 //color of entangle

static const Pixel SUPERHEAT(MAGIC_HEAT, 4, 3); //creates the spell using its active color as well as its spellbook coords
static const Pixel TELEBLOCK(MAGIC_TELE, 5, 8); //creates a spell for teleblock
static const Pixel ENTANGLE(MAGIC_ENTANGLE, 1, 8); //create a spell entangle

const int GAME_CENTER_X = 821 + SCREEN; //center of gameplay window X coord
const int GAME_CENTER_Y = 504 + SCREEN; //center of gameplay window Y coord

#endif
