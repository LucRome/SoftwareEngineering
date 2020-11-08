#pragma once
#include <vector>
#include "Rules.h"

struct playerNBestHand;

class DrawResolver
{
public:
	void resolveDraws(std::vector<playerNBestHand>& players_besthands, winTypes drawCase);
private:
	void resolveHighCard(std::vector<playerNBestHand>& players_besthands);
	void resolvePair(std::vector<playerNBestHand>& players_besthands);
	void resolveTwoPair(std::vector<playerNBestHand>& players_besthands);
	void resolveThreeOfAKind(std::vector<playerNBestHand>& players_besthands);
	void resolveStraight(std::vector<playerNBestHand>& players_besthands);
	void resolveFlush(std::vector<playerNBestHand>& players_besthands);
	void resolvefullHouse(std::vector<playerNBestHand>& players_besthands);
	void resolveFourOfAKind(std::vector<playerNBestHand>& players_besthands);
	void resolveStraightFlush(std::vector<playerNBestHand>& players_besthands);

	bool resolveValues(std::vector<playerNBestHand>& players_besthands, values own, values opponent); //false if draw
	void eraseLastOne(std::vector<playerNBestHand>& players_besthands);
	void eraseAllButLastOne(std::vector<playerNBestHand>& players_besthands);
};

