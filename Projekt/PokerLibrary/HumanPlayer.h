#pragma once
#include "Player.h"
#include "CardAndSymbols.h"
#include "Money.h"

class HumanPlayer: Player{
public:
	HumanPlayer(chipstack pStartingChips,std::string pName);
	outPlay play(chipstack pToCheck, std::vector<plays> pPlays) override;
private:
};
