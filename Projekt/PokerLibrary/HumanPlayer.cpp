#include "pch.h"
#include "HumanPlayer.h"
#include <iostream>

HumanPlayer::HumanPlayer(chipstack pStartingChips, std::string pName):Player(pStartingChips,pName) {

}


outPlay HumanPlayer::play(chipstack pToCheck,std::vector<plays> pPlays) {
	int play;
	chipstack chipsOut;
	std::cout << "What do u want to do";
	for (plays i:pPlays)
	{
		switch (i)
		{
		case check:
			std::cout << " check [0]";
			break;
		case raise:
			std::cout << " raise [1]";
			break;
		case fold:
			std::cout << " fold [2]";
			break;
		default:
			break;
		}
	}
	std::cin >> play;

	switch (play)
	{
	case 0:		//check
		chipsOut = pToCheck;
		//decFromWinnings(chipsOut); done by GameController
		return {check,chipsOut};
		break;
	case 1:		//raise
		std::cout << "How much do u want to raise?";
		chipsOut = chipstack::readChipstackFromConsole();
		chipsOut = (pToCheck + chipsOut);
		//decFromWinnings(chipsOut); done by Gamecontroller
		return {raise,chipsOut };
		break;
	case 2:		//fold
		return { fold,chipsOut };
		break;
	default:
		std::cout << "Input was not recognized";
		break;
	}
}