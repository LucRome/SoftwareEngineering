#include "Menue.h"
#include "Money.h"
#include "HumanPlayer.h"
#include <iostream>
#include <Output.h>
#include <Money.cpp>
#include <HumanPlayer.h>



Output out = Output();

Menue::Menue() {

}

Menue::~Menue() {

}


void Menue::Startgame() {

	/*  Welcome to poker
		Do you whant the rules to be displayed? 0 - no, 1 - yes 

		%rules%

		Please enter the number of players:
		The maximum number of players is 9

		The first player you enter will be big blind, the second small blind.
		Should player 0...8 be a bot or a human?
		1 = Bot; 2 = Human

		Please enter a Name for player 0...8:
			%chipstack for player%
		*/

	int displayRules, maxPlayers = 9, nrPlayers, humanBot, tableRange;
	std::string playerName;
	std::cout << "Welcome to poker" << std::endl << "Do you whant the rules to be displayed? 0 - no, 1 - yes" << std::endl;
	displayRules = out.userInput();
	if (displayRules == 1) {
		out.rulesOut();
	}

	do {
		std::cout << "Please enter the number of players: " << std::endl << "The maximum number of players is 9" << std::endl;
		nrPlayers = out.userInput();
	} while (nrPlayers > maxPlayers);

	std::cout << "Please enter the table range: " << std::endl;
	tableRange = out.userInput();

	for (int i = 0; i < nrPlayers; i++) {
		// first enterd is big blind, second small blind
		std::cout << "The first player you enter will be big blind, the second small blind.\n";
		std::cout << "Should player " << i << "be a bot or a human?" << std::endl;
		std::cout << "1 = Human; 2 = Bot" << std::endl;
		humanBot = out.userInput();
		std::cout << "Please enter a name for Player" << i << ": " << std::endl;
		playerName = out.userInput();
		

		switch (humanBot) {
		case 1: {
			//std::cout << "Human" << std::endl;
			if (i == 0) {
				chipstack bigBlind = bigBlind.readChipstackFromConsole();
				HumanPlayer bigBlindPlayer = HumanPlayer(bigBlind, playerName);
			}
			if (i == 1) {

			}
			else {
				chipstack startchips = startchips.readChipstackFromConsole();
				HumanPlayer human = HumanPlayer(startchips, playerName);
			}
			break;
			}
		case 2: {
			//std::cout << "Bot\n";
			//Call function to create a bot
			break;
		}
		}

		//Connection to Game Controller 
		/*std::vector<std::shared_ptr<Player>> players;
		players.push_back(std::make_shared<HumanPlayer>(st_ch, "A"));
		players.push_back(std::make_shared<HumanPlayer>(st_ch, "B"));
		players.push_back(std::make_shared<HumanPlayer>(st_ch, "C"));
		players.push_back(std::make_shared<HumanPlayer>(st_ch, "D"));
		players.shrink_to_fit();

		GameController gc = GameController(players, 10000, bB, sB);
		std::shared_ptr<Player>& winner = gc.playGame();*/

	}

}

