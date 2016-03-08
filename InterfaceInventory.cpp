#include "InterfaceInventory.h"

InterfaceInventory::InterfaceInventory()
{
	InvStart.x = pixInv._x - 46;
	InvStart.y = pixInv._y + 28;
}

//Check inventory open
bool InterfaceInventory::VerifyInventoryOpen()
{
	return pix.VerifyPixelColor(0x71261d00, pixInv._x + 25, pixInv._y - 11);
}

void InterfaceInventory::VerifyActiveInventory()
{
	if (!VerifyInventoryOpen())
	{
		mouse.MouseMoveArea(pixInv._x + 19, pixInv._y - 16, pixInv._x + 47, pixInv._y + 15); //coordinates of inventory tab
		mouse.LeftClick();
	}
}

//Gets Top Left coordinates of any inventory space ZERO INDEXED
POINT InterfaceInventory::GetItemCoords(int itemIndex)
{
	//horizontal index of the item (ZERO INDEXING)
	int invNumH = itemIndex % 4;
	//vertical index of item (ZERO INDEXING)
	int invNumV = (int)(itemIndex / 4);

	POINT InvIndex;
	InvIndex.x = InvStart.x + (INV_ITEM_WIDTH + INV_ITEM_HORIZ_SPACER)*invNumH;
	InvIndex.y = InvStart.y + (INV_ITEM_HEIGHT + INV_ITEM_VERT_SPACER)*invNumV;
	return InvIndex;
}

//moves to any pixel on an item given its index
void InterfaceInventory::MoveToItem(int itemIndex)
{
	POINT InvIndex = GetItemCoords(itemIndex);
	mouse.SetDeviation(25);
	mouse.MouseMoveArea(InvIndex.x, InvIndex.y, (InvIndex.x + 8) + (INV_ITEM_WIDTH - 16), (InvIndex.y + 8) + (INV_ITEM_HEIGHT - 16)); //inset 8 pixels on all sides because hover text is slow on edges
	mouse.SetDeviation(250);
}


bool InterfaceInventory::DropItem(int itemIndex)
{
	int dropOption = 1;
	menu5Option = false;

	mouse.ChangeSpeed(0.7); //slowishly move to item
	MoveToItem(itemIndex);
	Sleep(300); //sleep to get accurate verifying in next command, 300 is safe for all
	if (!VerifyTopLeftText(HOVER_ITEM)) //no item exists
		return false;
	if (VerifyHoverText(HOVER_ITEM)) //find items with more than usual # of options
	{
		menu5Option = true;
		dropOption = 2;
	}
	mouse.RightClick();
	mouse.ChangeSpeed(1.0);
	ChooseMenuOption(dropOption);
	mouse.LeftClick();
	return true;
}

//drop items within range, Drops all items between and including start and end
// stops once a space is reached
void  InterfaceInventory::DropItemRange(int start, int end)
{
	for (int i = start; i <= end; i++)
	{
		DropItem(i);
	}		

}

//drops every item in inventory
void  InterfaceInventory::DropAllItems()
{
	DropItemRange(0, 27);
}

//drops every item of a certain color in inventory
void  InterfaceInventory::DropItemsColored(unsigned int color)
{
	POINT item;
	for (int i = 0; i <= 27; i++)
	{
		item = GetItemCoords(i);
		if (pix.SearchPixelArea(color, item.x, item.y, item.x + INV_ITEM_WIDTH, item.y + INV_ITEM_HEIGHT)) //check if item is in this slot
			DropItem(i);
	}
}

bool InterfaceInventory::VerifyInventoryFull()
{
	bool Item = false;
	MoveToItem(27);
	Item |= VerifyTopLeftText(HOVER_ITEM); //checks both hover and top left to see if item exists 
	Item |= VerifyHoverText(HOVER_ITEM);
	return Item;
}

bool InterfaceInventory::VerifyInventoryFull(unsigned int color)
{
	POINT item = GetItemCoords(27);
	return pix.SearchPixelArea(color, item.x, item.y, item.x + INV_ITEM_WIDTH, item.y + INV_ITEM_HEIGHT, 10);
}
