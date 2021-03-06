#include "pch.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MockRandom.h"
#include "MockPlayer.h"
#include "DeckOfCards.h"
#include "Dealer.h"
#include "GameController.h"
#include "HumanPlayer.h"
#include "DumbBot.h"
#include "DrawResolver.h"

#include "Rules.h"
#include "GCFriend.h"
#include <vector>
#include <array>
#include <memory>
using namespace testing;



namespace n_rules {
	Rules rl;
	//tests for Rules
	//High card
	TEST(HighCard_true, 1) {
		hand p_hand = {
			{diamonds, ace},
			{clubs, six}
		};
		card c = { hearts, three };
		card c1 = { diamonds, two };
		card c2 = { spades, queen };
		card c3 = { clubs, jack };
		card c4 = { spades, seven };
		std::array<card, 5> community = {
			c, c1, c2, c3, c4
		};
		BestHand bh = rl.HasWon(p_hand, community);
		bool right = (bh.HighCard == p_hand.firstCard);
		EXPECT_TRUE(right);
	}

	TEST(HighCard_true, 2) {
		hand p_hand = {
			{diamonds, four},
			{clubs, six}
		};
		card c = { hearts, three };
		card c1 = { diamonds, two };
		card c2 = { spades, queen };
		card c3 = { clubs, jack };
		card c4 = { spades, seven };
		std::array<card, 5> community = {
			c, c1, c2, c3, c4
		};
		BestHand bh = rl.HasWon(p_hand, community);
		bool right = (bh.HighCard == p_hand.secondCard);
		EXPECT_TRUE(right);
	}

	//Tests for Rules
//Tests the highCardPart of hasWon
	TEST(Rules, hasWon_highCard) {
		Rules rl = Rules();
		hand hand = { {spades, queen}, {spades, nine} };
		card card1 = { diamonds, two };
		card card2 = { diamonds, three };
		card card3 = { hearts, ace };
		card card4 = { clubs, jack };
		card card5 = { diamonds, seven };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		for (int i = 1; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.firstCard);
	}

	//Tests the highCardPart of hasWon when the handcards have equal values
	TEST(Rules, hasWon_highCard_equalValues) {
		Rules rl = Rules();
		hand hand = { {spades, queen}, {clubs, nine} };
		card card1 = { diamonds, two };
		card card2 = { diamonds, three };
		card card3 = { hearts, ace };
		card card4 = { clubs, jack };
		card card5 = { diamonds, seven };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		for (int i = 1; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.firstCard);
		EXPECT_FALSE(result.HighCard == hand.secondCard);
	}

	//Tests if the pairPart of hasWon recognizes a pair thats split between community and hand cards
	TEST(Rules, hasWon_Pair_handAndCommunity) {
		Rules rl = Rules();
		hand hand = { {diamonds, queen}, {hearts, two} };
		card card1 = { diamonds, two };
		card card2 = { hearts, five };
		card card3 = { clubs, jack };
		card card4 = { spades, nine };
		card card5 = { spades, seven };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_TRUE(result.musterCorrect[pair]);
		for (int i = 2; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.firstCard);
		EXPECT_EQ(result.PairCard, values::two);
	}

	//Tests if the pairPart of hasWon recognizes a pair thats only on the hand
	TEST(Rules, hasWon_Pair_onHand) {
		Rules rl = Rules();
		hand hand = { {diamonds, two}, {hearts, two} };
		card card1 = { diamonds, queen };
		card card2 = { hearts, five };
		card card3 = { clubs, jack };
		card card4 = { spades, nine };
		card card5 = { spades, seven };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_TRUE(result.musterCorrect[pair]);
		for (int i = 2; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.firstCard);
		EXPECT_EQ(result.PairCard, values::two);
	}

