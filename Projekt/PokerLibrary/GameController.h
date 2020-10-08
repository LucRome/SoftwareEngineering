#pragma once
#include<memory>
#include "Player.h"
#include "DeckOfCards.h"

class GameController
{
public:
	GameController();
	void playGame(); //R�ckgabetyp ben�tigt, f�r Gewinner

private:
	DeckOfCards deckOfCards;
	std::vector<std::shared_ptr<Player>> players;
};

