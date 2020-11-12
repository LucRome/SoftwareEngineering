#include "pch.h"
#include "DumbBot.h"
#include "Rnd.h"


DumbBot::DumbBot(chipstack pStartingChips, std::string pName)
	:Player(pStartingChips, pName)
{
}




outPlay DumbBot::play(chipstack pToCheck, std::vector<plays> pPlays)
{
	
	outPlay outP;
	outP.play = detPlay(pPlays);

	switch (outP.play)
	{
	case fold:
		break;
	case check:
		outP.chips = pToCheck;
		break;
	case raise:
		outP.chips = randomRaiseChipstack(pToCheck);
	default:
		break;
	}
	return outP;
}

chipstack DumbBot::randomRaiseChipstack(chipstack pToCheck) const
{
	chipstack posible = getWinnings() - pToCheck;
	chipstack out;
	/*Randomly fill chipstack*/
	for (int i = 0; i < nr_chipvalues; i++) {
		out.m_chips[i] = random(posible.m_chips[i]);
	}
	return out;
}

int DumbBot::random(int max) const {
	return randomNr(max);
}


/*probabilities for actions * 100*/
constexpr int p_fold = 2;
constexpr int p_check = 90;
constexpr int p_raise = 8;

plays DumbBot::detPlay(std::vector<plays>& pPlays) const
{
	std::array<int, 3> pos = { 0 }; //possibilites are added (this array shows the top borders for each play)
	int top = 0; //aktuelle top
	int i = 0;
	for (plays p : pPlays) {
		switch (p) {
		case fold:
			top += p_fold;
			pos[i] = top;
			break;
		case check:
			top += p_check;
			pos[i] = top;
			break;
		case raise:
			top += p_raise;
			pos[i] = top;
			break;
		}
		i++;
	}

	//Determine your play
	int rnd = random(top);
	plays pl = fold;
	for (int i = 0; i < pPlays.size(); i++) {
		if (rnd < pos[i]) {
			pl = pPlays[i];
			break; //iterate until you found the roof
		}
	}
	return pl;
}
