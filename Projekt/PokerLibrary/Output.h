#pragma once
#include <vector>
#include "Player.h"
#include "StringMaps.h"
#include "Player_Besthand_struct.h"
#include <memory>

enum winTypes;

class Output
{
public:
	Output();
	~Output();
	void rulesOut();

	int userInput();

	int readChip(int value);

	int randomChips(int value);

	void printTable(const std::vector< std::shared_ptr< Player>>& players,
		int playerNr, const std::array< card, 5>& communityCard, const chipstack& playerBid, const chipstack& pot,
		const chipstack& max_bid);

	void printShowdown(const std::vector<playerNBestHand>& playerBesthand, const chipstack& pot, std::array<card, 5> communityCards);
	winTypes getBestWinType(const BestHand& bestHand);

	void printWinners(const std::vector<playerNBestHand>& playerBesthand);

	void clearConsole();

	std::string cardToString(const card& card);
	std::string chipstackToStringAndSum(const chipstack& c);

private:
	StringMaps strMaps;
};