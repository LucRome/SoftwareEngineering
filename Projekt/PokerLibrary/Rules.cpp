#include "pch.h"
#include "Rules.h"
#include <string.h>
#include <algorithm>



bool Rules::CheckNormalFlush(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable)
{
	std::array<card, 7> cards;
	for (int l = 0; l < 5; l++) {
		cards[l] = CardsOnTheTable[l];
	}
	cards[5] = CardsOnTheHand[0];
	cards[6] = CardsOnTheHand[1];
	//sort array cards
	int m = 0, n = 7, o=0;
	for (m=0; m < n; m++) {
		for (o = m + 1; o < n; o++) {
			if (cards[m].value > cards[o].value) {
				card temp = cards[m];
				cards[m] = cards[o];
				cards[o] = temp;
			}
		}
	}

	suits flush;
	for (int j = 0; j < 2; j++)
	{
		int Counter = 1;
		for (int i = 0; i < 5; i++)
		{

			if (CardsOnTheHand[j].suit == CardsOnTheTable[i].suit)
			{
				Counter++;
				flush = CardsOnTheHand[j].suit;
			}
		}
		if (Counter >= 5)
		{
			int arrayCounter = 0;
			for (int k = 6; k >=0; k--) {
				if (cards[k].suit == flush) {
					if (arrayCounter == 5) {
						return true;
					}
					Hands.Flush[arrayCounter]=cards[k];
					arrayCounter++;
				}
			}
			return true;
		}
		else
		{
			Counter = 0;
			flush = s_none;
		}
	}
	return false;
}


bool Rules::CheckFlush(std::array<card, 5> Cards) //used to check for Royal flush and straightFlush
{
	suits Check;
	Check = Cards[0].suit; //enough to check for the suit of the first card (all or nothing)
	int Counter = 1;
	bool isFlush = true;
	for (card c : Cards) {
		if (c.suit != Check) {
			isFlush = false;
			break;
		}
	}
	return isFlush;
}

bool Rules::CheckSuits(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable)
{
	values Check;
	int Counter = 0;
	int CounterBefore = 0;
	for (int i = 12; i >= 0; i--)
	{

		for (int j = 0; j < 2; j++)
		{
			if (CardsOnTheHand[j].value == values(i) && (Counter == CounterBefore))
			{
				Counter++;
				CardsForAStreet[Counter - 1] = CardsOnTheHand[j];
			}
		}
		if (Counter == CounterBefore)
		{
			for (int j = 0; j < 5; j++)
			{
				if (CardsOnTheTable[j].value == values(i) && (Counter == CounterBefore ))
				{
					Counter++;
					CardsForAStreet[Counter - 1] = CardsOnTheTable[j];
				}
			}
		}
		if ((Counter == CounterBefore) && Counter < 5)
		{
			Counter = 0;
			CounterBefore = 0;
		}
		else if (Counter < 5)
		{
			CounterBefore = Counter;
		}
		if (Counter >= 5)
		{
			return true;
		}

	}
	return false;
}

int Rules::CheckHowManyOfAKind(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable, int i)
{
	int Counter = 0;
	for (int j = 0; j < 5; j++) //only count cards on the table
	{
		if (CardsOnTheTable[j].value == values(i))
		{
			Counter++;
		}
	}
	return Counter;
}

bool Rules::CheckFourOfAKind(const std::array<card, 2>& CardsOnTheHand, std::array<int, 13> Numbers)
{
	
	values one = CardsOnTheHand[0].value;
	values two = CardsOnTheHand[1].value;
	int rest;
	if (one == two) {
		rest = 2;
	}
	else {
		rest = 3;
	}
	if (Numbers[one] >= rest) {
		Hands.FourOfAKindCard = one;
		Hands.ThreeOfAKindCard = one;
		Hands.TwoPairCards[0] = one;
		Hands.TwoPairCards[1] = one;
		Hands.PairCard = one;
		return true;
	}
	else if (Numbers[two] >= rest){
		Hands.FourOfAKindCard = one;
		Hands.ThreeOfAKindCard = one;
		Hands.TwoPairCards[0] = one;
		Hands.TwoPairCards[1] = one;
		Hands.PairCard = one;
		return true;
	}
	return false;
}

