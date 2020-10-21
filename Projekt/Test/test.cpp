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


//Tests Luca:
TEST(randomNumberGenerator, positive) {
	DeckOfCards deck = DeckOfCards();
	bool pos = true;
	for (int i = 0; i < 30; i++) {
		if (deck.randomNumberGenerator(52) < 0) {
			pos = false;
		}
	}
	EXPECT_TRUE(pos);
}