#pragma once
#include "Money.h"
#include "CardAndSymbols.h"
//only abstract
class Player
{
public:
	hand getHand() {										//returns the Hand with both Cards on the Hand
		return playerHand;
	}

	setHand(card pFirstCard, card pSecondCard) {			//Function can be used to set the new Card of a player at the beginning of a new round
		playerHand.firstCard = pFirstCard;
		playerHand.secondCard = pSecondCard;
	}

	chipstack HumanPlayer::getWinnings() {					//returns the balance of the Player at the moment 
		return winnings;
	}

	HumanPlayer::setWinnings(chipstack pStartingChips) {	//Function can be used to set the Balance of a player at the beginning of a new round
		winnings = pStartingChips;
	}
private:	

	hand playerHand;
	chipstack winnings;
};

