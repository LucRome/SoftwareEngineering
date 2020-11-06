#pragma once
#include "Player.h"
#include "CardAndSymbols.h"

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
};


class Rules
{
public:
	Rules();
	~Rules();


	BestHand HasWon(hand CardsOnTheHand, std::array<card, 5> CardsOnTheTable);


private:
	std::array<card, 5> CardsForAStreet; //contains the cards that build a street?

	bool CheckNormalFlush(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable); //checks for Flush (hand + community)

	bool CheckFlush(std::array<card, 5> Cards); //used for Straight Flush (+ Royal Flush)

	bool CheckSuits(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable); //returns true if  street (?)

	int CheckHowManyOfAKind(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable, int i); //Helper for 2,3,... ofAKind

	bool CheckVourOfAKind(std::array<int, 13> Numbers); //FourOfAKind

	int CheckThreeOfAKindAndFullHouse(std::array<int, 13> Numbers); //3 of a Kind + full House

	int CheckTwoPairAndPair(std::array<int, 13> Numbers); //pair, twoPairs (???)
	int CheckNumbers(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable); // 1: fourOfAKind, 2: ThreeOfAKind(?), ...

	BestHand Hands;
};