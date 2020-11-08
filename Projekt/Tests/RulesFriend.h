#pragma once
#include <Rules.h>
class RulesFriend :
    public Rules
{
public:
    RulesFriend();
    ~RulesFriend();
    bool NormalFlush(std::array<card, 2> CardsOnTheHand, std::array<card, 5> CardsOnTheTable);
};

