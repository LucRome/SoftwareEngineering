#include "RulesFriend.h"

RulesFriend::RulesFriend()
{
}

RulesFriend::~RulesFriend()
{
}

bool RulesFriend::NormalFlush(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable)
{
	return CheckNormalFlush(CardsOnTheHand, CardsOnTheTable);
}
