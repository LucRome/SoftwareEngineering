#pragma once
#include "Player.h"
#include "CardAndSymbols.h"
#include "Money.h"
#include "Output.h"

class HumanPlayer: public Player{
public:
	HumanPlayer(chipstack pStartingChips,std::string pName);
	outPlay play(chipstack pToCheck, std::vector<plays> pPlays) override;
private:
	Output out = Output();
};
