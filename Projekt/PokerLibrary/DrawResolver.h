#pragma once
#include <vector>
#include "Rules.h"

struct playerNBestHand;

class DrawResolver
{
public:
	//manipulates players_besthands -> void
	void resolveDraws(std::vector<playerNBestHand>& players_besthands, winTypes drawCase);
private:
	//different mechanisms for different winTypes
	void resolveHighCard(std::vector<playerNBestHand>& players_besthands);
	void resolvePair(std::vector<playerNBestHand>& players_besthands);
	void resolveTwoPair(std::vector<playerNBestHand>& players_besthands);
	void resolveThreeOfAKind(std::vector<playerNBestHand>& players_besthands);
	void resolveStraight(std::vector<playerNBestHand>& players_besthands);
	void resolveFlush(std::vector<playerNBestHand>& players_besthands);
	void resolvefullHouse(std::vector<playerNBestHand>& players_besthands);
	void resolveFourOfAKind(std::vector<playerNBestHand>& players_besthands);
	void resolveStraightFlush(std::vector<playerNBestHand>& players_besthands);

	//just resolve by the two values
	bool resolveValues(std::vector<playerNBestHand>& players_besthands, values own, values opponent); //false if draw
	//remove all players that "lost"
	void eraseLastOne(std::vector<playerNBestHand>& players_besthands);
	void eraseAllButLastOne(std::vector<playerNBestHand>& players_besthands);
};

