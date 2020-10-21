#include "Menue.h"
#include <iostream>
#include <Output.h>


Menue::Menue() {

}

Menue::~Menue() {

}

void Menue::Startgame() {
	int displayRules, maxPlayers = 9, nrPlayers, humanBot;
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
		std::cout << "1 = Bot; 2 = Human" << std::endl;
		std::cin >> humanBot;

		switch (humanBot) {
		case 1: {
			//Create a human player, enter name
			break;
			}
		case 2: {
			//Call function to create a bot
			break;
		}

		}
	}



}