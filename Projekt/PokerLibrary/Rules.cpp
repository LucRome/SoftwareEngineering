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
	/*for (int i = 0; i < 5; i++)
	{

		if (Check == Cards[h].suits())
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
		return false;
	}*/
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

/*Rules:: bool CheckVourOfAKind(int Zwei, int Drei, int Vier, int Fuenf, int Sechs, int Sieben, int Acht, int Neun, int Zehn, int Bube, int Dame, int Koenig, int Ass)
{
	if (Zwei == 4 || Drei == 4 || Vier == 4 || Fuenf == 4 || Sechs == 4 || Sieben == 4 || Acht == 4 || Neun == 4 || Zehn == 4 || Bube == 4 || Dame == 4 || Koenig == 4 || Ass == 4)
	{
		return true;
	}

	return false;
}*/

bool Rules::CheckVourOfAKind(std::array<int, 13>Numbers)
{
	for (int i = 0; i < 13; i++)
	{
		if (Numbers[i] = 4)
		{
			Hands.FourOfAKindCard = values(i);
			return true;
		}
	}
	return 0;
}



/*Rules:: int CheckThreeOfAKindAndFullHouse(int Zwei, int Drei, int Vier, int Fuenf, int Sechs, int Sieben, int Acht, int Neun, int Zehn, int Bube, int Dame, int Koenig, int Ass)
{
	if (Zwei == 3)
	{
		if (Drei >= 2 || Vier >= 2 || Fuenf >= 2 || Sechs >= 2 || Sieben >= 2 || Acht >= 2 || Neun >= 2 || Zehn >= 2 || Bube >= 2 || Dame >= 2 || Koenig >= 2 || Ass >= 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Drei == 3)
	{
		if (Zwei >= 2 || Vier >= 2 || Fuenf >= 2 || Sechs >= 2 || Sieben >= 2 || Acht >= 2 || Neun >= 2 || Zehn >= 2 || Bube >= 2 || Dame >= 2 || Koenig >= 2 || Ass >= 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Vier == 3)
	{
		if (Drei >= 2 || Zwei >= 2 || Fuenf >= 2 || Sechs >= 2 || Sieben >= 2 || Acht >= 2 || Neun >= 2 || Zehn >= 2 || Bube >= 2 || Dame >= 2 || Koenig >= 2 || Ass >= 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Fuenf == 3)
	{
		if (Drei >= 2 || Vier >= 2 || Zwei >= 2 || Sechs >= 2 || Sieben >= 2 || Acht >= 2 || Neun >= 2 || Zehn >= 2 || Bube >= 2 || Dame >= 2 || Koenig >= 2 || Ass >= 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Sechs == 3)
	{
		if (Drei >= 2 || Vier >= 2 || Fuenf >= 2 || Zwei >= 2 || Sieben >= 2 || Acht >= 2 || Neun >= 2 || Zehn >= 2 || Bube >= 2 || Dame >= 2 || Koenig >= 2 || Ass >= 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Sieben == 3)
	{
		if (Drei >= 2 || Vier >= 2 || Fuenf >= 2 || Sechs >= 2 || Zwei >= 2 || Acht >= 2 || Neun >= 2 || Zehn >= 2 || Bube >= 2 || Dame >= 2 || Koenig >= 2 || Ass >= 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Acht == 3)
	{
		if (Drei >= 2 || Vier >= 2 || Fuenf >= 2 || Sechs >= 2 || Sieben >= 2 || Zwei >= 2 || Neun >= 2 || Zehn >= 2 || Bube >= 2 || Dame >= 2 || Koenig >= 2 || Ass >= 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Neun == 3)
	{
		if (Drei >= 2 || Vier >= 2 || Fuenf >= 2 || Sechs >= 2 || Sieben >= 2 || Acht >= 2 || Zwei >= 2 || Zehn >= 2 || Bube >= 2 || Dame >= 2 || Koenig >= 2 || Ass >= 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Zehn == 3)
	{
		if (Drei >= 2 || Vier >= 2 || Fuenf >= 2 || Sechs >= 2 || Sieben >= 2 || Acht >= 2 || Neun >= 2 || Zwei >= 2 || Bube >= 2 || Dame >= 2 || Koenig >= 2 || Ass >= 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Bube == 3)
	{
		if (Drei >= 2 || Vier >= 2 || Fuenf >= 2 || Sechs >= 2 || Sieben >= 2 || Acht >= 2 || Neun >= 2 || Zehn >= 2 || Zwei >= 2 || Dame >= 2 || Koenig >= 2 || Ass >= 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Dame == 3)
	{
		if (Drei >= 2 || Vier >= 2 || Fuenf >= 2 || Sechs >= 2 || Sieben >= 2 || Acht >= 2 || Neun >= 2 || Zehn >= 2 || Bube >= 2 || Zwei >= 2 || Koenig >= 2 || Ass >= 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Koenig == 3)
	{
		if (Drei >= 2 || Vier >= 2 || Fuenf >= 2 || Sechs >= 2 || Sieben >= 2 || Acht >= 2 || Neun >= 2 || Zehn >= 2 || Bube >= 2 || Dame >= 2 || Zwei >= 2 || Ass >= 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Ass == 3)
	{
		if (Drei >= 2 || Vier >= 2 || Fuenf >= 2 || Sechs >= 2 || Sieben >= 2 || Acht >= 2 || Neun >= 2 || Zehn >= 2 || Bube >= 2 || Dame >= 2 || Koenig >= 2 || Zwei >= 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	return 0;
}*/


