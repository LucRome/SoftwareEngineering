#pragma once
#include "CardAndSymbols.h"
#include "DeckOfCards.h"

#include <array>
class Dealer
{
public:
	Dealer();
	void refresh();
	std::array<card, 2> getHand();
	std::array<card, 3> getFlop();
	card getCard();

private:
	DeckOfCards m_deckOfCards;
};

