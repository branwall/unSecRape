#pragma once
#include "InterfaceGeneral.h"

class InterfaceInventory : public InterfaceGeneral
{
protected:
	 POINT InvStart; //inventory with relation to the relative inventory pixel

public:
	InterfaceInventory(); //constructor

	//Check inventory open
	bool VerifyInventoryOpen();

	//checks inventory is open, if not, then opens it.
	void VerifyActiveInventory();

	//Gets Top Left coordinates of any inventory space ZERO INDEXED
	POINT GetItemCoords(int itemIndex);

	//moves to any pixel on an item given its index
	void MoveToItem(int itemIndex);

	//Drop an item smartly
	bool DropItem(int itemIndex);

	//drop items within range, Drops all items between and including start and end
	void DropItemRange(int start, int end);

	//drops every item in inventory
	void DropAllItems();

	//given a color, drop all instances colored that
	void DropItemsColored(unsigned int color);

	// checks slot 28 to see if inventory is full
	bool VerifyInventoryFull();

	// checks slot 28 against a color to see if inventory is full
	bool VerifyInventoryFull(unsigned int color);

};