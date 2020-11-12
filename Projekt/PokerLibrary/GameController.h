#pragma once
#include<memory>
#include "Player.h"
#include "DeckOfCards.h"
#include "Money.h"
#include "Dealer.h"
#include "Output.h"
#include "Rules.h"
#include "Player_Besthand_struct.h"

class GameController
{
public:
	GameController(std::vector<std::shared_ptr<Player>> players, int max, chipstack bigBlind, chipstack smallBlind);
	~GameController();
	friend class GCFriend;
	std::shared_ptr<Player> playGame(); //rounds until last player not bankrupt (winner)

private:
	void round(); //from preflop to showdown
	void resetAfterRound(); //reset membervariables for a new round
	//Functions for a round (see Rules.txt)
	bool preflop(int start_playerNr);
	bool flop(int start_playerNr);
	bool turn(int start_playerNr);
	bool river(int start_playerNr);
	void showdown(int start_playerNr);

	//bid (after each step)
	bool roundOfBidding(int start_playerNr);
	//move of one player
	plays movePlayer(int playerNr);
	std::vector<plays> possiblePlays(int playerNr);
	//have all players bid the same?
	bool allPlayersSamePot();

	//determines winners
	std::vector<playerNBestHand>& detWinner(std::vector<playerNBestHand>& players_besthands);
	//gives the money to the winners
	void addPotToWinners(std::vector<playerNBestHand>& winners);

	//add bid to all variables where its needed and remove from player
	void player_bid(int playerNr, chipstack chips);

	//membervariables
	Dealer dealer;

	std::vector<std::shared_ptr<Player>> m_players; //players that are bankrupt are deleted
	std::vector<std::shared_ptr<Player>> m_playersInRound; //to track who folded
	std::vector<chipstack> m_pot_perPlayer; //to track what each Player bid (fold -> remove)
	chipstack m_pot; //sum of all bids (pot)
	chipstack m_bid; //Highest bid (per round)
	chipstack m_smallBlind, m_bigBlind;
	int m_max;
	int m_dealer_pos; //start: 0

	std::array<card, 5> m_communityCard = {card(), card(), card(), card(), card()}; //community cards

	//Output Class
	Output out;
};

