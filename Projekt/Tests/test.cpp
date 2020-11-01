#include "pch.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MockRandom.h"
#include "MockPlayer.h"
#include "DeckOfCards.h"
#include "Dealer.h"
#include "GameController.h"
#include "HumanPlayer.h"
#include "GCFriend.h"
#include <vector>
#include <memory>
using namespace testing;



TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(RandomNumber, positive) {
	DeckOfCards deck = DeckOfCards();
	bool pos = true;
	for (int i = 0; i < 30; i++) {
		if (deck.randomNumberGenerator(52) < 0) {
			pos = false;
		}
	}
	EXPECT_TRUE(pos);
}

TEST(RandomNumber, correctNumber) {
	DeckOfCards deck = DeckOfCards();
	int number = 1;
	int test = deck.randomNumberGenerator(number);
	EXPECT_EQ(test, 0);
}


TEST(RandomNumber, one) {
	auto rnd = std::make_shared<MockRandom>();
	EXPECT_CALL(*rnd, randomNumberGenerator(_)).WillOnce(Return(15));
	int expected = 15;
	int gotten = rnd->randomNumberGenerator(3);
	EXPECT_EQ(expected, gotten);
}

TEST(movePlayer,  returnRaise) {
	chipstack st_ch = chipstack({ 1,1,1,1,1,1 });
	chipstack sB = chipstack({ 1,0,0,0,0,0 });
	chipstack bB = chipstack({ 2,0,0,0,0,0 });
	auto player1 = std::make_shared<MockPlayer>(st_ch, "a");
	outPlay play1 = { raise, chipstack({ 1,0,0,0,0,0 }) };
	EXPECT_CALL(*player1, play(_,_)).WillOnce(Return(play1)); 
	std::vector<std::shared_ptr<Player>> players;
	players.push_back(player1);
	GCFriend gc = GCFriend(players, 10000, bB, sB);
	EXPECT_EQ(gc.playersNextMove(0), raise);
}


TEST(allPlayersSamePot, simpleFalse) {
	chipstack st_ch = chipstack({ 1,1,1,1,1,1 });
	chipstack sB = chipstack({ 1,0,0,0,0,0 });
	chipstack bB = chipstack({ 2,0,0,0,0,0 });
	std::vector<std::shared_ptr<Player>> players;
	players.push_back(std::make_shared<MockPlayer>(st_ch, "A"));
	players.push_back(std::make_shared<MockPlayer>(st_ch, "B"));
	GCFriend gc = GCFriend(players, 10000, bB, sB);
	chipstack playerBids = chipstack({ 0,1,0,0,0,0 });
	gc.bidding(0, playerBids);
	EXPECT_EQ(gc.isPotSame(), false);
}

TEST(allPlayersSamePot, simpleTrue) {
	chipstack st_ch = chipstack({ 1,1,1,1,1,1 });
	chipstack sB = chipstack({ 1,0,0,0,0,0 });
	chipstack bB = chipstack({ 2,0,0,0,0,0 });
	std::vector<std::shared_ptr<Player>> players;
	players.push_back(std::make_shared<MockPlayer>(st_ch, "A"));
	players.push_back(std::make_shared<MockPlayer>(st_ch, "B"));
	GCFriend gc = GCFriend(players, 10000, bB, sB);
	chipstack playerBids = chipstack({ 0,1,0,0,0,0 });
	gc.bidding(0, playerBids);
	gc.bidding(1, playerBids);
	EXPECT_EQ(gc.isPotSame(), true);
}

TEST(money, simplePlus) {
	chipstack ch1 = chipstack({ 1,1,1,1,1,1 });
	chipstack ch2 = chipstack({ 0,0,0,0,0,1 });
	chipstack sum = ch1 + ch2; 
	chipstack expected = chipstack({ 1,1,1,1,1,2 });
	std::array<int, nr_chipvalues> exp = expected.m_chips; //transformation of struct chipstack back into an array
	std::array<int, nr_chipvalues> result = sum.m_chips; 
	EXPECT_EQ(exp[0], result[0]);
	EXPECT_EQ(exp[1], result[1]);
	EXPECT_EQ(exp[2], result[2]);
	EXPECT_EQ(exp[3], result[3]);
	EXPECT_EQ(exp[4], result[4]);
	EXPECT_EQ(exp[5], result[5]);
	EXPECT_EQ(exp[0], result[0]);
}

