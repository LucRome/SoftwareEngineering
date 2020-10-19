#pragma once
#include<memory>
#include "Player.h"
#include "DeckOfCards.h"
#include "Money.h"
#include "Dealer.h"

class GameController
{
public:
	GameController(std::vector<std::shared_ptr<Player>> players, int max, chipstack bigBlind, chipstack smallBlind);
	Player& playGame(); //Rückgabetyp benötigt, für Gewinner

private:
	void round();
	void preflop(int start_playerNr);
	void resetAfterRound();
	void flop(int start_playerNr);
	void turn(int start_playerNr);
	void river(int start_playerNr);
	void showdown(int start_playerNr);
	void roundOfBidding(int start_playerNr);
	plays movePlayer(int playerNr);
	std::vector<plays> possiblePlays(int playerNr);
	bool allPlayersSamePot();

	//add bid to all variables where its needed and remove from player
	void player_bid(int playerNr, chipstack chips);

	Dealer dealer;
	std::vector<std::shared_ptr<Player>> m_players; //players that are bankrupt are deleted
	std::vector<std::shared_ptr<Player>> m_playersInRound; //to track who folded
	std::vector<chipstack> m_pot_perPlayer; //to track what each Player bid (fold -> remove)
	chipstack m_pot; //sum of all bids (pot)
	chipstack m_bid; //Highest bid (per round)
	chipstack m_smallBlind, m_bigBlind;
	int m_max;
	int m_dealer_pos; //start: 0

	std::array<card, 5> m_communityCard;
};

