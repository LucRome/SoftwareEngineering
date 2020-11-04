#pragma once
#include "Player.h"
#include "CardAndSymbols.h"

class Rules
{
public:
	Rueles();
	~Rules();

	int HasWon(std::array<CardAndSymbols, 2> CardsOnTheHand, std::array<CardsAndSymbols, 5> CardsOnTheTable);


private:
	CardsAndSympols[5] CardsForAStreet;
};

