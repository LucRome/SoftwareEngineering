#include "pch.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MockRandom.h"
#include <memory>
#include "DeckOfCards.h"
#include "Dealer.h"
#include "CardAndSymbols.h"
#include <vector>
using namespace testing;



TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(RandomNumber, number) {
	auto rnd = std::make_shared<MockRandom>();
	EXPECT_CALL(*rnd, randomNumberGenerator(_)).WillOnce(Return(15));
	int expected = 15;
	int gotten = rnd->randomNumberGenerator(3);
	EXPECT_EQ(expected, gotten);
}

TEST(RandomCard, cards) {
	auto rnd = std::make_shared<MockRandom>();
	card card1 = { diamonds, three };
	EXPECT_CALL(*rnd, getRandomCard()).WillOnce(Return(card1));
	card gotten = rnd->getRandomCard();
	EXPECT_EQ(card1.suit, gotten.suit);
}

TEST(RandomCard, number) {
	DeckOfCards cards = DeckOfCards(0);
	//auto rnd = std::make_shared<MockRandom>();
	//int expected = 3;
	//EXPECT_CALL(*rnd, randomNumberGenerator(_)).WillOnce(Return(expected));
	////EXPECT_CALL(*rnd, getRandomCard()).Times(1);
	card gotten = cards.getRandomCard();
	card expecteded = { hearts, eight };
	std::cout << gotten.value << std::endl;
	std::cout << expecteded.value << std::endl;
	EXPECT_EQ(gotten.suit, expecteded.suit);

}
	