//sets bits in Hands struct
void Rules::CheckThreeOfAKindAndFullHouse(const std::array<card, 2>& CardsOnTheHand, std::array<int, 13> Numbers)
{
	values one = CardsOnTheHand[0].value;
	values two = CardsOnTheHand[1].value;
	if (one == two) //-> Only 3 Of A Kind possible
	{
		if (Numbers[one] >= 1) { //3 Of A Kind
			Hands.ThreeOfAKindCard = one;
			Hands.musterCorrect[threeOfAKind] = true;
			Hands.musterCorrect[pair] = true;
			Hands.PairCard = one;
		}
	}
	else if (Numbers[one] >= 2) { //3 OaK
		Hands.ThreeOfAKindCard = one;
		Hands.musterCorrect[threeOfAKind] = true;
		Hands.musterCorrect[pair] = true;
		Hands.PairCard = one;
		if (Numbers[two] >= 1) { //pair -> FullHouse
			Hands.FullHouseCards[0] = one;
			Hands.FullHouseCards[1] = two;
			Hands.musterCorrect[fullHouse] = true;
			Hands.musterCorrect[twoPair] = true;
			Hands.TwoPairCards[0] = two;
			Hands.TwoPairCards[1] = one;
		}
	}
	else if (Numbers[two] >= 2) { //3 OaK
		Hands.ThreeOfAKindCard = two;
		Hands.musterCorrect[threeOfAKind] = true;
		Hands.musterCorrect[pair] = true;
		Hands.PairCard = one;
		if (Numbers[one] >= 1) { //pair -> FullHouse
			Hands.FullHouseCards[0] = two;
			Hands.FullHouseCards[1] = one;
			Hands.musterCorrect[fullHouse] = true;
			Hands.musterCorrect[twoPair] = true;
			Hands.TwoPairCards[0] = one;
			Hands.TwoPairCards[1] = two;
		}
	}
}

void Rules::CheckTwoPairAndPair(const std::array<card, 2>& CardsOnTheHand, std::array<int, 13>Numbers)
{

	values one = CardsOnTheHand[0].value;
	values two = CardsOnTheHand[1].value;
	if (one == two) { //-> pair
		Hands.PairCard = one;
		Hands.musterCorrect[pair] = true;
	}
	else {
		bool p1 = Numbers[one] >= 1;
			bool p2 = Numbers[two] >= 1;
			if (p1 && p2) { //two pairs
				if (one > two) { //determine "better pair"
					Hands.TwoPairCards[0] = one;
					Hands.TwoPairCards[1] = two;
					Hands.PairCard = one;
				}
				else
				{
					Hands.TwoPairCards[0] = two;
					Hands.TwoPairCards[1] = one;
					Hands.PairCard = two;
				}
				Hands.musterCorrect[twoPair] = true;
				Hands.musterCorrect[pair] = true;
			}
			else if (p1) { //detremine which is the pair
				Hands.PairCard = one;
				Hands.musterCorrect[pair] = true;
			}
			else if (p2) {
				Hands.PairCard = two;
				Hands.musterCorrect[pair] = true;
			}
	}
	
}



void Rules::CheckNumbers(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable)
{
	std::array<int, 13>Numbers = { 0 };
	//int two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace
	for (int i = two; i < v_none; i++)
	{
		int storage;
		storage = CheckHowManyOfAKind(CardsOnTheHand, CardsOnTheTable, i); //checks cards on the table
		//TODO: check... change Parameters
		Numbers[i] = storage;
	}

	
	if (CheckFourOfAKind(CardsOnTheHand, Numbers))
	{
		Hands.musterCorrect[fourOfAKind] = true;
		Hands.musterCorrect[threeOfAKind] = true;
		Hands.musterCorrect[pair] = true;
		Hands.musterCorrect[twoPair] = true;
	}
	CheckThreeOfAKindAndFullHouse(CardsOnTheHand, Numbers); //directlay sets bits
	CheckTwoPairAndPair(CardsOnTheHand ,Numbers); //directly sets bits

}


Rules::Rules()
{
}

Rules::~Rules()
{
}

BestHand Rules::HasWon(hand CardsOnTheHandStruct, std::array<card, 5> CardsOnTheTable)
{
	Hands = BestHand(); //reset besthand
	std::array<card, 2> CardsOnTheHand;

	Hands.musterCorrect[highCard] = true;

	CardsOnTheHand[0] = CardsOnTheHandStruct.firstCard;
	CardsOnTheHand[1] = CardsOnTheHandStruct.secondCard;

	//Determine High Card
	if (CardsOnTheHand[0].value >= CardsOnTheHand[1].value)
	{
		Hands.HighCard = CardsOnTheHand[0];		//firstCard is HighCard
	}
	else
	{
		Hands.HighCard = CardsOnTheHand[1];		//secondCard is HighCard
	}
	if (CheckNormalFlush(CardsOnTheHand, CardsOnTheTable)) { //flush
		Hands.musterCorrect[flush]=true;
	}
	if (CheckSuits(CardsOnTheHand, CardsOnTheTable)) //street
	{
		if (CheckFlush(CardsForAStreet)) //StraightFlush
		{
			if (CardsForAStreet[0].value == values(12)) //Royalflush
			{
				Hands.musterCorrect[royalFlush] = true;
				Hands.musterCorrect[straightFlush] = true;
				Hands.StraightFlushHighestCard = CardsForAStreet[0];
				Hands.StraightHighestCard = CardsForAStreet[0];
				Hands.musterCorrect[straight] = true;
			}
			else
			{
				Hands.musterCorrect[straightFlush] = true;
				Hands.StraightFlushHighestCard = CardsForAStreet[0];
				Hands.StraightHighestCard = CardsForAStreet[0];
				Hands.musterCorrect[straight] = true;
			}
		}
		else //Straight
		{
			Hands.StraightHighestCard = CardsForAStreet[0];
			Hands.musterCorrect[straight] = true;
		}
	}
	CheckNumbers(CardsOnTheHand, CardsOnTheTable);
	return Hands;
}