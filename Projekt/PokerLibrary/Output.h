#pragma once
#include <vector>
#include "Player.h"
#include "StringMaps.h"
#include <memory>
class Output
{
public:
	Output();
	~Output();
	void rulesOut();

	int userInput();

	int readChip(int value);

	void printTable(const std::vector< std::shared_ptr< Player>>& players,
		int playerNr, const std::array< card, 5>& communityCard, const chipstack& playerBid, const chipstack& pot,
		const chipstack& max_bid);
	
	void clearConsole();

	std::string cardToString(const card& card);
	std::string chipstackToStringAndSum(const chipstack& c);

private:
	StringMaps strMaps;
};