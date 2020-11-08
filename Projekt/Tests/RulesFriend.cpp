#include "RulesFriend.h"

RulesFriend::RulesFriend()
	:Rules()
{
}

RulesFriend::~RulesFriend()
{
}

bool RulesFriend::NormalFlush(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable)
{
	return CheckNormalFlush(CardsOnTheHand, CardsOnTheTable);
}

bool RulesFriend::Suites(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable)
{
	return CheckSuits(CardsOnTheHand, CardsOnTheTable);
}
