#include "pch.h"
#include "DumbBot.h"
#include <random>
#include <time.h>

DumbBot::DumbBot(chipstack pStartingChips, std::string pName)
	:Player(pStartingChips, pName)
{
}


/*probabilities for actions * 100*/
constexpr int p_fold = 5;
constexpr int p_check = 75;
constexpr int p_raise = 20;

outPlay DumbBot::play(chipstack pToCheck, std::vector<plays> pPlays)
{
	int max_possibility = 0;
	/*add all possibilities */
}

std::mt19937 mt_rand(time(NULL));

int DumbBot::random(int max) const
{
	return mt_rand() % max;
}
