#include "pch.h"
#include "Dealer.h"

Dealer::Dealer()
{
	refresh();
}

void Dealer::refresh()
{
	m_deckOfCards.refreshDeck();
}

std::array<card, 2> Dealer::getHand()
{
	std::array<card, 2> returnCards = {
		getCard(), getCard()
	};
	return returnCards;
}

std::array<card, 3> Dealer::getFlop()
{
	std::array<card, 3> returnCards = {
		getCard(), getCard(), getCard()
	};
	return returnCards;
}

card Dealer::getCard()
{
	return m_deckOfCards.getRandomCard();
}
