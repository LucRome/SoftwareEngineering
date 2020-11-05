#pragma once
#include "Player.h"
class BotPlayer : Player{
public:
	BotPlayer(chipstack pStartingChips, std::string pName);
	outPlay play(chipstack pToCheck, std::vector<plays> pPlays) override;
};