	//Tests if the pairPart of hasWon recognizes a pair thats only in the community cards
	TEST(Rules, hasWon_Pair_communityOnly) {
		Rules rl = Rules();
		hand hand = { {hearts, five}, {spades, seven} };
		card card1 = { diamonds, two };
		card card2 = { hearts, two };
		card card3 = { clubs, jack };
		card card4 = { spades, nine };
		card card5 = { diamonds, queen };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[pair]);
		for (int i = 2; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.secondCard);
	}

	//One Pair is in the community Cards, the other is a mix of community card and hand card
	TEST(Rules, hasWon_doublePair_1) {
		Rules rl = Rules();
		hand hand = { {hearts, four}, {diamonds, ace} };
		card card1 = { diamonds, four };
		card card2 = { hearts, two };
		card card3 = { spades, nine };
		card card4 = { clubs, two };
		card card5 = { hearts, queen };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[twoPair]);
		EXPECT_TRUE(result.musterCorrect[pair]);
		for (int i = 3; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.secondCard);
		EXPECT_EQ(result.PairCard, values::four);

	}

	//Both Pairs are in the community Cards
	TEST(Rules, hasWon_doublePair_2) {
		Rules rl = Rules();
		hand hand = { {hearts, queen}, {diamonds, ace} };
		card card1 = { diamonds, four };
		card card2 = { hearts, two };
		card card3 = { spades, nine };
		card card4 = { clubs, two };
		card card5 = { hearts, four };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[twoPair]);
		EXPECT_FALSE(result.musterCorrect[pair]);
		for (int i = 3; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.secondCard);
	}

	//One pair is in the community cards, one pair on the hand
	TEST(Rules, hasWon_doublePair_3) {
		Rules rl = Rules();
		hand hand = { {hearts, four}, {diamonds, four} };
		card card1 = { diamonds, ace };
		card card2 = { hearts, two };
		card card3 = { spades, nine };
		card card4 = { clubs, two };
		card card5 = { hearts, queen };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[twoPair]);
		EXPECT_TRUE(result.musterCorrect[pair]);
		for (int i = 3; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.firstCard);
		EXPECT_EQ(result.PairCard, values::four);
	}

	//Both pairs are split up between community cards and hand
	TEST(Rules, hasWon_doublePair_4) {
		Rules rl = Rules();
		hand hand = { {clubs, two}, {hearts, four} };
		card card1 = { diamonds, four };
		card card2 = { hearts, two };
		card card3 = { spades, nine };
		card card4 = { diamonds, ace };
		card card5 = { hearts, queen };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_TRUE(result.musterCorrect[twoPair]);
		EXPECT_TRUE(result.musterCorrect[pair]);
		for (int i = 3; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.secondCard);
		EXPECT_EQ(result.PairCard, values::four);
		EXPECT_EQ(result.TwoPairCards[0], values::four);
		EXPECT_EQ(result.TwoPairCards[1], values::two);
	}

	// three of a kind split up with between community and hand
	TEST(Rules, hasWon_threeOfAKind_1) {
		Rules rl = Rules();
		hand hand = { {hearts, three}, {diamonds, two} };
		card card1 = { hearts, two };
		card card2 = { spades, two };
		card card3 = { clubs, queen };
		card card4 = { spades, nine };
		card card5 = { clubs, ace };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[twoPair]);
		EXPECT_TRUE(result.musterCorrect[pair]);
		EXPECT_TRUE(result.musterCorrect[threeOfAKind]);
		for (int i = 4; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.firstCard);
		EXPECT_EQ(result.PairCard, values::two);
		EXPECT_EQ(result.ThreeOfAKindCard, values::two);
	}

	//three of a kind only in community
	TEST(Rules, hasWon_threeOfAKind_2) {
		Rules rl = Rules();
		hand hand = { {spades, nine}, {clubs, ace} };
		card card1 = { hearts, two };
		card card2 = { hearts, three };
		card card3 = { diamonds, two };
		card card4 = { spades, two };
		card card5 = { clubs, queen };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[twoPair]);
		EXPECT_FALSE(result.musterCorrect[pair]);
		EXPECT_FALSE(result.musterCorrect[threeOfAKind]);
		for (int i = 4; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.secondCard);
	}

	//Tests for straightPart in HasWon
	TEST(Rules, hasWon_straight_1) {
		Rules rl = Rules();
		hand hand = { {clubs, five}, {diamonds, queen} };
		card card1 = { hearts, two };
		card card2 = { clubs, three };
		card card3 = { diamonds, four };
		card card4 = { spades, six };
		card card5 = { hearts, jack };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[twoPair]);
		EXPECT_FALSE(result.musterCorrect[pair]);
		EXPECT_FALSE(result.musterCorrect[threeOfAKind]);
		EXPECT_TRUE(result.musterCorrect[straight]);
		for (int i = 5; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.secondCard);
		EXPECT_EQ(result.StraightHighestCard, card4);
	}
	//TODO: ace as start
	TEST(Rules, hasWon_straight_2) {
		Rules rl = Rules();
		hand hand = { {clubs, queen}, {diamonds, four} };
		card card1 = { hearts, two };
		card card2 = { clubs, three };
		card card3 = { spades, ace };
		card card4 = { diamonds, nine };
		card card5 = { hearts, five };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[twoPair]);
		EXPECT_FALSE(result.musterCorrect[pair]);
		EXPECT_FALSE(result.musterCorrect[threeOfAKind]);
		EXPECT_TRUE(result.musterCorrect[straight]);
		for (int i = 5; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.firstCard);
		EXPECT_EQ(result.StraightHighestCard.value, five);
	}

	//ace as last card of straight
	TEST(Rules, hasWon_straight_3) {
		Rules rl = Rules();
		hand hand = { {clubs, queen}, { hearts, ace } };
		card card1 = { diamonds, ten };
		card card2 = { spades, jack };
		card card3 = { diamonds, nine };
		card card4 = { spades, king };
		card card5 = { clubs, five };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[twoPair]);
		EXPECT_FALSE(result.musterCorrect[pair]);
		EXPECT_FALSE(result.musterCorrect[threeOfAKind]);
		EXPECT_TRUE(result.musterCorrect[straight]);
		for (int i = 5; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.secondCard);
		EXPECT_EQ(result.StraightHighestCard, hand.secondCard);
	}

	//6 cards in a row instead of only 5
	TEST(Rules, hasWon_straight_4)
	{
		Rules rl = Rules();
		hand hand = { {clubs, ten}, {hearts, ace} };
		card card1 = { hearts, five };
		card card2 = { spades, six };
		card card3 = { diamonds, seven };
		card card4 = { diamonds, eight };
		card card5 = { clubs, nine };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[twoPair]);
		EXPECT_FALSE(result.musterCorrect[pair]);
		EXPECT_FALSE(result.musterCorrect[threeOfAKind]);
		EXPECT_TRUE(result.musterCorrect[straight]);
		for (int i = 5; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.secondCard);
		EXPECT_EQ(result.StraightHighestCard, hand.firstCard);
	}

	//combined straight and doublePair
	TEST(Rules, hasWon_straight_5) {
		Rules rl = Rules();
		hand hand = { {clubs, five}, {diamonds, three} };
		card card1 = { hearts, two };
		card card2 = { clubs, three };
		card card3 = { diamonds, four };
		card card4 = { hearts, five };
		card card5 = { spades, six };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_TRUE(result.musterCorrect[twoPair]);
		EXPECT_TRUE(result.musterCorrect[pair]);
		EXPECT_FALSE(result.musterCorrect[threeOfAKind]);
		EXPECT_TRUE(result.musterCorrect[straight]);
		for (int i = 5; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.firstCard);
		EXPECT_EQ(result.PairCard, values::five);
		EXPECT_EQ(result.TwoPairCards[0], values::five);
		EXPECT_EQ(result.TwoPairCards[1], values::three);
		EXPECT_EQ(result.StraightHighestCard, card5);
	}

	//straight combined with threeOfAKind
	TEST(Rules, hasWon_straight_6) {
		Rules rl = Rules();
		hand hand = { {clubs, five}, {diamonds, five} };
		card card1 = { hearts, two };
		card card2 = { clubs, three };
		card card3 = { diamonds, four };
		card card4 = { hearts, five };
		card card5 = { spades, six };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[twoPair]);
		EXPECT_TRUE(result.musterCorrect[pair]);
		EXPECT_TRUE(result.musterCorrect[threeOfAKind]);
		EXPECT_TRUE(result.musterCorrect[straight]);
		for (int i = 5; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.firstCard);
		EXPECT_EQ(result.PairCard, values::five);
		EXPECT_EQ(result.ThreeOfAKindCard, values::five);
		EXPECT_EQ(result.StraightHighestCard, card5);
	}

	// Tests for the flushPart in HasWon
	TEST(Rules, hasWon_flush_1) {
		Rules rl = Rules();
		hand hand = { {clubs, ace}, {hearts, six} };
		card card1 = { diamonds, four };
		card card2 = { hearts, five };
		card card3 = { hearts, two };
		card card4 = { hearts, queen };
		card card5 = { hearts, jack };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[twoPair]);
		EXPECT_FALSE(result.musterCorrect[pair]);
		EXPECT_FALSE(result.musterCorrect[threeOfAKind]);
		EXPECT_FALSE(result.musterCorrect[straight]);
		EXPECT_TRUE(result.musterCorrect[flush]);
		for (int i = 6; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.firstCard);
		EXPECT_EQ(result.Flush[0].value, queen);
		EXPECT_EQ(result.Flush[1].value, jack);
		EXPECT_EQ(result.Flush[2].value, six);
		EXPECT_EQ(result.Flush[3].value, five);
		EXPECT_EQ(result.Flush[4].value, two);
	}

	//combined flush and doublePair
	TEST(Rules, hasWon_flush_2) {
		Rules rl = Rules();
		hand hand = { {clubs, jack}, { hearts, six } };
		card card1 = { diamonds, queen };
		card card2 = { hearts, five };
		card card3 = { hearts, two };
		card card4 = { hearts, queen };
		card card5 = { hearts, jack };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[twoPair]);
		EXPECT_TRUE(result.musterCorrect[pair]);
		EXPECT_FALSE(result.musterCorrect[threeOfAKind]);
		EXPECT_FALSE(result.musterCorrect[straight]);
		EXPECT_TRUE(result.musterCorrect[flush]);
		for (int i = 6; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.firstCard);
		EXPECT_EQ(result.PairCard, values::jack);
		EXPECT_EQ(result.Flush[0].value, queen);
		EXPECT_EQ(result.Flush[1].value, jack);
		EXPECT_EQ(result.Flush[2].value, six);
		EXPECT_EQ(result.Flush[3].value, five);
		EXPECT_EQ(result.Flush[4].value, two);
	}

	//combined flush and threeOfAKind
	TEST(Rules, hasWon_flush_3) {
		Rules rl = Rules();
		hand hand = { {clubs, queen},{ hearts, six } };
		card card1 = { diamonds, queen };
		card card2 = { hearts, five };
		card card3 = { hearts, two };
		card card4 = { hearts, queen };
		card card5 = { hearts, jack };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[twoPair]);
		EXPECT_TRUE(result.musterCorrect[pair]);
		EXPECT_TRUE(result.musterCorrect[threeOfAKind]);
		EXPECT_FALSE(result.musterCorrect[straight]);
		EXPECT_TRUE(result.musterCorrect[flush]);
		for (int i = 6; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.firstCard);
		EXPECT_EQ(result.PairCard, values::queen);
		EXPECT_EQ(result.ThreeOfAKindCard, values::queen);
		EXPECT_EQ(result.Flush[0].value, queen);
		EXPECT_EQ(result.Flush[1].value, jack);
		EXPECT_EQ(result.Flush[2].value, six);
		EXPECT_EQ(result.Flush[3].value, five);
		EXPECT_EQ(result.Flush[4].value, two);
	}

	//flush only in the communitycards
	TEST(Rules, hasWon_flush_4) {
		Rules rl = Rules();
		hand hand = { {clubs, ace}, { diamonds, four } };
		card card1 = { hearts, six };
		card card2 = { hearts, five };
		card card3 = { hearts, two };
		card card4 = { hearts, queen };
		card card5 = { hearts, jack };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[twoPair]);
		EXPECT_FALSE(result.musterCorrect[pair]);
		EXPECT_FALSE(result.musterCorrect[threeOfAKind]);
		EXPECT_FALSE(result.musterCorrect[straight]);
		EXPECT_FALSE(result.musterCorrect[flush]);
		for (int i = 6; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.firstCard);
	}

	//6 cards for a flush
	TEST(Rules, hasWon_flush_5) {
		Rules rl = Rules();
		hand hand = { {clubs, ace}, { hearts, four } };
		card card1 = { hearts, six };
		card card2 = { hearts, five };
		card card3 = { hearts, two };
		card card4 = { hearts, queen };
		card card5 = { hearts, jack };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[twoPair]);
		EXPECT_FALSE(result.musterCorrect[pair]);
		EXPECT_FALSE(result.musterCorrect[threeOfAKind]);
		EXPECT_FALSE(result.musterCorrect[straight]);
		EXPECT_TRUE(result.musterCorrect[flush]);
		for (int i = 6; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.firstCard);
		EXPECT_EQ(result.Flush[0].value, queen);
		EXPECT_EQ(result.Flush[1].value, jack);
		EXPECT_EQ(result.Flush[2].value, six);
		EXPECT_EQ(result.Flush[3].value, five);
		EXPECT_EQ(result.Flush[4].value, four);



	}


	//Tests for the fullHousePart in HasWon
	TEST(Rules, hasWon_fullHouse_1) {
		Rules rl = Rules();
		hand hand = { {hearts, two}, {diamonds, queen} };
		card card1 = { hearts, two };
		card card2 = { clubs, two };
		card card3 = { diamonds, ace };
		card card4 = { clubs, queen };
		card card5 = { spades, four };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_TRUE(result.musterCorrect[twoPair]);
		EXPECT_TRUE(result.musterCorrect[pair]);
		EXPECT_TRUE(result.musterCorrect[threeOfAKind]);
		EXPECT_FALSE(result.musterCorrect[straight]);
		EXPECT_TRUE(result.musterCorrect[fullHouse]);
		EXPECT_FALSE(result.musterCorrect[flush]);
		for (int i = 7; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.secondCard);
		EXPECT_EQ(result.PairCard, values::queen);
		EXPECT_EQ(result.TwoPairCards[0], values::queen);
		EXPECT_EQ(result.TwoPairCards[1], values::two);
		EXPECT_EQ(result.ThreeOfAKindCard, values::two);
		EXPECT_EQ(result.FullHouseCards[0], values::two);
		EXPECT_EQ(result.FullHouseCards[1], values::queen);
	}

	TEST(Rules, hasWon_fullHouse_2) { //3 only in community -> only a pair
		Rules rl = Rules();
		hand hand = { {hearts, ace}, {diamonds, queen} };
		card card1 = { hearts, two };
		card card2 = { clubs, two };
		card card3 = { diamonds, two };
		card card4 = { clubs, queen };
		card card5 = { spades, four };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[twoPair]);
		EXPECT_TRUE(result.musterCorrect[pair]);
		EXPECT_FALSE(result.musterCorrect[threeOfAKind]);
		EXPECT_FALSE(result.musterCorrect[straight]);
		EXPECT_FALSE(result.musterCorrect[fullHouse]);
		EXPECT_FALSE(result.musterCorrect[flush]);
		for (int i = 7; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.firstCard);
		EXPECT_EQ(result.PairCard, values::queen);
		EXPECT_EQ(result.ThreeOfAKindCard, values::two);
	}

	//Tests for the fourOfAKindPart in HasWon
	TEST(Rules, hasWon_fourOfAKind_1) {
		Rules rl = Rules();
		hand hand = { {hearts, six}, {spades, nine} };
		card card1 = { diamonds, three };
		card card2 = { hearts, three };
		card card3 = { clubs, three };
		card card4 = { spades, three };
		card card5 = { clubs, queen };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[twoPair]);
		EXPECT_FALSE(result.musterCorrect[pair]);
		EXPECT_FALSE(result.musterCorrect[threeOfAKind]);
		EXPECT_FALSE(result.musterCorrect[straight]);
		EXPECT_FALSE(result.musterCorrect[fullHouse]);
		EXPECT_FALSE(result.musterCorrect[flush]);
		EXPECT_FALSE(result.musterCorrect[fourOfAKind]);
		for (int i = 8; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.secondCard);
	}

	TEST(Rules, hasWon_fourOfAKind_2) {
		Rules rl = Rules();
		hand hand = { {hearts, six}, {spades, three} };
		card card1 = { diamonds, three };
		card card2 = { hearts, three };
		card card3 = { clubs, three };
		card card4 = { spades, nine };
		card card5 = { clubs, queen };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_TRUE(result.musterCorrect[twoPair]);
		EXPECT_TRUE(result.musterCorrect[pair]);
		EXPECT_TRUE(result.musterCorrect[threeOfAKind]);
		EXPECT_FALSE(result.musterCorrect[straight]);
		EXPECT_FALSE(result.musterCorrect[fullHouse]);
		EXPECT_FALSE(result.musterCorrect[flush]);
		EXPECT_TRUE(result.musterCorrect[fourOfAKind]);
		for (int i = 8; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		std::cout << result.TwoPairCards[0] << std::endl;
		EXPECT_EQ(result.HighCard, hand.firstCard);
		EXPECT_EQ(result.PairCard, values::three);
		EXPECT_EQ(result.TwoPairCards[0], values::three);
		EXPECT_EQ(result.TwoPairCards[1], values::three);
		EXPECT_EQ(result.ThreeOfAKindCard, values::three);
		EXPECT_EQ(result.FourOfAKindCard, values::three);
	}

	TEST(Rules, hasWon_straightFlush_1) {
		Rules rl = Rules();
		hand hand = { {clubs, queen}, { diamonds, two } };
		card card1 = { clubs, ten };
		card card2 = { diamonds, three };
		card card3 = { diamonds, four };
		card card4 = { diamonds, five };
		card card5 = { diamonds, six };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[twoPair]);
		EXPECT_FALSE(result.musterCorrect[pair]);
		EXPECT_FALSE(result.musterCorrect[threeOfAKind]);
		EXPECT_TRUE(result.musterCorrect[straight]);
		EXPECT_FALSE(result.musterCorrect[fullHouse]);
		EXPECT_TRUE(result.musterCorrect[flush]);
		EXPECT_FALSE(result.musterCorrect[fourOfAKind]);
		EXPECT_TRUE(result.musterCorrect[straightFlush]);
		for (int i = 9; i < 10; i++) {
			EXPECT_FALSE(result.musterCorrect[i]);
		}
		EXPECT_EQ(result.HighCard, hand.firstCard);
		EXPECT_EQ(result.Flush[0].value, six);
		EXPECT_EQ(result.Flush[1].value, five);
		EXPECT_EQ(result.Flush[2].value, four);
		EXPECT_EQ(result.Flush[3].value, three);
		EXPECT_EQ(result.Flush[4].value, two);
		EXPECT_EQ(result.StraightFlushHighestCard, card5);
		EXPECT_EQ(result.StraightHighestCard, card5);
	}

	//Tests the royalFlushPart of hasWon
	TEST(Rules, hasWon_royalFlush_1) {
		Rules rl = Rules();
		hand hand = { {clubs, three}, { diamonds, ace } };
		card card1 = { spades, nine };
		card card2 = { diamonds, king };
		card card3 = { diamonds, queen };
		card card4 = { diamonds, jack };
		card card5 = { diamonds, ten };
		std::array <card, 5> community = { card1, card2, card3, card4, card5 };
		BestHand result = rl.HasWon(hand, community);
		EXPECT_TRUE(result.musterCorrect[highCard]);
		EXPECT_FALSE(result.musterCorrect[twoPair]);
		EXPECT_FALSE(result.musterCorrect[pair]);
		EXPECT_FALSE(result.musterCorrect[threeOfAKind]);
		EXPECT_TRUE(result.musterCorrect[straight]);
		EXPECT_FALSE(result.musterCorrect[fullHouse]);
		EXPECT_TRUE(result.musterCorrect[flush]);
		EXPECT_FALSE(result.musterCorrect[fourOfAKind]);
		EXPECT_TRUE(result.musterCorrect[straightFlush]);
		EXPECT_TRUE(result.musterCorrect[royalFlush]);
		EXPECT_EQ(result.HighCard, hand.secondCard);
		EXPECT_EQ(result.StraightHighestCard, hand.secondCard);
		EXPECT_EQ(result.Flush[0].value, ace);
		EXPECT_EQ(result.Flush[1].value, king);
		EXPECT_EQ(result.Flush[2].value, queen);
		EXPECT_EQ(result.Flush[3].value, jack);
		EXPECT_EQ(result.Flush[4].value, ten);
		EXPECT_EQ(result.StraightFlushHighestCard, hand.secondCard);
	}
}

