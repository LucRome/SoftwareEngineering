#pragma once
#include<memory>
#include "Player.h"
#include "DeckOfCards.h"

class GameController
{
public:
	GameController(std::vector<std::shared_ptr<Player>>);
	void playGame(); //Rückgabetyp benötigt, für Gewinner

private:
	DeckOfCards deckOfCards;
	std::vector<std::shared_ptr<Player>> players;
};

