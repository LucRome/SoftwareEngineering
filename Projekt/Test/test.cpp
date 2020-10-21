#include "pch.h"
#include "DeckOfCards.h"

TEST(randomNumberGenerator, correctNumber) {
	DeckOfCards deck = DeckOfCards();
	int number = 1;
	int test = deck.randomNumberGenerator(number);
	EXPECT_EQ(test, 0);
}

TEST(overload, correct) {
	EXPECT_EQ(1, 1);
}
