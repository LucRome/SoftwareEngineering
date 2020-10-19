#pragma once
#include "Player.h"
#include "CardAndSymbols.h"
#include "Money.h"

class HumanPlayer: Player{
public:
	HumanPlayer();
	chipstack play(chipstack pToCheck, std::vector<plays> pPlays) override;
private:
};
