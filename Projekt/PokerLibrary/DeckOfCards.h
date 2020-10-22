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
	card getRandomCard();
	void refreshDeck();

private:
	void fillDeck();
	std::vector<card> m_cardDeck;
};