namespace n_randomNrGen {
	//Tests for RandomGenerator
	//Tests wether the return value of randomNumberGenerator is positive
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
}

namespace n_gameController {
	//Tests for GameController
//Tests if funkction movePlayers() returns the selected action of the player
	TEST(movePlayer, returnRaise) {
		chipstack st_ch = chipstack({ 1,1,1,1,1,1 });
		chipstack sB = chipstack({ 1,0,0,0,0,0 });
		chipstack bB = chipstack({ 2,0,0,0,0,0 });
		auto player1 = std::make_shared<MockPlayer>(st_ch, "a");
		outPlay play1 = { raise, chipstack({ 1,0,0,0,0,0 }) };
		EXPECT_CALL(*player1, play(_, _)).WillOnce(Return(play1)); //reaction of the player is mocked to raise; this avoids Input
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

}

namespace n_money {
	//Tests for money
//Follwing Tests check wether the overload operators for chipstack work accordingly
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
		chipstack expected = chipstack({ 1,1,1,1,1,0 });
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

	TEST(money, less_Equal) {
		chipstack ch1 = chipstack({ 12,5,44,6,3,1 });
		int ch2 = 2090;
		bool less = false;
		if (ch1 < ch2) {
			less = true;
		}
		EXPECT_FALSE(less);
	}

