#pragma once
#include "Money.h"
#include "CardAndSymbols.h"
//only abstract
class Player
{
public:
	hand getHand() = 0;								//returns the Hand with both Cards on the Hand
	setHand(card pFirstCard, card pSecondCard) = 0;		//Function can be used to set the new Card of a player at the beginning of a new round

private:	
	hand playerHand;
};

