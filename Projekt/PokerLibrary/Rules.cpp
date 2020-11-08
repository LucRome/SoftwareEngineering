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
	int counterBeforeAce = 12;
	for (int i = 12; i >= 0; i--)
	{

		for (int j = 0; j < 2; j++)
		{
			if (CardsOnTheHand[j].value == values(i) && (Counter == CounterBefore || Counter==counterBeforeAce))
			{
				Counter++;
				CardsForAStreet[Counter - 1] = CardsOnTheHand[j];
			}
		}
		if (Counter == CounterBefore)
		{
			for (int j = 0; j < 5; j++)
			{
				if (CardsOnTheTable[j].value == values(i) && (Counter == CounterBefore || Counter == counterBeforeAce))
				{
					Counter++;
					CardsForAStreet[Counter - 1] = CardsOnTheTable[j];
				}
			}
		}
		if ((Counter == CounterBefore || Counter == counterBeforeAce) && Counter < 5)
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
				}
			}
			Hands.ThreeOfAKindCard = values(j);
			Hands.musterCorrect[threeOfAKind] = true;
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
	//int Zwei, Drei, Vier, Fuenf, Sechs, Sieben, Acht, Neun, Zehn, Bube, Dame, Koenig, Ass;
	for (int i = 0; i < 13; i++)
	{
		int Speicher;
		Speicher = CheckHowManyOfAKind(CardsOnTheHand, CardsOnTheTable, i);
		Numbers[i] = Speicher;
	}

	
	if (CheckFourOfAKind(Numbers))
	{
		Hands.musterCorrect[fourOfAKind] = true;
		Hands.musterCorrect[threeOfAKind] = true;
		Hands.musterCorrect[pair] = true;
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
		Hands.HighCard = CardsOnTheHand[0];		//Höchste Karte Rückgabe
	}
	else
	{
		Hands.HighCard = CardsOnTheHand[1];		//Höchste Karte Rückgabe
	}

	if (CheckSuits(CardsOnTheHand, CardsOnTheTable)) //street
	{
		if (CheckFlush(CardsForAStreet)) //StraightFlush
		{
			if (CardsForAStreet[0].value == values(12)) //Royalflush
			{
				Hands.musterCorrect[royalFlush] = true;
			}
			else
			{
				Hands.musterCorrect[straightFlush] = true;
				Hands.StraightFlushHighestCard = CardsForAStreet[0];
			}
		}
		else
		{
			Hands.StraightHighestCard = CardsForAStreet[0];
			Hands.musterCorrect[straight] = true;
		}
	}
	CheckNumbers(CardsOnTheHand, CardsOnTheTable);
	return Hands;
}