	TEST(money, less_true) {
		chipstack ch1 = chipstack({ 11,5,44,6,3,1 });
		int ch2 = 3000;
		bool less = false;
		if (ch1 < ch2) {
			less = true;
		}
		EXPECT_TRUE(less);
	}

	TEST(money, less_false) {
		chipstack ch1 = chipstack({ 12,5,56,6,3,11 });
		int ch2 = 2090;
		bool less = false;
		if (ch1 < ch2) {
			less = true;
		}
		EXPECT_FALSE(less);
	}

	TEST(money, equal_True) {
		chipstack ch1 = chipstack({ 12,5,44,6,3,1 });
		int ch2 = 2090;
		bool equal = false;
		if (ch1 == ch2) {
			equal = true;
		}
		EXPECT_TRUE(equal);
	}

	TEST(money, equal_false) {
		chipstack ch1 = chipstack({ 11,5,44,6,3,1 });
		int ch2 = 19;
		bool equal = false;
		if (ch1 == ch2) {
			equal = true;
		}
		EXPECT_FALSE(equal);
	}

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

	//Tests the sum() Function for Chipstacks
	TEST(money, sumOperator) {
		chipstack ch1 = chipstack({ 12, 5, 44, 6, 3, 1 }); //12*5 + 5*10 + 44*20 + 6*50 + 3*100 + 1*500 = 2090
		int sum = ch1.sum();
		int expected = 2090;
		EXPECT_EQ(sum, expected);
	}

