#include "pch.h"
#include "DeckOfCards.h"
#include "GameController.h"
#include "HumanPlayer.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

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


//Test: GameController::playGame()
//only while menue isnt finished
//TODO: remove
#define st_ch chipstack({1,1,1,1,1,1})
#define sB chipstack({1,0,0,0,0,0})
#define bB chipstack({2,0,0,0,0,0})

TEST(playGame, justPlay) {
	std::vector<std::shared_ptr<Player>> players;
	players.push_back(std::make_shared<HumanPlayer>(st_ch, "A"));
	players.push_back(std::make_shared<HumanPlayer>(st_ch, "B"));
	players.push_back(std::make_shared<HumanPlayer>(st_ch, "C"));
	players.push_back(std::make_shared<HumanPlayer>(st_ch, "D"));
	players.shrink_to_fit();

	GameController gc = GameController(players, 10000, bB, sB);
	std::shared_ptr<Player>& winner = gc.playGame();
	std::string s = winner->getName();
	bool suc = s == "A";
	EXPECT_TRUE(suc);
}