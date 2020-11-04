#include "pch.h"
#include "Rules.h"
#include <string.h>



Rules:: bool CheckNormalFlush(std::array<CardAndSymbols, 2> CardsOnTheHand, std::array<CardsAndSymbols, 5> CardsOnTheTable)
{
	
	for (int j = 0; j < 2; j++)
	{
		
		int Counter = 1;
		for (int i = 0; i < 5; i++)
		{

			if ( CardsOnTheHand[j].suits == CardsOnTheTable[i].suits)
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
			Counter=0;
		}
	}
	return false;
	
}








Rules:: bool CheckFlush(std::array<CardAndSymbols, 5> Cards)
{
	suits Check;
	Check = Cards[i].suits();
	int Counter = 1;
	for (int i = 0; i < 5; i++)
	{

		if (Check == CardsOnTheTable[h].suits())
		{
			Counter++;

		}
	}
	if(Counter >= 5)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Rules:: bool CheckSuits(std::array<CardAndSymbols, 2> CardsOnTheHand, std::array<CardsAndSymbols, 5> CardsOnTheTable)
{
	values Check;
	int Counter=0;
	int CounterBefore = 0;
	for (int i = 12; i>=0 ; i--)
	{

		for (int j = 0; j < 2; j++)
		{
			if (CardsOnTheHand[j].values == values(i) && Counter == CounterBefore)
			{
				Counter++;
				CardsForAStreet[Counter - 1] = CardsOnTheHand[j];
			}
		}
		if (Counter == CounterBefore)
		{
			for (int j = 0; j < 5; j++)
			{
				if (CardsOnTheTable[j].values() == values(i) && Counter == CounterBefore)
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
		else if(Counter<5)
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

Rueles:: int CheckHowManyOfAKind(std::array<CardAndSymbols, 2> CardsOnTheHand, std::array<CardsAndSymbols, 5> CardsOnTheTable,int i)
{
	int Counter;
	for (int j = 0; j < 2; j++)
	{
		if (CardsOnTheHand[j].values == values(i))
		{
			Counter++;
		}
	}
	for (int j = 0; j < 5; j++)
	{
		if (CardsOnTheTable[j].values == values(i))
		{
			Counter++;
		}
	}
	return Counter;
}

Rules:: bool CheckVourOfAKind(int Zwei, int Drei, int Vier, int Fuenf, int Sechs, int Sieben, int Acht, int Neun, int Zehn, int Bube, int Dame, int Koenig, int Ass)
{
	if (Zwei == 4 || Drei == 4 || Vier == 4 || Fuenf == 4 || Sechs == 4 || Sieben == 4 || Acht == 4 || Neun == 4 || Zehn == 4 || Bube == 4 || Dame == 4 || Koenig == 4 || Ass == 4)
	{
		return true;
	}
	return false;
}

Rules:: int CheckThreeOfAKindAndFullHouse(int Zwei, int Drei, int Vier, int Fuenf, int Sechs, int Sieben, int Acht, int Neun, int Zehn, int Bube, int Dame, int Koenig, int Ass)
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
}

Rules:: int CheckTwoPairAndPair(int Zwei, int Drei, int Vier, int Fuenf, int Sechs, int Sieben, int Acht, int Neun, int Zehn, int Bube, int Dame, int Koenig, int Ass)
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
}



Rules:: int CheckNumbers(std::array<CardAndSymbols, 2> CardsOnTheHand, std::array<CardsAndSymbols, 5> CardsOnTheTable)
{
	int Zwei, Drei, Vier, Fuenf, Sechs, Sieben, Acht, Neun, Zehn, Bube, Dame, Koenig, Ass;
	for (int i = 0; i < 13; i++)
	{
		int Speicher;
		Speicher = CheckHowManyOfAKind(std::array<CardAndSymbols, 2> CardsOnTheHand, std::array<CardsAndSymbols, 5> CardsOnTheTable, i);
	    
		if (i = 0)
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
		}
	}
	
	bool Check;
	int IntCheck
	Check = CheckVourOfAKind(Zwei, Drei, Vier, Fuenf, Sechs, Sieben, Acht, Neun, Zehn, Bube, Dame, Koenig, Ass);
	if (Check == true)
	{
		return 1;
	}
	IntCheck = CheckThreeOfAKind(Zwei, Drei, Vier, Fuenf, Sechs, Sieben, Acht, Neun, Zehn, Bube, Dame, Koenig, Ass);
	if (IntCheck == 1)
	{
		return 2;
	}
	else if (IntCheck == 2)
	{
		return 3;
	}
	IntCheck = CheckTwoPairAndPair(Zwei, Drei, Vier, Fuenf, Sechs, Sieben, Acht, Neun, Zehn, Bube, Dame, Koenig, Ass);
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


Rules::int HasWon(std::array<CardAndSymbols, 2> CardsOnTheHand, std::array<CardsAndSymbols, 5> CardsOnTheTable)
{
	int IntCheck;
	bool Check;
	bool Street == false; bool ThreeOfAKind = false; bool TwoPair = false, Pair = false;
	CardsAndSymbols HighestCardOnTheHand;
	if (CardsOnTheHand[0].values >= CardsOnTheHand[1].values)
	{
		HighestCardOnTheHand = CardsOnTheHand[0];
	}
	else
	{
		HighestCardOnTheHand = CardsOnTheHand[1];
	}


	Check = CheckSuits(CardsOnTheHand, CardsOnTheTable);
	if (Check == true)
	{
		Check = CheckFlush(CardsForAStreet);
		if (Check == true)
		{
			if (CardsForAStreet[0].values() == values[12])
			{


				//Royalflush Rückgabe



			}
			else
			{

				//Flush Rückgabe


			}
		}
		else
		{
			Street == true;
		}
	}

	IntCheck = CheckNumbers(CardsOnTheHand, CardsOnTheTable);
	if (IntCheck == 1)
	{
		// Viererpasch Rückgabe
	}
	else if (IntCheck == 2)
	{
		// Fullhouse Rückgabe
	}
	else if (IntCheck == 3)
	{
		ThreeOfAKind = true;
	}
	else if (Intcheck == 4)
	{
		TwoPair = true;
	}
	else if (IntCheck == 5)
	{
		Pair = true;
	}
	Check = CheckNormalFlush(CardsOnTheHand, CardsOnTheTable);
	if (Check == true)
	{
		// Flush Rückgabe
	}
	if (Street == true)
	{
		// Straight Rückgabe
	}
	if (ThreeOfAKind == true)
	{
		//Three of A Kind Rückgabe
	}
	if (TwoPair == true)
	{
		//Two Pair Rückgabe
	}
	if (Pair == true)
	{
		//Pair Rückgabe
	}
	//Höchste Karte Rückgabe
}