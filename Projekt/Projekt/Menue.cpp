#include "Menue.h"
#include <iostream>


void Menue() {
	char displayRules, humanBot;
	int nrPlayers;
	std::cout << "Welcome to poker" << std::endl << "Do you whant the rules to be displayed? If yes type y" << std::endl;
	std::cin >> displayRules;
	if (displayRules == 'y') {
		//call function to print rules
		std::cout << "rules:";
	}
	std::cout << "Please enter the number of players: ";
	std::cin >> nrPlayers;
	std::cout << "Do you have friends to play with or do you whant to play against the bot? [f/b]" << std::endl;
	std::cin >> humanBot;



}