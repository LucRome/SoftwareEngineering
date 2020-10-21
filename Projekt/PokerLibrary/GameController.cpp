#include "pch.h"
#include "GameController.h"

GameController::GameController(std::vector<std::shared_ptr<Player>> players, int max, chipstack bigBlind, chipstack smallBlind)
	:m_players(players)
	,m_max(max)
	,m_bigBlind(bigBlind)
	,m_smallBlind(smallBlind)
	,m_dealer_pos(0)
	,m_playersInRound(players)
	,m_communityCard(std::array<card, 5>())
{
	m_players.shrink_to_fit();
	m_playersInRound.shrink_to_fit();

	//initialise m_pot_perPlayer 
	for (int i = 0; i < m_players.size(); i++) {
		m_pot_perPlayer.push_back(chipstack());
	}
	m_pot_perPlayer.shrink_to_fit();
}

Player& GameController::playGame()
{
	//TODO: extract bankrupt players (after each round)
	bool cont = true;
	while (cont) {
		round();
		m_dealer_pos = (m_dealer_pos + 1) % m_playersInRound.size();
		//extract bankrupt players
		for (int i = 0; i < m_players.size(); i++) {
			if (m_players[i]->getWinnings() == 0) {
				m_players.erase(m_players.begin() + i);
			}
		}
		m_players.shrink_to_fit();

		//reset everything from previous round
		resetAfterRound();
	}
	return *(m_players[0]);
}

//TODO: Blinds

void GameController::round()
{
	//Blinds
	int sb_pos = (m_dealer_pos + 1) % m_playersInRound.size();
	int bb_pos = (sb_pos + 1) % m_playersInRound.size();
	int startBid_pos = (bb_pos + 1) % m_playersInRound.size();

	player_bid(sb_pos, m_smallBlind);
	player_bid(bb_pos, m_bigBlind);

	preflop(startBid_pos);
	startBid_pos = (startBid_pos + 1) % m_playersInRound.size();
	flop(startBid_pos);
	startBid_pos = (startBid_pos + 1) % m_playersInRound.size();
	turn(startBid_pos);
	startBid_pos = (startBid_pos + 1) % m_playersInRound.size();
	river(startBid_pos);
	showdown(startBid_pos);
}

void GameController::preflop(int start_playerNr)
{
	for (std::shared_ptr<Player> p : m_playersInRound) {
		std::array<card, 2> hand = dealer.getHand();
		p->setHand(hand[0], hand[1]);
	}
	roundOfBidding(start_playerNr);
}

void GameController::resetAfterRound()
{
	dealer.refresh();
	m_bid = chipstack();
	m_pot = chipstack();
	for (chipstack c : m_pot_perPlayer) {
		c = chipstack();
	}
}

void GameController::flop(int start_playerNr)
{
	std::array<card, 3> c_flop = dealer.getFlop();
	for (int i = 0; i < c_flop.size(); i++) {
		m_communityCard[i] = c_flop[i];
	}
	roundOfBidding(start_playerNr);
}

#define turn_pos 3
void GameController::turn(int start_playerNr)
{
	m_communityCard[turn_pos] = dealer.getCard();
	roundOfBidding(start_playerNr);
}

#define river_pos 4
void GameController::river(int start_playerNr)
{
	m_communityCard[river_pos] = dealer.getCard();
	roundOfBidding(start_playerNr);
}

void GameController::showdown(int start_playerNr)
{
	//TODO: showdown (need rules and Output)
	//also: add pot to winner
}

void GameController::roundOfBidding(int start_playerNr)
{
	int playersThatActed = 0;
	int playerNr = start_playerNr; //point to the plyers whos turn it is
	bool cont = true;
	
	while (cont) {
		for (int i = 0; i < m_playersInRound.size(); i++) { //just iterate over all players
			out.printTable(m_playersInRound, playerNr, m_communityCard, m_pot_perPlayer[playerNr],
				m_pot, m_bid);
			if (movePlayer(playerNr) != fold) { //increase PlayerNr. if Player doesnt fold
				playerNr = (playerNr + 1) % m_playersInRound.size();
			}
			else {
				playerNr %= m_playersInRound.size();
			}
			playersThatActed++;
			if(playersThatActed >= m_playersInRound.size() && allPlayersSamePot()) {
				cont = false;
			}
		}
	}

//TODO: noch prüfen, falls negative Werte im moneystack -> ungültiger Zug
//TODO: ALL-IN
}

plays GameController::movePlayer(int playerNr)
{
	plays play;
	bool moveAllowed = false;
	do { //let player choose move until correct
		outPlay move = m_players[playerNr]->play(m_bid - m_pot_perPlayer[playerNr], possiblePlays(playerNr));
		switch (move.play) {
		case fold: //remove Players from all vectors for this round
			moveAllowed = true;
			m_playersInRound.erase(m_playersInRound.begin() + playerNr);
			m_pot_perPlayer.erase(m_pot_perPlayer.begin() + playerNr);
			break;
		case check: //check whether bid is right, then remove chips from player and add to pot
			if (move.chips == (m_bid.sum() - m_pot_perPlayer[playerNr].sum())) {
				moveAllowed = true;
				player_bid(playerNr, move.chips);
			}
			break;
		case raise: //only allowed when player_pot + new bid <= maximum
			if (m_pot_perPlayer[playerNr] + move.chips < m_max + 1
				&& m_pot_perPlayer[playerNr] + move.chips > m_bid) {
				moveAllowed = true;
				player_bid(playerNr, move.chips);
			}
			break;
		default:
			moveAllowed = false;
		}
		play = move.play;
	} while (!moveAllowed);
	return play;
}

std::vector<plays> GameController::possiblePlays(int playerNr)
{
	//TODO: ausarbeiten
	std::vector<plays> possible;
	possible.push_back(fold);
	if (m_pot_perPlayer[playerNr] <= m_bid) {
		possible.push_back(check);
	}
	if (m_pot_perPlayer[playerNr] < m_max) {
		possible.push_back(raise);
	}
	return possible;
}

bool GameController::allPlayersSamePot()
{
	bool same = true;
	for (int i = 0; i < m_playersInRound.size(); i++) {
		if (!(m_pot_perPlayer[i] == m_bid.sum())) {
			same = false;
		}
	}
	return same;
}


void GameController::player_bid(int playerNr, chipstack chips)
{
	m_playersInRound[playerNr]->decFromWinnings(chips);
	m_pot_perPlayer[playerNr] = m_pot_perPlayer[playerNr] + chips;
	m_pot = m_pot + chips;
	if (m_pot_perPlayer[playerNr] > m_bid) {
		m_bid = m_pot_perPlayer[playerNr];
	}
}
