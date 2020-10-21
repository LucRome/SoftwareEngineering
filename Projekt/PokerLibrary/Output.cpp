#include "pch.h"
#include "Output.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "StringMaps.h"



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
	std::cin >> amount;
	return amount;
}

void Output::printTable(const std::vector< std::shared_ptr< Player>>& players,
	int playerIndex, const std::array< card, 5>& communityCard,const chipstack& playerBid, const chipstack& pot,
	const chipstack& max_bid)
{
	clearConsole();

	/*	Your turn player xy (1)

		hand: {} (2)
		community cards: {} (3)

		your Bid: {} (sum: ) (4)
		highest Bid: {} (sum: ) (5)
		Pot: {} (sum: ) (6)

		your Money: {} (sum: ) (7)

		other Players: (8)
			xy: 12€ (sum) (9)
			xy: 12€ (sum) (10)
	*/
	//(1)
	std::cout << "Your turn player " << players[playerIndex]->getName() << std::endl << std::endl;
	//(2)
	hand h = players[playerIndex]->getHand();
	std::cout << "\thand: {" << cardToString(h.firstCard) << ", " << cardToString(h.secondCard) << "}" << std::endl;
	//(3)
	std::cout << "\tcommunity cards: { ";
	for (card c : communityCard) {
		std::cout << cardToString(c) << " ";
	}
	std::cout << std::endl << std::endl;
	//(4)
	std::cout << "\tyour Bid: " << chipstackToStringAndSum(playerBid) << std::endl;
	//(5)
	std::cout << "\thighest Bid: " << chipstackToStringAndSum(max_bid) << std::endl;
	//(6)
	std::cout << "\tPot: " << chipstackToStringAndSum(pot) << std::endl;
	//(7)
	std::cout << "\tyour Money: " << chipstackToStringAndSum(players[playerIndex]->getWinnings()) << std::endl << std::endl;
	//(8)
	std::cout << "\tother Players: " << std::endl;
	//(9),(10),...
	for (int i = 0; i < players.size(); i++) {
		if (i != playerIndex) {
			std::cout << "\t\t" << players[i]->getName() << ": " << chipstackToStringAndSum(players[i]->getWinnings()) << std::endl;
		}
	}
}

void Output::clearConsole()
{
	system("CLS");
}

std::string Output::cardToString(const card& card)
{
	std::string s = "[";
	s += strMaps.suit_string(card.suit);
	s += ": ";
	s += strMaps.value_string(card.value);
	s += "]";
	return s;
}

std::string Output::chipstackToStringAndSum(const chipstack& c)
{
	std::string s = c.toString();
	s += " (sum: ";
	s += c.sum();
	s += ")";
	return s;
}
