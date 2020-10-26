#include "pch.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MockRandom.h"
#include <memory>
#include "DeckOfCards.h"
#include "Dealer.h"
#include <vector>
using namespace testing;



TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(RandomNumber, eins) {
	auto rnd = std::make_shared<MockRandom>();
	EXPECT_CALL(*rnd, randomNumberGenerator(_)).WillOnce(Return(15));
	int expected = 15;
	int gotten = rnd->randomNumberGenerator(3);
	EXPECT_EQ(expected, gotten);
}
	

