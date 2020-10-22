#include "pch.h"
#include "DeckOfCards.h"
std::mt19937 mt_rand(time(NULL));


DeckOfCards::DeckOfCards()
{
    fillDeck();
}

int DeckOfCards::randomNumberGenerator(int numberOfCards)
{
    int random = mt_rand();
    random = std::abs(random); //make positive
    return random % numberOfCards;
}

card DeckOfCards::getRandomCard()
{
    int cardNr = randomNumberGenerator(m_cardDeck.size());
    card returnCard = m_cardDeck[cardNr];
    //maybe: first swap with last element, then pop_back -> faster?
    m_cardDeck.erase(m_cardDeck.begin() + cardNr);
    return returnCard;
}

void DeckOfCards::refreshDeck()
{
    m_cardDeck.clear();
    fillDeck();
}

void DeckOfCards::fillDeck()
{
    for (suits i = suits::diamonds; i <= suits::spades; i = suits(i + 1)) {
        //Iterate over the enum values for suits
        for (values j = values::two; j <= values::ace; j = values(j + 1)) {
            //Iterate over the enum values for the values
            m_cardDeck.push_back({ i,j });
        }
    }
    m_cardDeck.shrink_to_fit(); //reduces Vector size to not block unused memory
}
