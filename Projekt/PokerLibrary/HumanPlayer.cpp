#include "pch.h"
#include "HumanPlayer.h"
#include <iostream>

HumanPlayer::HumanPlayer(card pFirstCard, card pSecondCard, chipstack pStartingChips) {
	setHand(pFirstCard, pSecondCard);
	setWinnings(pStartingChips);
}

chipstack HumanPlayer::play(chipstack pToCheck,std::vector<plays> pPlays) {
	int play;
	for (plays i:pPlays)
	{
		switch (i)
		{
		case fold:
			//ausgabe
			break;
		case check:
			break;
		case raise:
			break;
		default:
			break;
		}
	}
	std::cin >> play;

	switch (play)
	{
	case 0:		//check
		//dec 
		return {check,pToCheck};
		break;
	case 1:		//raise
		std::cout << "How much do u want to raise?"
		//Eingabe in Chipstack
			return {};
		break;
	case 2:		//fold
		return //emptyChipstack
		break;
	default:
		std::cout << "Couldn't de"
		break;
	}
}