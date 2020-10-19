#pragma once
#include "Player.h"
#include "CardAndSymbols.h"
#include "Money.h"

class HumanPlayer: public Player{
public:
	HumanPlayer();
	hand getHand();									//returns the Hand with both Cards on the Hand
	setHand(card pFirstCard, card pSecondCard);		//Function can be used to set the new Card of a player at the beginning of a new round
	chipstack getWinnings();						//Function can be used to show whats the balance of the Player at the moment 
	setWinnings(chipstack pStartingChips);			//Function can be used to set the Balamce of a player at the beginning of a new round
private:
	chipstack winnings;
};
