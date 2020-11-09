#include "Menue.h"
#include "Money.h"
#include "HumanPlayer.h"
#include "GameController.h"
#include <iostream>
#include <string>
#include <Output.h>
#include <Money.cpp>
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

	// Variabels for menue 
	int displayRules, maxPlayers = 9, nrPlayers, humanBot, tableRange, nameBot, k = 1;;
	std::string playerName;


	std::cout << "Welcome to poker" << std::endl << "Do you whant the rules to be displayed? no = 0, yes = 1" << std::endl;
	displayRules = out.userInput();
	if (displayRules == 1) {
		out.rulesOut();
	}

	// Clear Console befor game starts, Comment out not needed os
	// Windows
	system("pause");

	//Linux
	//system("read");

	out.clearConsole();


	//Number of player will be enterd
	do {
		std::cout << "Please enter the number of players: " << std::endl << "The maximum number of players is 9" << std::endl;
		nrPlayers = out.userInput();
	} while (nrPlayers > maxPlayers || nrPlayers <= 1);

	//Table range will be entered
	do {
		std::cout << "Please enter the table range: " << std::endl << "The minimal table range is 25000" << std::endl;
		tableRange = out.userInput();
	} while (tableRange < 25000);


	// first enterd is big blind, second small blind
	std::cout << "The first player you enter will be big blind, the second small blind.\n";

	//Create Players, Bots
	for (int i = 0; i < nrPlayers; i++) {
		std::cout << "Should player " << (i+1) << " be a bot or a human?" << std::endl;
		std::cout << "1 = human; 2 = bot" << std::endl;
		humanBot = out.userInput();

		//naming Bot or not 
		if (humanBot != 1) {
			std::cout << "Du you whant to name the bot? 1 = yes, 2 = no" << std::endl;
			nameBot = out.userInput();
			// default name for bot
			if (nameBot == 2) {
				std::string s = std::to_string(k);
				playerName = "Bot" + s;
				k++;
			}
		}

		//naming players
		if (humanBot == 1 || nameBot == 1) {
			std::cout << "Please enter a name for player " << (i + 1) << ": " << std::endl;
			std::cin >> playerName;
		}

		//chipstack and array players
		switch (humanBot) {
		//Human player
		case 1: {
			//big bilnd
			if (i == 0) {
				bigBlind = bigBlind.readChipstackFromConsole();
				players.push_back(std::make_shared<HumanPlayer>(bigBlind, playerName));
				break;
			}
			//small blind
			if (i == 1) {
				smallBlind = smallBlind.readChipstackFromConsole();
				players.push_back(std::make_shared<HumanPlayer>(smallBlind, playerName));
				break;
			}
			//other players
			else {
				startchips = startchips.readChipstackFromConsole();
				players.push_back(std::make_shared<HumanPlayer>(startchips, playerName));
			}
			break;
		}
		//Bot 
		case 2: {
			//big blind
			if (i == 0) {
				bigBlind = bigBlind.createChipstackForBot();
				players.push_back(std::make_shared<DumbBot>(bigBlind, playerName));
				break;
			}
			//small blind
			if (i == 1) {
				smallBlind = smallBlind.createChipstackForBot();
				players.push_back(std::make_shared<DumbBot>(smallBlind, playerName));
				break;
			}
			//other
			else {
				startchips = startchips.createChipstackForBot();
				players.push_back(std::make_shared<DumbBot>(startchips, playerName));
				break;
			}
			break;
		}
		}
	}

	//Connection to Game Controller 
	players.shrink_to_fit();

	//start game
	GameController gc = GameController(players, tableRange, bigBlind, smallBlind);
	std::shared_ptr<Player>& winner = gc.playGame();

}