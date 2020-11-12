#include "pch.h"
#include "HumanPlayer.h"
#include <iostream>
#include "Output.h"

HumanPlayer::HumanPlayer(chipstack pStartingChips, std::string pName):Player(pStartingChips,pName) {

}


outPlay HumanPlayer::play(chipstack pToCheck,std::vector<plays> pPlays) {
	int play;
	chipstack chipsOut;
	std::cout << "What do you want to do";

	for (plays i:pPlays)
	{
		switch (i)
		{
		case fold:
			std::cout << " fold [0]";
			break;
		case check:
			std::cout << " check [1]";
			break;
		case raise:
			std::cout << " raise [2]";
			break;
		default:
			break;
		}
	}

	play = out.userInput();
	if (play != 0 && play != 1 && play != 2) {
		do {
			std::cout << "Invalid input please try again" << std::endl;
			play = out.userInput();
		} while (play != 0 && play != 1 && play != 2);
	}



	switch (play)
	{
	case 1:		//check
		chipsOut = pToCheck;
		//decFromWinnings(chipsOut); done by GameController
		return {check,chipsOut};
		break;
	case 2:		//raise
		std::cout << "How much do u want to raise?";
		chipsOut = chipstack::readChipstackFromConsole();
		chipsOut = (pToCheck + chipsOut);
		//decFromWinnings(chipsOut); done by Gamecontroller
		return {raise,chipsOut };
		break;
	case 0:		//fold
		return { fold,chipsOut };
		break;
	default:
		std::cout << "Input was not recognized";
		break;
	}
}