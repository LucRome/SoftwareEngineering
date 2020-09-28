#include "pch.h"
#include "DeckOfCards.h"
std::mt19937 mt_rand(time(NULL));


DeckOfCards::DeckOfCards()
{
    for (suits i = suits::diamonds; i <= suits::spades; i = suits(i + 1)) { 
    //Iterate over the enum values for suits
        for (values j = values::two; j <= values::ace; j = values(j + 1)) {
        //Iterate over the enum values for the values
            cardDeck.push_back({ i,j });
        }
    }
}

int DeckOfCards::randomNumberGenerator(int numberOfCards)
{
    int random = mt_rand();
    return random % numberOfCards;
}
