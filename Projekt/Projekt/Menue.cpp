#include "Menue.h"
#include <iostream>
#include <Output.h>


Menue::Menue() {

}

Menue::~Menue() {

}

void Menue::Startgame() {
	int displayRules;
	int nrPlayers, humanBot;
	std::cout << "Welcome to poker" << std::endl << "Do you whant the rules to be displayed? If yes type 1" << std::endl;
	std::cin >> displayRules;
	if (displayRules == 1) {
		Output out = Output();
		out.rulesOut();
	}
	std::cout << "Please enter the number of players: " << std::endl;
	std::cin >> nrPlayers;

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