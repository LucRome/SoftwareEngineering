#pragma once
#include "CardAndSymbols.h"
#include "DeckOfCards.h"

#include <array>
class Dealer
{
public:
	Dealer();
	void refresh(); //refills the cardDeck
	std::array<card, 2> getHand(); //returns the Hand
	std::array<card, 3> getFlop(); //returns the Flop
	card getCard(); //returns single card

private:
	DeckOfCards m_deckOfCards;
};

