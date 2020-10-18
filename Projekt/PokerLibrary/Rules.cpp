#include "pch.h"
#include "Rules.h"
#include <string.h>
#include "CardAndSymbols.h"

std::string ChangeCards(int i)
{
	std::string Check;
	if (i == 0)
	{
		strcpy(Check, "two");
	}
	if (i == 1)
	{
		strcpy(Check, "three");
	}
	if (i == 2)
	{
		strcpy(Check, "four");
	}
	if (i == 3)
	{
		strcpy(Check, "five");
	}
	if (i == 4)
	{
		strcpy(Check, "six");
	}
	if (i == 5)
	{
		strcpy(Check, "seven");
	}
	if (i == 6)
	{
		strcpy(Check, "eight");
	}
	if (i == 7)
	{
		strcpy(Check, "nine");
	}
	if (i == 8)
	{
		strcpy(Check, "ten");
	}
	else if (i == 9)
	{
		strcpy(Check, "jack");
	}
	else if (i == 10)
	{
		strcpy(Check, "queen");
	}
	else if (i == 11)
	{
		strcpy(Check, "king");
	}
	else if (i == 12)
	{
		strcpy(Check, "ace");
	}
	return Check;
}

bool CheckFlush(std::array<CardAndSymbols, 2> CardsOnTheHand, std::array<CardsAndSymbols, 5> CardsOnTheTable, int i, std::string suitCheck)
{
	int isTrue=0;
	std::string Check;
	strcpy(Check, ChangeCards(i));
	for (int j = 0; j < 2; j++)
	{
		if (strcmp(CardsOnTheHand[j].value, Check) && strcmp(CardsOnTheHand[j].suit, suitCheck)
		{
			isTrue++;
			if (isTrue == 4)
			{
				return true;
			}
			i++;
			return (CheckSymbol(CardsOnTheHand,CardsOnTheTable,i,suitCheck));
		}
	}
	for (int j = 0; j < 5; j++)
	{
		if (strcmp(CardsOnTheTable[j].value, Check) && strcmp(CardsOnTheTable[j].suit, suitCheck)
		{
			isTrue++;
			if (isTrue == 4)
			{
				return true;
			}
			i++;
			return (CheckSymbol(CardsOnTheHand, CardsOnTheTable, i, suitCheck));
		}
	}
	return false;

}

bool RoyalFlush(std::array<CardAndSymbols, 2> CardsOnTheHand, std::array<CardsAndSymbols, 5> CardsOnTheTable)
{
	int i;

	for (int j = 0; j < 2; j++)
	{
		if (CardsOnTheHand[j].suit == spades)
		{
			i++;
		}
	}
	for (int j = 0; j < 5; j++)
	{
		if (CardsOnTheTable[j].suit == spades)
		{
			i++;
		}
	}
	if (i >= 5)
	{
		bool Symbols;
		Symbols = CheckFlush(CardsOnTheHand, CardsOnTheTable, 8, "spades");
		if (Symbols)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool IsFlush(std::array<CardAndSymbols, 2> CardsOnTheHand, std::array<CardsAndSymbols, 5> CardsOnTheTable)
{
	bool isTrue;
	for (int j = 0; j < 4; j++)
	{
		std::string suitToCheck;
		if (j == 0)
		{
			strcpy(suitToCheck, "diamonds");
		}
		if (j == 1)
		{
			strcpy(suitToCheck, "hearts");
		}
		if (j == 2)
		{
			strcpy(suitToCheck, "clubs");
		}
		if (j == 3)
		{
			strcpy(suitToCheck, "spades");
		}
		for (int i = 0; i <= 8; i++)
		{
			isTrue=CheckFlush(CardsOnTheHand, CardsOnTheTable, i, suitToCheck);
			if (isTrue)
			{
				return true;
			}
		}
	}
	return false;
}



int HasWon(std::array<CardAndSymbols, 2> CardsOnTheHand, std::array<CardsAndSymbols, 5> CardsOnTheTable)
{

}