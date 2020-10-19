#pragma once
#include "Money.h"
#include "CardAndSymbols.h"
#include "enum.h"
#include <vector>

struct outPlay
{
	plays play;
	chipstack chips;
};

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
	
	HumanPlayer::addToWinnings(chipstack pAdd) {	//
		winnings = winnings + pAdd;
	}

	HumanPlayer::decFromWinnings(chipstack pDec) {	//
		winnings = winnings - pDec;
	}

	virtual chipstack play(chipstack pToCheck, std::vector<plays> pPlays) = 0;
private:	

	hand playerHand;
	chipstack winnings;
};

