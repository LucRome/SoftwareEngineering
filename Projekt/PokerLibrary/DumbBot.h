#pragma once
#include "Player.h"
#include "CardAndSymbols.h"
#include "Money.h"
class DumbBot :
    public Player
{
public:
    DumbBot(chipstack pStartingChips, std::string pName);
    outPlay play(chipstack pToCheck, std::vector<plays> pPlays) override;

private:
    int random(int max) const;
};

