#include "Menue.h"
#include "Money.h"
#include "HumanPlayer.h"
#include <iostream>
#include <Output.h>
#include <Money.cpp>
#include <HumanPlayer.h>


Menue::Menue() {

}

Menue::~Menue() {

}

void Menue::Startgame() {

	/*  Welcome to poker
		Do you whant the rules to be displayed? If yes type 1
		
		%rules%
		
		Please enter the number of players:
		The maximum number of players is 9
		
		Should player 0...8 be a bot or a human?
		1 = Bot; 2 = Human

		Please enter a Name for player 0...8:
			%chipstack for player%
		*/
	int displayRules, maxPlayers = 9, nrPlayers, humanBot;
	std::string playerName;
	std::cout << "Welcome to poker" << std::endl << "Do you whant the rules to be displayed? If yes type 1" << std::endl;
	std::cin >> displayRules;
	if (displayRules == 1) {
		Output out = Output();
		out.rulesOut();
	}

	do {
		std::cout << "Please enter the number of players: " << std::endl << "The maximum number of players is 9" << std::endl;
		std::cin >> nrPlayers;
	} while (nrPlayers > maxPlayers);

	for (int i = 0; i < nrPlayers; i++) {
		std::cout << "Should player " << i << "be a bot or a human?" << std::endl;
		std::cout << "1 = Human; 2 = Bot" << std::endl;
		std::cin >> humanBot;
		std::cout << "Please enter a name for Player" << i << ": " << std::endl;
		std::cin >> playerName;
		
		switch (humanBot) {
		case 1: {
			//std::cout << "Human" << std::endl;
			chipstack startchips = startchips.readChipstackFromConsole();
			//HumanPlayer human = HumanPlayer(startchips, playerName);
			break;
			}
		case 2: {
			//std::cout << "Bot\n";
			//Call function to create a bot
			break;
		}
		}

	}

}