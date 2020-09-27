#include "pch.h"
#include "DeckOfCards.h"
std::mt19937 mt_rand(time(NULL));


int DeckOfCards::randomNumberGenerator(int numberOfCards)
{
    int random = mt_rand();
    return random % numberOfCards;
}
