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
	std::array<CardsAndSympols,5> CardsForAStreet;

	struct BestHand 
	{
		bool RoyalFlush = false;
		bool StraightFlush = false;
		bool FourOfAKind = false;
		bool FullHouse = false;
		bool Flush = false;
		bool Straight = false;
		bool ThreeOfAKind = false;
		bool TwoPair = false;
		bool Pair = false;


		CardsAndSymbols StraightFlushHighestCard;
		values FourOfAKindCard;
		std::array<values, 2> FullHouseCards;
		CardsAndSymbols StraightHighestCard;
		values ThreeOfAKindCard;
		std::array<values, 2> TwoPairCards;
		values PairCard;
		CardsAndSymbols HighCard;
	}Hands;
}

