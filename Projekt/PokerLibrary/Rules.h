#pragma once
#include "Player.h"
#include "CardAndSymbols.h"

class Rules
{
public:
	Rules();
	~Rules();

	int HasWon(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable);


private:
	std::array<card, 5> CardsForAStreet;

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


		card StraightFlushHighestCard;
		values FourOfAKindCard;
		std::array<values, 2> FullHouseCards;
		card StraightHighestCard;
		values ThreeOfAKindCard;
		std::array<values, 2> TwoPairCards;
		values PairCard;
		card HighCard;
	}Hands;
};