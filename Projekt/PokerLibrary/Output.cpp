#include "pch.h"
#include "Output.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "StringMaps.h"
#include "DeckOfCards.h"
#include "Rnd.h"
#include "Rules.h"
#include "Player_Besthand_struct.h"


Output::Output()
{

}

Output::~Output()
{

}

void Output::rulesOut()
{
	std::ifstream file;
	file.open("Rules.txt");
	std::string line;
	while(std::getline(file, line)){
		std::cout << line << std::endl;
	}
	file.close();
}

int Output::readChip(int value)
{
	int amount;
	std::cout << "Chipvalue: " << value << std::endl;
	std::cout << "amount: ";
	amount = userInput();
	return amount;
}

//for Bot Chipstack 
int Output::randomChips(int value) {
	int amount;
	DeckOfCards random = DeckOfCards();
	amount = random.randomNumberGenerator(20);
	// amount = randomNr(20); 
	return amount;
}

//catch wrong user input (no int values and values < 0)
int Output::userInput() {
	int input;
	while ((!(std::cin >> input)) || input < 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input please try again" << std::endl;
	}
	return input;
}

void Output::printTable(const std::vector< std::shared_ptr< Player>>& players,
	int playerIndex, const std::array< card, 5>& communityCard,const chipstack& playerBid, const chipstack& pot,
	const chipstack& max_bid)
{
	clearConsole();

	/*	Your turn player xy (1)

		hand:				{} (2)
		community cards:	{} (3)

		your Bid:			{} (sum: ) (4)
		highest Bid:		{} (sum: ) (5)
		Pot:				{} (sum: ) (6)

		your Money:			{} (sum: ) (7)

		other Players: (8)
			xy: 12€ (sum) (9)
			xy: 12€ (sum) (10)
	*/
	//(1)
	std::cout << "Your turn player " << players[playerIndex]->getName() << std::endl << std::endl;
	//(2)
	hand h = players[playerIndex]->getHand();
	std::cout << "\thand:\t\t { " << cardToString(h.firstCard) << " " << cardToString(h.secondCard) << " }" << std::endl;
	//(3)
	std::cout << "\tcommunity cards: { ";
	for (card c : communityCard) {
		std::cout << cardToString(c) << " ";
	}
	std::cout <<"}" << std::endl << std::endl;
	//(4)
	std::cout << "\tyour Bid: \t" << chipstackToStringAndSum(playerBid) << std::endl;
	//(5)
	std::cout << "\thighest Bid: \t" << chipstackToStringAndSum(max_bid) << std::endl;
	//(6)
	std::cout << "\tPot: \t\t" << chipstackToStringAndSum(pot) << std::endl;
	//(7)
	std::cout << "\tyour Money: \t" << chipstackToStringAndSum(players[playerIndex]->getWinnings()) << std::endl << std::endl;
	//(8)
	std::cout << "\tother Players: " << std::endl;
	//(9),(10),...
	for (int i = 0; i < players.size(); i++) {
		if (i != playerIndex) {
			std::cout << "\t\t" << players[i]->getName() << ": \t" << chipstackToStringAndSum(players[i]->getWinnings()) << std::endl;
		}
	}
}

std::array<std::string, 10> winTypesStrings = {
	"high Card", "pair", "two Pairs", "three of a Kind", "straight", "flush", "fullHouse",
	"four of a Kind", "straightFlush", "royalFlush" };

void Output::printShowdown(const std::vector<playerNBestHand>& playerBesthand, const chipstack& pot, std::array<card, 5> communityCards)
{
	clearConsole();
	/*
	SHOWDOWN:
	*communitiy cards*	(1)
	pot: xy				(2)
	*Name*: *Besthand*	(3) (3.1)
		*cards*			(3.2)
	*Name*: *Besthand*
		*cards*
	...
	*/
	
	//(1)
	std::cout << "SHOWDOWN: \n\ncommunity cards: {";
	for (card c : communityCards) {
		std::cout << cardToString(c) << " ";
	}
	std::cout << "}" << std::endl << std::endl;
	//(2)
	std::cout << "pot: " << pot.sum() << std::endl << std::endl;
	//(3)
	for (playerNBestHand pH : playerBesthand) {
		// (3.1)
		std::cout << pH.player->getName() << ": " 
			<< winTypesStrings[getBestWinType(pH.besthand)] << std::endl;
		hand h = pH.player->getHand();
		std::cout << "\thand: { " << cardToString(h.firstCard) << " " << cardToString(h.secondCard) << " }" << std::endl;
	}

	//wait for input (otherwise it would be gone to soon)
	std::cout << "Press any key";
	char c;
	std::cin >> c;
}

winTypes Output::getBestWinType(const BestHand& bestHand)
{
	winTypes ret = highCard;
	for (int i = royalFlush; i > highCard; i--) { //high Card doesnt need to be checked
		if (bestHand.musterCorrect[i]) {
			ret = winTypes(i);
			break;
		}
	}
	return ret;
}

void Output::printWinners(const std::vector<playerNBestHand>& playerBesthand)
{
	/*
	WINNERS:
	
		*Name1*
		*Name2*
		...
	*/
	std::cout << "WINNERS: " << std::endl << std::endl;
	for (playerNBestHand p : playerBesthand) {
		std::cout << "\t" << p.player->getName() << std::endl;
	}
	//wait for input (otherwise it would be gone to soon)
	std::cout << "Press any key";
	char c;
	std::cin >> c;
}

void Output::clearConsole()
{
	
#ifdef _WIN32 // Windows
	system("CLS");
#elif __linux__ //linux
	system("clear");
#else
#error "OS not supported"
#endif
}

void Output::pause()
{
#ifdef _WIN32 // Windows
	system("pause");
#elif __linux__ //linux
	system("read");
#else
#error "OS not supported"
#endif
}

std::string Output::cardToString(const card& card)
{
	std::string s = "[";
	s.append(strMaps.suit_string(card.suit));
	s.append(": ");
	s.append(strMaps.value_string(card.value));
	s.append("]");
	return s;
}

std::string Output::chipstackToStringAndSum(const chipstack& c)
{
	std::string s = c.toString();
	s.append(" (sum: ");
	s.append(std::to_string(c.sum()));
	s.append("$)");
	return s;
}
