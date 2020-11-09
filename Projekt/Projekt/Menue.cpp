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
	chipstack startchips;

	// Variabels for menue 
	int displayRules, maxPlayers = 9, nrPlayers, humanBot, tableRange, nameBot, k = 1;;
	std::string playerName;


	std::cout << "Welcome to poker" << std::endl << "Do you whant the rules to be displayed? no = 0, yes = 1" << std::endl;
	displayRules = out.userInput();
	if (displayRules == 1) {
		out.rulesOut();
	}

	// Clear Console befor game starts
	out.pause();

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
		case 1:
			startchips = startchips.readChipstackFromConsole();
			players.push_back(std::make_shared<HumanPlayer>(startchips, playerName));
			break;

		//Bot 
		case 2:
			startchips = startchips.createChipstackForBot();
			players.push_back(std::make_shared<DumbBot>(startchips, playerName));
			break;
		}
	}
	players.shrink_to_fit();

	chipstack bigBlind = chipstack({ 0,1,0,0,0,0 });
	chipstack smallBlind = chipstack({ 1,0,0,0,0,0 });

	//Ask if standardblinds or custom
	std::cout << "Bigblind: " << bigBlind.toString() << std::endl;
	std::cout << "Smallblind: " << smallBlind.toString() << std::endl;

	std::cout << "Do you want to change the blinds (yes/no : 1/0)" << std::endl;

	
	int in;
	do
	{
		in = out.userInput();
	} while (in != 0 && in != 1);
	
	if (in == 1) {
		bool blindsToBig = false;

		do {
			std::cout << "Bigblind: ";
			bigBlind = chipstack::readChipstackFromConsole();
			std::cout << "\nSmallblind: ";
			smallBlind = chipstack::readChipstackFromConsole();

			for (std::shared_ptr<Player> p : players) { //check if blinds are >10% of Players cash
				if (bigBlind.sum() * 10 > p->getWinnings().sum() || 
					smallBlind.sum() * 10 > p->getWinnings().sum()) {
					blindsToBig = true;
				}
			}
			if (blindsToBig) {
				std::cout << "Blinds are > 10% of lowest player cash, please change" << std::endl;
			}
		} while (blindsToBig);
		
	}
	//Connection to Game Controller 
	//start game
	GameController gc = GameController(players, tableRange, bigBlind, smallBlind);
	std::shared_ptr<Player>& winner = gc.playGame();

}