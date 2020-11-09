#include "Menue.h"
#include "Money.h"
#include "HumanPlayer.h"
#include "GameController.h"
#include <iostream>
#include <Output.h>
#include <HumanPlayer.h>
#include "DumbBot.h"


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
		Should player 1...9 be a bot or a human?
		1 = Bot; 2 = Human

		Please enter a Name for player 0...8:
			%chipstack for player%
		*/
	
	//Vektor Players:
	std::vector<std::shared_ptr<Player>>players;

	//Chipstacks 
	chipstack bigBlind, smallBlind, startchips;


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
	} while (nrPlayers > maxPlayers || nrPlayers <= 1);

	do {
		std::cout << "Please enter the table range: " << std::endl << "The minimel table range is 25000" << std::endl;
		tableRange = out.userInput();
	} while (tableRange < 25000);


	// first enterd is big blind, second small blind
	std::cout << "The first player you enter will be big blind, the second small blind.\n";

	for (int i = 0; i < nrPlayers; i++) {
		std::cout << "Should player " << (i+1) << " be a bot or a human?" << std::endl;
		std::cout << "1 = human; 2 = bot; 3 = smart bot" << std::endl;
		humanBot = out.userInput();
		std::cout << "Please enter a name for player " << (i+1) << ": " << std::endl;
		std::cin >> playerName;
		


		switch (humanBot) {
		case 1: {
			//Human player
			if (i == 0) {
				bigBlind = bigBlind.readChipstackFromConsole();
				players.push_back(std::make_shared<HumanPlayer>(bigBlind, playerName));
				break;
			}
			if (i == 1) {
				smallBlind = smallBlind.readChipstackFromConsole();
				players.push_back(std::make_shared<HumanPlayer>(smallBlind, playerName));
				break;
			}
			else {
				startchips = startchips.readChipstackFromConsole();
				players.push_back(std::make_shared<HumanPlayer>(startchips, playerName));
			}
			break;
		}
		case 2: {
			//Bot 
			if (i == 0) {
				bigBlind = bigBlind.createChipstackForBot();
				players.push_back(std::make_shared<DumbBot>(bigBlind, playerName));
				break;
			}
			if (i == 1) {
				smallBlind = smallBlind.createChipstackForBot();
				players.push_back(std::make_shared<DumbBot>(smallBlind, playerName));
				break;
			}
			else {
				startchips = startchips.createChipstackForBot();
				players.push_back(std::make_shared<DumbBot>(startchips, playerName));
				break;
			}
			break;
		}
		case 3: {
			//smart bot 
			if (i == 0) {
				bigBlind = bigBlind.createChipstackForBot();
				//Bot
				break;
			}
			if (i == 1) {
				smallBlind = smallBlind.createChipstackForBot();
				//bot
				break;
			}
			else {
				startchips = startchips.createChipstackForBot();
				//bot
				break;
			}
		}
		}



	}

	//Connection to Game Controller 
	players.shrink_to_fit();

	GameController gc = GameController(players, tableRange, bigBlind, smallBlind);
	std::shared_ptr<Player>& winner = gc.playGame();

}

