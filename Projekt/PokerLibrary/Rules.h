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
	suits Flush;
	card StraightHighestCard;
	values ThreeOfAKindCard;
	std::array<values, 2> TwoPairCards; //highest value first; if you have a full house [0] is the pair of the three [1] is the normal pair
	values PairCard;
	card HighCard;
};

//TODO: optimize

class Rules
{
public:
	Rules();
	~Rules();


	BestHand HasWon(hand CardsOnTheHand, std::array<card, 5> CardsOnTheTable);
	friend class RulesFriend;

private:
	std::array<card, 5> CardsForAStreet; //contains the cards that build a street?
	
	bool CheckNormalFlush(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable); //checks for Flush (hand + community)
	bool CheckFlush(std::array<card, 5> Cards); //used for Straight Flush (+ Royal Flush)
	bool CheckSuits(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable); //returns true if  street (?)
	int CheckHowManyOfAKind(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable, int i); //Helper for 2,3,... ofAKind
	bool CheckFourOfAKind(std::array<int, 13> Numbers); //FourOfAKind
														
	//set the bits of musterCorrect
	void CheckThreeOfAKindAndFullHouse(std::array<int, 13> Numbers); //3 of a Kind + full House (1. fullHouse, 2 3oaK)
	void CheckTwoPairAndPair(std::array<int, 13> Numbers); //2 pair, 1 twoPairs 
	void CheckNumbers(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable); // 1: fourOfAKind, 2: fullHouse, 3: 3oak, 4: 2pair, 5: pair, 0: highCard

	BestHand Hands;
};