TEST(money, allPlus) {
	chipstack ch1 = chipstack({ 1,1,1,1,1,1 });
	chipstack ch2 = chipstack({ 1,3,6,12,2,1 });
	chipstack sum = ch1 + ch2;
	chipstack expected = chipstack({ 2,4,7,13,3,2 });
	std::array<int, nr_chipvalues> exp = expected.m_chips; //transformation of struct chipstack back into an array
	std::array<int, nr_chipvalues> result = sum.m_chips;
	EXPECT_EQ(exp[0], result[0]);
	EXPECT_EQ(exp[1], result[1]);
	EXPECT_EQ(exp[2], result[2]);
	EXPECT_EQ(exp[3], result[3]);
	EXPECT_EQ(exp[4], result[4]);
	EXPECT_EQ(exp[5], result[5]);
	EXPECT_EQ(exp[0], result[0]);
}

TEST(money, simpleMinus) {
	chipstack ch1 = chipstack({ 1,1,1,1,1,1 });
	chipstack ch2 = chipstack({ 0,0,0,0,0,1 });
	chipstack sum = ch1 - ch2;
	chipstack expected = chipstack({ 1,1,1,1,1,0});
	std::array<int, nr_chipvalues> exp = expected.m_chips; //transformation of struct chipstack back into an array
	std::array<int, nr_chipvalues> result = sum.m_chips;
	EXPECT_EQ(exp[0], result[0]);
	EXPECT_EQ(exp[1], result[1]);
	EXPECT_EQ(exp[2], result[2]);
	EXPECT_EQ(exp[3], result[3]);
	EXPECT_EQ(exp[4], result[4]);
	EXPECT_EQ(exp[5], result[5]);
	EXPECT_EQ(exp[0], result[0]);
}

TEST(money, allMinus) {
	chipstack ch1 = chipstack({ 12,5,44,6,3,1 });
	chipstack ch2 = chipstack({ 9,3,22,4,2,1 });
	chipstack sum = ch1 - ch2;
	chipstack expected = chipstack({ 3,2,22,2,1,0 });
	std::array<int, nr_chipvalues> exp = expected.m_chips; //transformation of struct chipstack back into an array
	std::array<int, nr_chipvalues> result = sum.m_chips;
	EXPECT_EQ(exp[0], result[0]);
	EXPECT_EQ(exp[1], result[1]);
	EXPECT_EQ(exp[2], result[2]);
	EXPECT_EQ(exp[3], result[3]);
	EXPECT_EQ(exp[4], result[4]);
	EXPECT_EQ(exp[5], result[5]);
	EXPECT_EQ(exp[0], result[0]);
}
TEST(money, minusGoesNegative) {
	chipstack ch1 = chipstack({ 12,5,44,6,3,1 });
	chipstack ch2 = chipstack({ 9,3,22,4,2,5 });
	chipstack sum = ch1 - ch2;
	chipstack expected = chipstack({ 3,2,22,2,1,-4 });
	std::array<int, nr_chipvalues> exp = expected.m_chips; //transformation of struct chipstack back into an array
	std::array<int, nr_chipvalues> result = sum.m_chips;
	EXPECT_EQ(exp[0], result[0]);
	EXPECT_EQ(exp[1], result[1]);
	EXPECT_EQ(exp[2], result[2]);
	EXPECT_EQ(exp[3], result[3]);
	EXPECT_EQ(exp[4], result[4]);
	EXPECT_EQ(exp[5], result[5]);
	EXPECT_EQ(exp[0], result[0]);
}

TEST(money, lessThanOrEqual_simpleEqual) {
	chipstack ch1 = chipstack({ 12,5,44,6,3,1 });
	chipstack ch2 = chipstack({ 12,5,44,6,3,1 });
	bool lessThanOrEqual = false;
	if (ch1 <= ch2) {
		lessThanOrEqual = true;
	}
	EXPECT_TRUE(lessThanOrEqual);
}

TEST(money, lessThanOrEqual_complexEqual) {
	chipstack ch1 = chipstack({ 12,5,44,6,3,1 });
	chipstack ch2 = chipstack({ 0,9,0,0,0,4 });
	bool lessThanOrEqual = false;
	if (ch1 <= ch2) {
		lessThanOrEqual = true;
	}
	EXPECT_TRUE(lessThanOrEqual);
}

TEST(money, lessThanOrEqual_less) {
	chipstack ch1 = chipstack({ 11,5,44,6,3,1 });
	chipstack ch2 = chipstack({ 12,5,44,6,3,1 });
	bool lessThanOrEqual = false;
	if (ch1 <= ch2) {
		lessThanOrEqual = true;
	}
	EXPECT_TRUE(lessThanOrEqual);
}