	//Test the if the output of the toString() function is a expected
	TEST(money, toString) {
		chipstack ch1 = chipstack({ 6, 5, 4, 3, 2, 1 });
		std::string st = ch1.toString();
		std::string expected = "{ 5$: 6, 10$: 5, 20$: 4, 50$: 3, 100$: 2, 500$: 1 }";
		EXPECT_EQ(st, expected);

	}
}

namespace n_out {
	//Tests for output
//Tests the Output of the cardToString() Function
	TEST(output, cardToString) {
		Output out = Output();
		card c1 = { diamonds, five };
		std::string result = out.cardToString(c1);
		std::string expected = "[D: 5]";
		EXPECT_EQ(result, expected);
	}

	//Tests if output of chipstackToStringAndSum ist as expected
	TEST(output, chipstackToStringAndSum) {
		Output out = Output();
		chipstack ch1 = chipstack({ 6, 5, 4, 3, 2, 1 });
		std::string st = out.chipstackToStringAndSum(ch1);
		std::string expected = "{ 5$: 6, 10$: 5, 20$: 4, 50$: 3, 100$: 2, 500$: 1 } (sum: 1010$)";
		EXPECT_EQ(st, expected);
	}
}

namespace n_drawResolvernf {
	// constants(can be used to build all tests)

	Rules rules;
	chipstack ch = chipstack({ 1,1,1,1,1,1 });
	card card1, card2, card3, card4, card5;
	hand h1, h2;
	std::array<card, 5> community;
	std::shared_ptr<DumbBot> p1 = std::make_shared<DumbBot>(ch, "A");
	std::shared_ptr<DumbBot> p2 = std::make_shared<DumbBot>(ch, "B");
	DrawResolver dR;