int Rules::CheckThreeOfAKindAndFullHouse(std::array<int, 13> Numbers)
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
					return 1;
				}
			}
			Hands.ThreeOfAKindCard = values(j);
			return 2;
		}
	}
	return 0;
}




/*Rules:: int CheckTwoPairAndPair(int Zwei, int Drei, int Vier, int Fuenf, int Sechs, int Sieben, int Acht, int Neun, int Zehn, int Bube, int Dame, int Koenig, int Ass)
{
	if (Zwei == 2)
	{
		if (Drei == 2 || Vier == 2 || Fuenf == 2 || Sechs == 2 || Sieben == 2 || Acht == 2 || Neun == 2 || Zehn == 2 || Bube == 2 || Dame == 2 || Koenig == 2 || Ass == 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Drei == 2)
	{
		if (Zwei == 2 || Vier == 2 || Fuenf == 2 || Sechs == 2 || Sieben == 2 || Acht == 2 || Neun == 2 || Zehn == 2 || Bube == 2 || Dame == 2 || Koenig == 2 || Ass == 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Vier == 2)
	{
		if (Zwei == 2 || Drei == 2 || Fuenf == 2 || Sechs == 2 || Sieben == 2 || Acht == 2 || Neun == 2 || Zehn == 2 || Bube == 2 || Dame == 2 || Koenig == 2 || Ass == 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Fuenf == 2)
	{
		if (Drei == 2 || Vier == 2 || Zwei == 2 || Sechs == 2 || Sieben == 2 || Acht == 2 || Neun == 2 || Zehn == 2 || Bube == 2 || Dame == 2 || Koenig == 2 || Ass == 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Sechs == 2)
	{
		if (Drei == 2 || Vier == 2 || Fuenf == 2 || Zwei == 2 || Sieben == 2 || Acht == 2 || Neun == 2 || Zehn == 2 || Bube == 2 || Dame == 2 || Koenig == 2 || Ass == 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Sieben == 2)
	{
		if (Drei == 2 || Vier == 2 || Fuenf == 2 || Sechs == 2 || Zwei == 2 || Acht == 2 || Neun == 2 || Zehn == 2 || Bube == 2 || Dame == 2 || Koenig == 2 || Ass == 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Acht == 2)
	{
		if (Drei == 2 || Vier == 2 || Fuenf == 2 || Sechs == 2 || Sieben == 2 || Zwei == 2 || Neun == 2 || Zehn == 2 || Bube == 2 || Dame == 2 || Koenig == 2 || Ass == 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Neun == 2)
	{
		if (Drei == 2 || Vier == 2 || Fuenf == 2 || Sechs == 2 || Sieben == 2 || Acht == 2 || Zwei == 2 || Zehn == 2 || Bube == 2 || Dame == 2 || Koenig == 2 || Ass == 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Zehn == 2)
	{
		if (Drei == 2 || Vier == 2 || Fuenf == 2 || Sechs == 2 || Sieben == 2 || Acht == 2 || Neun == 2 || Zwei == 2 || Bube == 2 || Dame == 2 || Koenig == 2 || Ass == 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Bube == 2)
	{
		if (Drei == 2 || Vier == 2 || Fuenf == 2 || Sechs == 2 || Sieben == 2 || Acht == 2 || Neun == 2 || Zehn == 2 || Zwei == 2 || Dame == 2 || Koenig == 2 || Ass == 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Dame == 2)
	{
		if (Drei == 2 || Vier == 2 || Fuenf == 2 || Sechs == 2 || Sieben == 2 || Acht == 2 || Neun == 2 || Zehn == 2 || Bube == 2 || Zwei == 2 || Koenig == 2 || Ass == 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Koenig == 2)
	{
		if (Drei == 2 || Vier == 2 || Fuenf == 2 || Sechs == 2 || Sieben == 2 || Acht == 2 || Neun == 2 || Zehn == 2 || Bube == 2 || Dame == 2 || Zwei == 2 || Ass == 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	if (Ass == 2)
	{
		if (Drei == 2 || Vier == 2 || Fuenf == 2 || Sechs == 2 || Sieben == 2 || Acht == 2 || Neun == 2 || Zehn == 2 || Bube == 2 || Dame == 2 || Koenig == 2 || Zwei == 2)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	return 0;
}*/

