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

	
	//Vektor Players:
	std::vector<std::shared_ptr<Player>>players;

	//Chipstacks 
	chipstack startchips;

	// Variabels for menue 
	// k is for bot names (nummeration)
	// in: input blinds 
	int displayRules, maxPlayers = 9, nrPlayers, humanBot, tableRange, nameBot, k = 1, in;
	std::string playerName;

	//Welcome
	std::cout << "Welcome to poker" << std::endl;

	//display rules
	do {
		std::cout << "Do you whant the rules to be displayed? no = 0, yes = 1" << std::endl;
		displayRules = out.userInput();
	} while (displayRules != 0 && displayRules !=1);

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



	//Create Players, Bots
	for (int i = 0; i < nrPlayers; i++) {
		do {
			std::cout << "Should player " << (i + 1) << " be a bot or a human?" << std::endl;
			std::cout << "0 = human; 1 = bot" << std::endl;
			humanBot = out.userInput();
		} while (humanBot != 1 && humanBot != 0);

		//naming Bot or not 
		if (humanBot != 0) {
			do {
				std::cout << "Du you whant to name the bot? 0 = yes, 1 = no" << std::endl;
				nameBot = out.userInput();
			} while (nameBot != 1 && nameBot != 0);

			// default name for bot
			if (nameBot == 1) {
				std::string s = std::to_string(k);
				playerName = "Bot" + s;
				k++;
			}
		}

		//naming players and bots (depending on users choice)
		if (humanBot == 0 || nameBot == 0) {
			std::cout << "Please enter a name for player " << (i + 1) << ": " << std::endl;
			std::cin >> playerName;
		}

		//chipstack and array players
		switch (humanBot) {
		//Human player
		case 0:
			startchips = startchips.readChipstackFromConsole();
			players.push_back(std::make_shared<HumanPlayer>(startchips, playerName));
			break;

		//Bot 
		case 1:
			startchips = startchips.createChipstackForBot();
			players.push_back(std::make_shared<DumbBot>(startchips, playerName));
			break;
		}
	}
	players.shrink_to_fit();

	//default chipstacks for blinds
	chipstack bigBlind = chipstack({ 0,1,0,0,0,0 });
	chipstack smallBlind = chipstack({ 1,0,0,0,0,0 });

	//Ask if standardblinds or custom
	std::cout << "Bigblind: " << bigBlind.toString() << std::endl;
	std::cout << "Smallblind: " << smallBlind.toString() << std::endl;

	std::cout << "Do you want to change the blinds? 0 = no, 1 = yes" << std::endl;


	do
	{
		in = out.userInput();
	} while (in != 0 && in != 1);
	
	if (in == 1) {
		bool blindsToBig = false;

		do {
			std::cout << "Bigblind: \n";
			bigBlind = chipstack::readChipstackFromConsole();
			std::cout << "\nSmallblind: \n";
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
	std::shared_ptr<Player> winner = gc.playGame();

	out.clearConsole();
	std::cout << "The winner is: " << winner->getName() << std::endl;

}