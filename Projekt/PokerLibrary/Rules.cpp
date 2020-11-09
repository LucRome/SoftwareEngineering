#include "pch.h"
#include "Rules.h"
#include <string.h>



bool Rules::CheckNormalFlush(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable)
{
	std::array<card, 7> cardsInGame;
	for (int i = 0; i < 5; i++) {
		cardsInGame[i] = CardsOnTheTable[i];
	}
	cardsInGame[5] = CardsOnTheHand[0];
	cardsInGame[6] = CardsOnTheHand[1];
	for (int i = 0; i < 7; i++) {
		int counter = 1; 
		for (int j = i + 1; j < 7; j++) {
			if (cardsInGame[i].suit == cardsInGame[j].suit) {
				counter++;
			}
		}
		if (counter >= 5) {
			Hands.Flush = cardsInGame[i].suit;
			return true;
		}
		else {
			counter = 0;
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
	for (int j = 0; j < 2; j++)
	{
		if (CardsOnTheHand[j].value == values(i))
		{
			Counter++;
		}
	}
	for (int j = 0; j < 5; j++) //TODO: nur wenn auch auf Hand
	{
		if (CardsOnTheTable[j].value == values(i))
		{
			Counter++;
		}
	}
	return Counter;
}

bool Rules::CheckFourOfAKind(std::array<int, 13>Numbers)
{
	for (int i = 0; i < 13; i++)
	{
		if (Numbers[i] == 4)
		{
			Hands.FourOfAKindCard = values(i);
			Hands.ThreeOfAKindCard = values(i);
			Hands.TwoPairCards[0] = values(i);
			Hands.TwoPairCards[1] = values(i);
			Hands.PairCard = values(i);
			return true;
		}
	}
	return false;
}

//sets bits in Hands struct
void Rules::CheckThreeOfAKindAndFullHouse(std::array<int, 13> Numbers)
{
	for (int j = 0; j < 13; j++)
	{
		if (Numbers[j] == 3)
		{
			for (int i = 0; i < 13; i++)
			{
				if (Numbers[i] >= 2 && i != j)
				{
					Hands.FullHouseCards[0] = values(j);
					Hands.FullHouseCards[1] = values(i);
					Hands.musterCorrect[fullHouse] = true;
					Hands.musterCorrect[twoPair] = true;
					Hands.TwoPairCards[0] = values(j);
					Hands.TwoPairCards[1] = values(i);
				}
			}
			Hands.ThreeOfAKindCard = values(j);
			Hands.musterCorrect[threeOfAKind] = true;
			Hands.musterCorrect[pair] = true;
			Hands.PairCard = values(j);

		}
	}
}

void Rules::CheckTwoPairAndPair(std::array<int, 13>Numbers)
{
	for (int j = 0; j < 13; j++) // iterate over all values (first pair)
	{
		//TODO: improve
		if (Numbers[j] == 2)
		{
			for (int i = 0; i < 13; i++) //iterate over all values (second pair)
			{
				if (Numbers[i] == 2 && i != j)
				{
					Hands.TwoPairCards[0] = values(j);
					Hands.TwoPairCards[1] = values(i);
					Hands.musterCorrect[twoPair] = true;
				}
				Hands.PairCard = values(j);
				Hands.musterCorrect[pair] = true; //1?
			}
		}
	}
}



void Rules::CheckNumbers(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable)
{
	std::array<int, 13>Numbers = { 0 };
	//int two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace
	for (int i = 0; i < 13; i++)
	{
		int storage;
		storage = CheckHowManyOfAKind(CardsOnTheHand, CardsOnTheTable, i);
		Numbers[i] = storage;
	}

	
	if (CheckFourOfAKind(Numbers))
	{
		Hands.musterCorrect[fourOfAKind] = true;
		Hands.musterCorrect[threeOfAKind] = true;
		Hands.musterCorrect[pair] = true;
		Hands.musterCorrect[twoPair] = true;
	}
	CheckThreeOfAKindAndFullHouse(Numbers); //directlay sets bits
	CheckTwoPairAndPair(Numbers); //directly sets bits

}


Rules::Rules()
{
}

Rules::~Rules()
{
}

BestHand Rules::HasWon(hand CardsOnTheHandStruct, std::array<card, 5> CardsOnTheTable)
{
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