TEST(money, lessThanOrEqual_greater) {
	chipstack ch1 = chipstack({ 11,5,56,6,3,11 });
	chipstack ch2 = chipstack({ 12,5,44,6,3,1 });
	bool lessThanOrEqual = false;
	if (ch1 <= ch2) {
		lessThanOrEqual = true;
	}
	EXPECT_FALSE(lessThanOrEqual);
}

/* Following Tests for Overload Operator <
TEST(money, less_Equal) {
	chipstack ch1 = chipstack({ 12,5,44,6,3,1 });
	chipstack ch2 = chipstack({ 12,5,44,6,3,1 });
	bool less = false;
	if (ch1 < ch2) {
		less = true;
	}
	EXPECT_FALSE(less);
}

TEST(money, less_true) {
	chipstack ch1 = chipstack({ 11,5,44,6,3,1 });
	chipstack ch2 = chipstack({ 12,5,44,6,3,1 });
	bool less = false;
	if (ch1 < ch2) {
		less = true;
	}
	EXPECT_TRUE(less);
}

TEST(money, less_false) {
	chipstack ch1 = chipstack({ 12,5,56,6,3,11 });
	chipstack ch2 = chipstack({ 12,5,44,6,3,1 });
	bool less = false;
	if (ch1 < ch2) {
		less = true;
	}
	EXPECT_FALSE(less);
}
*/

/*Following Tests for Overload Operator ==
TEST(money, equal_simpleTrue) {
	chipstack ch1 = chipstack({ 12,5,44,6,3,1 });
	chipstack ch2 = chipstack({ 12,5,44,6,3,1 });
	bool equal = false;
	if (ch1 == ch2) {
		equal = true;
	}
	EXPECT_TRUE(equal);
}

TEST(money, equal_complexTrue) {
	chipstack ch1 = chipstack({ 0,9,0,0,0,4 });
	chipstack ch2 = chipstack({ 12,5,44,6,3,1 });
	bool equal = false;
	if (ch1 == ch2) {
		equal = true;
	}
	EXPECT_TRUE(equal);
}

TEST(money, equal_false) {
	chipstack ch1 = chipstack({ 11,5,44,6,3,1 });
	chipstack ch2 = chipstack({ 12,5,44,6,3,1 });
	bool equal = false;
	if (ch1 == ch2) {
		equal = true;
	}
	EXPECT_TRUE(equal);
}
*/

TEST(money, greater_Equal) {
	chipstack ch1 = chipstack({ 12,5,44,6,3,1 });
	chipstack ch2 = chipstack({ 12,5,44,6,3,1 });
	bool greater = false;
	if (ch1 > ch2) {
		greater = true;
	}
	EXPECT_FALSE(greater);
}

TEST(money, greater_false) {
	chipstack ch1 = chipstack({ 11,5,44,6,3,1 });
	chipstack ch2 = chipstack({ 12,5,44,6,3,1 });
	bool greater = false;
	if (ch1 > ch2) {
		greater = true;
	}
	EXPECT_FALSE(greater);
}

TEST(money, greater_true) {
	chipstack ch1 = chipstack({ 12,5,56,6,3,11 });
	chipstack ch2 = chipstack({ 12,5,44,6,3,1 });
	bool greater = false;
	if (ch1 > ch2) {
		greater = true;
	}
	EXPECT_TRUE(greater);
}

TEST(money, sumOperator) {
	chipstack ch1 = chipstack({ 12, 5, 44, 6, 3, 1 });
	int sum = ch1.sum();
	int expected = 2090;
	EXPECT_EQ(sum, expected);
}




//Test: GameController::playGame()
//only while menue isnt finished
//TODO: remove
//#define st_ch chipstack({1,1,1,1,1,1})
//#define sB chipstack({1,0,0,0,0,0})
//#define bB chipstack({2,0,0,0,0,0})
//
//TEST(playGame, justPlay) {
//	std::vector<std::shared_ptr<Player>> players;
//	players.push_back(std::make_shared<HumanPlayer>(st_ch, "A"));
//	players.push_back(std::make_shared<HumanPlayer>(st_ch, "B"));
//	players.push_back(std::make_shared<HumanPlayer>(st_ch, "C"));
//	players.push_back(std::make_shared<HumanPlayer>(st_ch, "D"));
//	players.shrink_to_fit();
//
//	GameController gc = GameController(players, 10000, bB, sB);
//	std::shared_ptr<Player>& winner = gc.playGame();
//	std::string s = winner->getName();
//	bool suc = s == "A";
//	EXPECT_TRUE(suc);
//}
