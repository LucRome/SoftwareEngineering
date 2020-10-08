#pragma once
#include <random>
#include <time.h>
#include <vector>
#include "CardAndSymbols.h"

class DeckOfCards
{
public:
	DeckOfCards();
	int randomNumberGenerator(int numberOfCards);

private:
	std::vector<card> cardDeck;
};
