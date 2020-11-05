#pragma once
#include <random>
#include <time.h>
#include <vector>
#include "CardAndSymbols.h"

class DeckOfCards
{
public:
	DeckOfCards();
	DeckOfCards(int seed);
	virtual ~DeckOfCards();
	virtual int randomNumberGenerator(int numberOfCards);
	virtual card getRandomCard();
	void refreshDeck();

protected:
	void fillDeck();
private:
	std::vector<card> m_cardDeck;
};

