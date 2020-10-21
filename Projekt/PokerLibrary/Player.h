#pragma once
#include "Money.h"
#include "CardAndSymbols.h"
#include "enum.h"
#include <vector>
#include <string>
struct outPlay
{
	plays play;
	chipstack chips;
};

//only abstract
class Player
{
public:
	Player(chipstack pStartingChips, std::string pName) {
		winnings = pStartingChips;
		name = pName;
	}

	hand getHand() const {										//returns the Hand with both Cards on the Hand
		return playerHand;
	}

	void setHand(card pFirstCard, card pSecondCard) {			//Function can be used to set the new Card of a player at the beginning of a new round
		playerHand.firstCard = pFirstCard;
		playerHand.secondCard = pSecondCard;
	}

	std::string getName() const {
		return name;
	}

	chipstack getWinnings() const {					//returns the balance of the Player at the moment 
		return winnings;
	}

	void setWinnings(chipstack pStartingChips) {	//Function can be used to set the Balance of a player at the beginning of a new round
		winnings = pStartingChips;
	}
	
	void addToWinnings(chipstack pAdd) {	//
		winnings = winnings + pAdd;
	}

	void decFromWinnings(chipstack pDec) {	//
		winnings = winnings - pDec;
	}

	virtual outPlay play(chipstack pToCheck, std::vector<plays> pPlays) = 0;

	bool bankrupt() const;
	void setBankrupt();
private:	
	std::string name;
	hand playerHand;
	chipstack winnings;

	bool m_bankrupt = false;
};

