#include "pch.h"
#include "Dealer.h"

Dealer::Dealer()
{
	refresh();
}

//generates a new carddeck for the dealer
void Dealer::refresh()
{
	m_deckOfCards.refreshDeck();
}

//returns 2 random cards
std::array<card, 2> Dealer::getHand()
{
	std::array<card, 2> returnCards = {
		getCard(), getCard()
	};
	return returnCards;
}

//returns 3 random cards
std::array<card, 3> Dealer::getFlop()
{
	std::array<card, 3> returnCards = {
		getCard(), getCard(), getCard()
	};
	return returnCards;
}

//returns one random card from the deck
card Dealer::getCard()
{
	return m_deckOfCards.getRandomCard();
}