int Rules::CheckTwoPairAndPair(std::array<int, 13>Numbers)
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
					return 1; //nich eher 2?
				}
				Hands.PairCard = values(j);
				return 2; //1?
			}
		}
	}
	return 0;
}



int Rules::CheckNumbers(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable)
{
	std::array<int, 13>Numbers;
	//int Zwei, Drei, Vier, Fuenf, Sechs, Sieben, Acht, Neun, Zehn, Bube, Dame, Koenig, Ass;
	for (int i = 0; i < 13; i++)
	{
		int Speicher;
		Speicher = CheckHowManyOfAKind(CardsOnTheHand, CardsOnTheTable, i);
		Numbers[i] = Speicher;
		/*if (i = 0)
		{
			Zwei = Speicher;
		}
		if (i = 1)
		{
			Drei = Speicher;
		}
		if (i = 2)
		{
			Vier = Speicher;
		}
		if (i = 3)
		{
			Fuenf = Speicher;
		}
		if (i = 4)
		{
			Sechs = Speicher;
		}
		if (i = 5)
		{
			Sieben = Speicher;
		}
		if (i = 6)
		{
			Acht = Speicher;
		}
		if (i = 7)
		{
			Neun = Speicher;
		}
		if (i = 8)
		{
			Zehn = Speicher;
		}
		if (i = 9)
		{
			Bube = Speicher;
		}
		if (i = 10)
		{
			Dame = Speicher;
		}
		if (i = 11)
		{
			Koenig = Speicher;
		}
		if (i = 12)
		{
			Ass = Speicher;
		}*/
	}

	bool Check;
	int IntCheck;
	Check = CheckVourOfAKind(Numbers);
	if (Check == true)
	{
		return 1;
	}
	IntCheck = CheckThreeOfAKindAndFullHouse(Numbers); //CheckThreeOfAKind (old)
	if (IntCheck == 1)
	{
		return 2;
	}
	else if (IntCheck == 2)
	{
		return 3;
	}
	IntCheck = CheckTwoPairAndPair(Numbers);
	if (IntCheck == 1)
	{
		return 4;
	}
	else if (IntCheck == 2)
	{
		return 5;
	}

	return 0;

}


BestHand Rules::HasWon(hand CardsOnTheHandStruct, std::array<card, 5> CardsOnTheTable)
{
	std::array<card, 2> CardsOnTheHand;
	//std::array<card, 5> CardsOnTheTable;

	CardsOnTheHand[0] = CardsOnTheHandStruct.firstCard;
	CardsOnTheHand[1] = CardsOnTheHandStruct.secondCard;
	/*CardsOnTheTable[0] = CardsOnTheTable.Card1;
	CardsOnTheTable[1] = CardsOnTheTable.Card2;
	CardsOnTheTable[2] = CardsOnTheTable.Card3;
	CardsOnTheTable[3] = CardsOnTheTable.Card4;
	CardsOnTheTable[4] = CardsOnTheTable.Card5;*/


	int IntCheck;
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

				Hands.RoyalFlush = true;
				//Royalflush Rückgabe



			}
			else
			{
				Hands.StraightFlush = true;
				Hands.StraightFlushHighestCard = CardsForAStreet[0];
				//Flush Rückgabe
				//TODO: eher street?

			}
		}
		else
		{
			Hands.StraightHighestCard = CardsForAStreet[0];
			Street = true;
		}
	}

	IntCheck = CheckNumbers(CardsOnTheHand, CardsOnTheTable);
	if (IntCheck == 1)
	{
		Hands.FourOfAKind = true;
		// Viererpasch Rückgabe
	}
	else if (IntCheck == 2)
	{
		Hands.FullHouse = true;
		// Fullhouse Rückgabe
	}
	else if (IntCheck == 3)
	{
		Hands.ThreeOfAKind = true;
	}
	else if (IntCheck == 4)
	{
		Hands.TwoPair = true;
	}
	else if (IntCheck == 5)
	{
		Hands.Pair = true;
	}
	Check = CheckNormalFlush(CardsOnTheHand, CardsOnTheTable);
	if (Check == true)
	{
		Hands.Flush = true;
	}
	if (Street == true)
	{
		Hands.Straight = true;
		// Straight Rückgabe
	}

	return Hands;
}