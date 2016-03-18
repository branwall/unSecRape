#pragma once
#include "InterfaceGeneral.h"

class InterfaceInventory : public InterfaceGeneral
{
protected:
	POINT InvStart; //inventory with relation to the relative inventory pixel
	POINT SpellStart; //where the spells start relative to inv pixel

public:
	InterfaceBank(); //constructor

						  //Check bank open
	bool VerifyBankOpen();

	//checks if bank is open to a specific tab. If not, opens thab.
	void VerifyTabOpen(int tabNumber);

	//check if inventory is empty
	bool VerifyInventoryEmpty();

	//Withdraws x items, typing in the exact amount to set the "x" in game
	
	void setWithdrawX(int bankPosition, int x);

	void withdraw1(int bankPosition);

	void withdraw5(int bankPosition);

	void withdraw10(int bankPosition);

	void withdrawX(int bankPosition);

	void withdrawABO(int bankPosition);
	//todo: add overloads that take a color for safe checking


	//Deposits X items, setting the exact amount 
	void setDepositX(int invPosition, int x)

	void deposit1(int invPosition)
	
	void deposit5(int invPosition)

	void deposit10(int invPosition)

	void depositX(int invPosition)
	//todo: add overloads to take a color for safe checking.


};