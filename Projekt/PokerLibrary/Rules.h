#pragma once
#include "Player.h"
#include "CardAndSymbols.h"

enum winTypes {highCard, pair, twoPair, threeOfAKind, straight, flush, fullHouse, fourOfAKind, straightFlush, royalFlush};

struct BestHand
{
	/*bool RoyalFlush = false;
	bool StraightFlush = false;
	bool FourOfAKind = false;
	bool FullHouse = false;
	bool Flush = false;
	bool Straight = false;
	bool ThreeOfAKind = false;
	bool TwoPair = false;
	bool Pair = false;
	bool highCard = false*/

	std::array<bool, 10> musterCorrect = { false };

	card StraightFlushHighestCard;
	values FourOfAKindCard;
	std::array<values, 2> FullHouseCards; //first: threeOfAKind, second: pair
	std::array<card, 5> Flush;
	card StraightHighestCard;
	values ThreeOfAKindCard;
	std::array<values, 2> TwoPairCards; //highest value first; if you have a full house [0] is the pair of the three [1] is the normal pair
	values PairCard;
	card HighCard;
};

struct CardsAndIsHand {
	card card;
	bool isHand;
};


class Rules
{
public:
	Rules();
	~Rules();


	BestHand HasWon(hand CardsOnTheHand, std::array<card, 5> CardsOnTheTable);

private:
	std::array<card, 5> CardsForAStreet; //contains the cards that build a street
	
	bool CheckNormalFlush(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable); //checks for Flush (hand + community)
	bool CheckFlush(std::array<card, 5> Cards); //used for Straight Flush (+ Royal Flush)
	bool CheckValues(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable); //returns true if  street 
	int CheckHowManyOfAKind(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable, int i); //Helper for 2,3,... ofAKind
	bool CheckFourOfAKind(const std::array<card, 2>& CardsOnTheHand, std::array<int, 13> Numbers); //FourOfAKind
														
	//set the bits of musterCorrect
	void CheckThreeOfAKindAndFullHouse(const std::array<card, 2>& CardsOnTheHand, std::array<int, 13> Numbers); //3 of a Kind + full House (1. fullHouse, 2. 3oaK)
	void CheckTwoPairAndPair(const std::array<card, 2>& CardsOnTheHand, std::array<int, 13> Numbers); //2 pair, 1 twoPairs 
	void CheckNumbers(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable); // 1: fourOfAKind, 2: fullHouse, 3: 3oak, 4: 2pair, 5: pair, 0: highCard

	//helper function for straight

	BestHand Hands;
};