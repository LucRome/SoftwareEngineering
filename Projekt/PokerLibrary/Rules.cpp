#include "pch.h"
#include "Rules.h"
#include <string.h>



bool Rules::CheckNormalFlush(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable)
{

	for (int j = 0; j < 2; j++)
	{

		int Counter = 1;
		for (int i = 0; i < 5; i++)
		{

			if (CardsOnTheHand[j].suit == CardsOnTheTable[i].suit)
			{
				Counter++;
			}
		}
		if (Counter >= 5)
		{
			return true;
		}
		else
		{
			Counter = 0;
		}
	}
	return false;

}








bool Rules::CheckFlush(std::array<card, 5> Cards) //used to check for Royal flush
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
			if (CardsOnTheHand[j].value == values(i) && Counter == CounterBefore)
			{
				Counter++;
				CardsForAStreet[Counter - 1] = CardsOnTheHand[j];
			}
		}
		if (Counter == CounterBefore)
		{
			for (int j = 0; j < 5; j++)
			{
				if (CardsOnTheTable[j].value == values(i) && Counter == CounterBefore)
				{
					Counter++;
					CardsForAStreet[Counter - 1] = CardsOnTheTable[j];
				}
			}
		}
		if (Counter == CounterBefore && Counter < 5)
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

bool Rules::CheckVourOfAKind(std::array<int, 13>Numbers)
{
	for (int i = 0; i < 13; i++)
	{
		if (Numbers[i] == 4)
		{
			Hands.FourOfAKindCard = values(i);
			return true;
		}
	}
	return false;
}


winTypes Rules::CheckThreeOfAKindAndFullHouse(std::array<int, 13> Numbers)
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
					return fullHouse;
				}
			}
			Hands.ThreeOfAKindCard = values(j);
			return threeOfAKind;
		}
	}
	return highCard; //None of both
}

winTypes Rules::CheckTwoPairAndPair(std::array<int, 13>Numbers)
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
					return twoPair; //nich eher 2?
				}
				Hands.PairCard = values(j);
				return pair; //1?
			}
		}
	}
	return highCard; //none
}



winTypes Rules::CheckNumbers(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable)
{
	std::array<int, 13>Numbers = { 0 };
	//int Zwei, Drei, Vier, Fuenf, Sechs, Sieben, Acht, Neun, Zehn, Bube, Dame, Koenig, Ass;
	for (int i = 0; i < 13; i++)
	{
		int Speicher;
		Speicher = CheckHowManyOfAKind(CardsOnTheHand, CardsOnTheTable, i);
		Numbers[i] = Speicher;
	}

	bool Check;
	winTypes IntCheck;
	Check = CheckVourOfAKind(Numbers);
	if (Check == true)
	{
		return fourOfAKind;
	}
	IntCheck = CheckThreeOfAKindAndFullHouse(Numbers); //CheckThreeOfAKind (old)
	if (IntCheck == fullHouse)
	{
		return fullHouse;
	}
	else if (IntCheck == threeOfAKind)
	{
		return threeOfAKind;
	}
	IntCheck = CheckTwoPairAndPair(Numbers);
	if (IntCheck == twoPair)
	{
		return twoPair;
	}
	else if (IntCheck == pair)
	{
		return pair;
	}

	return highCard;

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

	CardsOnTheHand[0] = CardsOnTheHandStruct.firstCard;
	CardsOnTheHand[1] = CardsOnTheHandStruct.secondCard;

	winTypes IntCheck;
	bool Check;
	bool Street = false;
	bool ThreeOfAKind = false;
	bool TwoPair = false;
	bool Pair = false;
	if (CardsOnTheHand[0].value >= CardsOnTheHand[1].value)
	{
		Hands.HighCard = CardsOnTheHand[0];		//Höchste Karte Rückgabe
	}
	else
	{
		Hands.HighCard = CardsOnTheHand[1];		//Höchste Karte Rückgabe
	}


	Check = CheckSuits(CardsOnTheHand, CardsOnTheTable); //street
	if (Check == true)
	{
		Check = CheckFlush(CardsForAStreet); //flush
		if (Check == true)
		{
			if (CardsForAStreet[0].value == values(12)) //Royalflush
			{
				Hands.musterCorrect[royalFlush] = true;
				//Royalflush Rückgabe
			}
			else
			{
				Hands.musterCorrect[straightFlush] = true;
				Hands.StraightFlushHighestCard = CardsForAStreet[0];
				//Straight Flush Rückgabe

			}
		}
		else
		{
			Hands.StraightHighestCard = CardsForAStreet[0];
			Street = true;
		}
	}

	IntCheck = CheckNumbers(CardsOnTheHand, CardsOnTheTable);
	if (IntCheck == fourOfAKind)
	{
		Hands.musterCorrect[fourOfAKind] = true;
		// Viererpasch Rückgabe
	}
	else if (IntCheck == fullHouse)
	{
		Hands.musterCorrect[fullHouse] = true;
		// Fullhouse Rückgabe
	}
	else if (IntCheck == ThreeOfAKind)
	{
		Hands.musterCorrect[ThreeOfAKind] = true;
	}
	else if (IntCheck == TwoPair)
	{
		Hands.musterCorrect[TwoPair] = true;
	}
	else if (IntCheck == pair)
	{
		Hands.musterCorrect[pair] = true;
	}
	Check = CheckNormalFlush(CardsOnTheHand, CardsOnTheTable);
	if (Check == true)
	{
		Hands.musterCorrect[flush] = true;
	}
	if (Street == true)
	{
		Hands.musterCorrect[straight] = true;
		// Straight Rückgabe
	}

	return Hands;
}