	//----------------------------------high card-----------------------------------//
	//simple
	TEST(drawResolver, HighCard_normal) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, king}, {hearts, five} }; //expected winner
		h2 = { {diamonds, seven}, {clubs, five} };
		card1 = { diamonds, eight };
		card2 = { clubs, nine };
		card3 = { diamonds, ace };
		card4 = { spades, eight };
		card5 = { spades, eight };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[highCard] && players_besthands[1].besthand.musterCorrect[highCard]);
		//Resolve draws
		dR.resolveDraws(players_besthands, highCard);
		EXPECT_EQ(players_besthands.size(), 1);
		EXPECT_EQ(players_besthands[0].player, p1);
	}

	//resolvable
	TEST(drawResolver, HighCard_resolvable) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, three}, {hearts, five} }; //expected winner
		h2 = { {diamonds, two}, {clubs, five} };
		card1 = { diamonds, eight };
		card2 = { clubs, nine };
		card3 = { diamonds, ace };
		card4 = { spades, eight };
		card5 = { spades, eight };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[highCard] && players_besthands[1].besthand.musterCorrect[highCard]);
		//Resolve draws
		dR.resolveDraws(players_besthands, highCard);
		EXPECT_EQ(players_besthands.size(), 1);
		EXPECT_EQ(players_besthands[0].player, p1);
	}

	//true draw
	TEST(drawResolver, HighCard_draw) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, three}, {hearts, five} };
		h2 = { {diamonds, three}, {clubs, five} };
		card1 = { diamonds, eight };
		card2 = { clubs, nine };
		card3 = { diamonds, ace };
		card4 = { spades, eight };
		card5 = { spades, eight };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[highCard] && players_besthands[1].besthand.musterCorrect[highCard]);
		//Resolve draws
		dR.resolveDraws(players_besthands, highCard);
		EXPECT_EQ(players_besthands.size(), 2);
		EXPECT_EQ(players_besthands[0].player, p1);
		EXPECT_EQ(players_besthands[1].player, p2);
	}

	//----------------------------------pair-----------------------------------//
	//simple
	TEST(drawResolver, pair_normal) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, three}, {hearts, five} }; //expected winner
		h2 = { {diamonds, two}, {clubs, six} };
		card1 = { diamonds, three };
		card2 = { clubs, nine };
		card3 = { diamonds, ace };
		card4 = { spades, eight };
		card5 = { spades, two };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[pair] && players_besthands[1].besthand.musterCorrect[pair]);
		//Resolve draws
		dR.resolveDraws(players_besthands, pair);
		EXPECT_EQ(players_besthands.size(), 1);
		EXPECT_EQ(players_besthands[0].player, p1);
	}

	//resolvable
	TEST(drawResolver, pair_resolvable) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, three}, {hearts, five} };
		h2 = { {diamonds, four}, {clubs, five} }; //expected winner
		card1 = { diamonds, eight };
		card2 = { clubs, five };
		card3 = { diamonds, ace };
		card4 = { spades, eight };
		card5 = { spades, eight };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[pair] && players_besthands[1].besthand.musterCorrect[pair]);
		//Resolve draws
		dR.resolveDraws(players_besthands, pair);
		EXPECT_EQ(players_besthands.size(), 1);
		EXPECT_EQ(players_besthands[0].player, p2);
	}

	//true draw
	TEST(drawResolver, pair_draw) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, three}, {hearts, five} };
		h2 = { {diamonds, three}, {clubs, five} };
		card1 = { diamonds, eight };
		card2 = { clubs, five };
		card3 = { diamonds, ace };
		card4 = { spades, eight };
		card5 = { spades, eight };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[pair] && players_besthands[1].besthand.musterCorrect[pair]);
		//Resolve draws
		dR.resolveDraws(players_besthands, pair);
		EXPECT_EQ(players_besthands.size(), 2);
		EXPECT_EQ(players_besthands[0].player, p1);
		EXPECT_EQ(players_besthands[1].player, p2);
	}

	//----------------------------------2pair-----------------------------------//
	//simple
	TEST(drawResolver, twopair_normal) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, king}, {hearts, two} }; //expected winner
		h2 = { {diamonds, seven}, {clubs, five} };
		card1 = { diamonds, king };
		card2 = { clubs, two };
		card3 = { diamonds, ace };
		card4 = { spades, five };
		card5 = { spades, seven };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[twoPair] && players_besthands[1].besthand.musterCorrect[twoPair]);
		//Resolve draws
		dR.resolveDraws(players_besthands, twoPair);
		EXPECT_EQ(players_besthands.size(), 1);
		EXPECT_EQ(players_besthands[0].player, p1);
	}

	//resolvable
	TEST(drawResolver, twopair_resolvable) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, three}, {hearts, five} };
		h2 = { {diamonds, four}, {clubs, five} }; //expected winner
		card1 = { diamonds, eight };
		card2 = { clubs, five };
		card3 = { diamonds, four };
		card4 = { spades, eight };
		card5 = { spades, three };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[twoPair] && players_besthands[1].besthand.musterCorrect[twoPair]);
		//Resolve draws
		dR.resolveDraws(players_besthands, twoPair);
		EXPECT_EQ(players_besthands.size(), 1);
		EXPECT_EQ(players_besthands[0].player, p2);
	}

	//true draw
	TEST(drawResolver, twopair_draw) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, three}, {hearts, five} };
		h2 = { {diamonds, three}, {clubs, five} };
		card1 = { diamonds, eight };
		card2 = { clubs, five };
		card3 = { diamonds, ace };
		card4 = { spades, three };
		card5 = { spades, eight };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[twoPair] && players_besthands[1].besthand.musterCorrect[twoPair]);
		//Resolve draws
		dR.resolveDraws(players_besthands, twoPair);
		EXPECT_EQ(players_besthands.size(), 2);
		EXPECT_EQ(players_besthands[0].player, p1);
		EXPECT_EQ(players_besthands[1].player, p2);
	}

	//----------------------------------3 of a kind-----------------------------------//
	//simple
	TEST(drawResolver, threeOfAKind_normal) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, two}, {hearts, ace} }; //expected winner
		h2 = { {diamonds, seven}, {clubs, five} };
		card1 = { diamonds, ace };
		card2 = { clubs, ace };
		card3 = { diamonds, five };
		card4 = { spades, five };
		card5 = { spades, six };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[threeOfAKind] && players_besthands[1].besthand.musterCorrect[threeOfAKind]);
		//Resolve draws
		dR.resolveDraws(players_besthands, threeOfAKind);
		EXPECT_EQ(players_besthands.size(), 1);
		EXPECT_EQ(players_besthands[0].player, p1);
	}

	//resolvable
	TEST(drawResolver, threeOfAKind_resolvable) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, three}, {hearts, five} };
		h2 = { {diamonds, four}, {clubs, five} }; //expected winner
		card1 = { diamonds, five };
		card2 = { clubs, five };
		card3 = { diamonds, four };
		card4 = { spades, eight };
		card5 = { spades, three };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[threeOfAKind] && players_besthands[1].besthand.musterCorrect[threeOfAKind]);
		//Resolve draws
		dR.resolveDraws(players_besthands, threeOfAKind);
		EXPECT_EQ(players_besthands.size(), 1);
		EXPECT_EQ(players_besthands[0].player, p2);
	}

	//true draw
	TEST(drawResolver, threeOfAKind_draw) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, three}, {hearts, five} };
		h2 = { {diamonds, three}, {clubs, five} };
		card1 = { diamonds, eight };
		card2 = { clubs, five };
		card3 = { diamonds, ace };
		card4 = { spades, five };
		card5 = { spades, eight };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[threeOfAKind] && players_besthands[1].besthand.musterCorrect[threeOfAKind]);
		//Resolve draws
		dR.resolveDraws(players_besthands, threeOfAKind);
		EXPECT_EQ(players_besthands.size(), 2);
		EXPECT_EQ(players_besthands[0].player, p1);
		EXPECT_EQ(players_besthands[1].player, p2);
	}

	//----------------------------------straight-----------------------------------//
	//simple
	TEST(drawResolver, straight_normal) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, queen}, {hearts, seven} }; //expected winner
		h2 = { {diamonds, king}, {clubs, two} };
		card1 = { diamonds, three };
		card2 = { clubs, four };
		card3 = { diamonds, five };
		card4 = { spades, five };
		card5 = { spades, six };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[straight] && players_besthands[1].besthand.musterCorrect[straight]);
		//Resolve draws
		dR.resolveDraws(players_besthands, straight);
		EXPECT_EQ(players_besthands.size(), 1);
		EXPECT_EQ(players_besthands[0].player, p1);
	}

	//resolvable
	TEST(drawResolver, straight_resolvable) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, queen}, {hearts, five} };
		h2 = { {diamonds, king}, {clubs, five} }; //expected winner
		card1 = { diamonds, two };
		card2 = { clubs, three };
		card3 = { diamonds, four };
		card4 = { spades, ace };
		card5 = { spades, three };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[straight] && players_besthands[1].besthand.musterCorrect[straight]);
		//Resolve draws
		dR.resolveDraws(players_besthands, straight);
		EXPECT_EQ(players_besthands.size(), 1);
		EXPECT_EQ(players_besthands[0].player, p2);
	}

	//true draw
	TEST(drawResolver, straight_draw) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, three}, {hearts, five} };
		h2 = { {diamonds, three}, {clubs, five} };
		card1 = { diamonds, two };
		card2 = { clubs, four };
		card3 = { diamonds, six };
		card4 = { spades, five };
		card5 = { spades, eight };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[straight] && players_besthands[1].besthand.musterCorrect[straight]);
		//Resolve draws
		dR.resolveDraws(players_besthands, straight);
		EXPECT_EQ(players_besthands.size(), 2);
		EXPECT_EQ(players_besthands[0].player, p1);
		EXPECT_EQ(players_besthands[1].player, p2);
	}

	//----------------------------------flush-----------------------------------//
	//simple
	TEST(drawResolver, flush_normal) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {hearts, queen}, {hearts, seven} }; //expected winner
		h2 = { {hearts, queen}, {hearts, two} };
		card1 = { hearts, three };
		card2 = { hearts, four };
		card3 = { hearts, five };
		card4 = { spades, five };
		card5 = { spades, six };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[flush] && players_besthands[1].besthand.musterCorrect[flush]);
		//Resolve draws
		dR.resolveDraws(players_besthands, flush);
		EXPECT_EQ(players_besthands.size(), 1);
		EXPECT_EQ(players_besthands[0].player, p1);
	}

	//middle-way doesnt exist 
	
	//true draw
	TEST(drawResolver, flush_draw) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, three}, {diamonds, five} };
		h2 = { {diamonds, three}, {diamonds, five} };
		card1 = { diamonds, two };
		card2 = { diamonds, four };
		card3 = { diamonds, six };
		card4 = { spades, five };
		card5 = { spades, eight };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[flush] && players_besthands[1].besthand.musterCorrect[flush]);

		//Resolve draws
		dR.resolveDraws(players_besthands, flush);
		EXPECT_EQ(players_besthands.size(), 2);
		EXPECT_EQ(players_besthands[0].player, p1);
		EXPECT_EQ(players_besthands[1].player, p2);
	}

	//----------------------------------fullHouse-----------------------------------//
	//simple
	TEST(drawResolver, fullHouse_normal) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, queen}, {hearts, two} }; //expected winner
		h2 = { {diamonds, jack}, {clubs, two} };
		card1 = { diamonds, two };
		card2 = { clubs, queen };
		card3 = { diamonds, queen };
		card4 = { spades, jack };
		card5 = { spades, jack };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[fullHouse] && players_besthands[1].besthand.musterCorrect[fullHouse]);
		//Resolve draws
		dR.resolveDraws(players_besthands, fullHouse);
		EXPECT_EQ(players_besthands.size(), 1);
		EXPECT_EQ(players_besthands[0].player, p1);
	}

	//resolvable
	TEST(drawResolver, fullHouse_resolvable) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, queen}, {hearts, five} };
		h2 = { {diamonds, queen}, {clubs, six} }; //expected winner
		card1 = { diamonds, queen };
		card2 = { clubs, six };
		card3 = { diamonds, six };
		card4 = { spades, five };
		card5 = { spades, five };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[fullHouse] && players_besthands[1].besthand.musterCorrect[fullHouse]);
		//Resolve draws
		dR.resolveDraws(players_besthands, fullHouse);
		EXPECT_EQ(players_besthands.size(), 1);
		EXPECT_EQ(players_besthands[0].player, p2);
	}

	//true draw
	TEST(drawResolver, fullHouse_draw) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, three}, {hearts, five} };
		h2 = { {diamonds, three}, {clubs, five} };
		card1 = { diamonds, three };
		card2 = { clubs, three };
		card3 = { diamonds, three };
		card4 = { spades, five };
		card5 = { spades, five };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[fullHouse] && players_besthands[1].besthand.musterCorrect[fullHouse]);
		//Resolve draws
		dR.resolveDraws(players_besthands, fullHouse);
		EXPECT_EQ(players_besthands.size(), 2);
		EXPECT_EQ(players_besthands[0].player, p1);
		EXPECT_EQ(players_besthands[1].player, p2);
	}

	//----------------------------------4Oak-----------------------------------//
	//simple
	TEST(drawResolver, fourOfAKind_normal) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, queen}, {hearts, queen} }; //expected winner
		h2 = { {diamonds, jack}, {clubs, jack} };
		card1 = { diamonds, two };
		card2 = { clubs, queen };
		card3 = { diamonds, queen };
		card4 = { spades, jack };
		card5 = { spades, jack };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[fourOfAKind] && players_besthands[1].besthand.musterCorrect[fourOfAKind]);
		//Resolve draws
		dR.resolveDraws(players_besthands, fourOfAKind);
		EXPECT_EQ(players_besthands.size(), 1);
		EXPECT_EQ(players_besthands[0].player, p1);
	}

	//resolvable
	TEST(drawResolver, fourOfAKind_resolvable) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, queen}, {hearts, five} };
		h2 = { {diamonds, queen}, {clubs, six} }; //expected winner
		card1 = { diamonds, queen };
		card2 = { clubs, six };
		card3 = { diamonds, six };
		card4 = { spades, queen };
		card5 = { spades, queen };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[fourOfAKind] && players_besthands[1].besthand.musterCorrect[fourOfAKind]);
		//Resolve draws
		dR.resolveDraws(players_besthands, fourOfAKind);
		EXPECT_EQ(players_besthands.size(), 1);
		EXPECT_EQ(players_besthands[0].player, p2);
	}

	//true draw
	TEST(drawResolver, fourOfAKind_draw) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, three}, {hearts, five} };
		h2 = { {diamonds, three}, {clubs, five} };
		card1 = { diamonds, three };
		card2 = { clubs, five };
		card3 = { diamonds, five };
		card4 = { spades, five };
		card5 = { spades, five };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[fourOfAKind] && players_besthands[1].besthand.musterCorrect[fourOfAKind]);
		//Resolve draws
		dR.resolveDraws(players_besthands, fourOfAKind);
		EXPECT_EQ(players_besthands.size(), 2);
		EXPECT_EQ(players_besthands[0].player, p1);
		EXPECT_EQ(players_besthands[1].player, p2);
	}

	//----------------------------------straightFlush-----------------------------------//
	//simple
	TEST(drawResolver, straightFlush_normal) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, queen}, {diamonds, jack} }; //expected winner
		h2 = { {diamonds, seven}, {diamonds, six} };
		card1 = { diamonds, eight };
		card2 = { diamonds, nine };
		card3 = { diamonds, ten };
		card4 = { spades, jack };
		card5 = { spades, jack };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[straightFlush] && players_besthands[1].besthand.musterCorrect[straightFlush]);
		//Resolve draws
		dR.resolveDraws(players_besthands, straightFlush);
		EXPECT_EQ(players_besthands.size(), 1);
		EXPECT_EQ(players_besthands[0].player, p1);
	}

	//resolvable
	TEST(drawResolver, straightFlush_resolvable) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, queen}, {hearts, five} };
		h2 = { {diamonds, queen}, {clubs, six} }; //expected winner
		card1 = { diamonds, eight };
		card2 = { diamonds, nine };
		card3 = { diamonds, ten };
		card4 = { diamonds, jack };
		card5 = { spades, two };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[straightFlush] && players_besthands[1].besthand.musterCorrect[straightFlush]);
		//Resolve draws
		dR.resolveDraws(players_besthands, straightFlush);
		EXPECT_EQ(players_besthands.size(), 1);
		EXPECT_EQ(players_besthands[0].player, p2);
	}

	//true draw
	TEST(drawResolver, straightFlush_draw) {
		std::vector<playerNBestHand> players_besthands;
		//cards
		h1 = { {diamonds, queen}, {hearts, five} };
		h2 = { {diamonds, queen}, {clubs, five} };
		card1 = { diamonds, eight };
		card2 = { diamonds, nine };
		card3 = { diamonds, ten };
		card4 = { diamonds, jack };
		card5 = { spades, two };
		community = { card1, card2, card3, card4, card5 };
		//players hands
		p1->setHand(h1.firstCard, h1.secondCard);
		p2->setHand(h2.firstCard, h2.secondCard);
		//players_besthands
		players_besthands.push_back({ p1, rules.HasWon(h1, community) });
		players_besthands.push_back({ p2, rules.HasWon(h2, community) });
		//test if winTypes are right
		EXPECT_TRUE(players_besthands[0].besthand.musterCorrect[straightFlush] && players_besthands[1].besthand.musterCorrect[straightFlush]);
		//Resolve draws
		dR.resolveDraws(players_besthands, straightFlush);
		EXPECT_EQ(players_besthands.size(), 2);
		EXPECT_EQ(players_besthands[0].player, p1);
		EXPECT_EQ(players_besthands[1].player, p2);
	}
}

////Tests the whole Gamesystem
//TEST(system, playgame) {
//	chipstack chip1 = chipstack({ 6,5,4,3,2,1 });
//	chipstack chip2 = chipstack({ 6,0,0,0,0,0 });
//	chipstack sb = chipstack({ 1,0,0,0,0,0 });
//	chipstack bb = chipstack({ 2,0,0,0,0,0 });
//	std::shared_ptr<Player> bot1 = std::make_shared<DumbBot>(chip1, "a");
//	std::shared_ptr<Player> bot2 = std::make_shared<DumbBot>(chip2, "b");
//	std::vector<std::shared_ptr<Player>> players;
//	players.push_back(bot1);
//	players.push_back(bot2);
//	int max=10000;
//	GameController gc = GameController(players, max, bb, sb);
//	std::shared_ptr<Player> winner = gc.playGame();
//	bool systemruns=false;
//	if(winner==bot1 || winner==bot2){
//		systemruns=true;
//	}
//	EXPECT_TRUE(systemruns);
//}
