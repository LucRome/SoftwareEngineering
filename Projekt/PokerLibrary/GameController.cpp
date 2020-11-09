#include "pch.h"
#include "GameController.h"
#include "Rules.h"
#include "DrawResolver.h"

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

GameController::~GameController()
{
}

std::shared_ptr<Player>& GameController::playGame()
{
	bool cont = true;
	while (cont) {
		round();
		//extract bankrupt players
		for (int i = 0; i < m_players.size(); i++) {
			if (m_players[i]->bankrupt()) {
				m_players.erase(m_players.begin() + i);
			}
		}
		if (m_players.size() > 1) { //check if at least 2 players are left
			m_dealer_pos = (m_dealer_pos + 1) % m_players.size();
			m_players.shrink_to_fit();
			m_playersInRound = m_players;
			//reset everything from previous round
			resetAfterRound();
		}
		else {
			cont = false;
		}
		
	}
	return m_players[0];
}


void GameController::round() //return false if all players folded
{
	//Blinds
	int sb_pos = (m_dealer_pos + 1) % m_playersInRound.size();
	int bb_pos = (sb_pos + 1) % m_playersInRound.size();
	int startBid_pos = (bb_pos + 1) % m_playersInRound.size();

	player_bid(sb_pos, m_smallBlind);
	player_bid(bb_pos, m_bigBlind);

	if (preflop(startBid_pos)) { //just continue if there are still players left
		startBid_pos = (startBid_pos + 1) % m_playersInRound.size();
		if (flop(startBid_pos)) {
			startBid_pos = (startBid_pos + 1) % m_playersInRound.size();
			if (turn(startBid_pos)) {
				startBid_pos = (startBid_pos + 1) % m_playersInRound.size();
				if (river(startBid_pos)) {
					showdown(startBid_pos);
				}
			}
		}
	}
}

bool GameController::preflop(int start_playerNr)
{
	for (std::shared_ptr<Player> p : m_playersInRound) {
		std::array<card, 2> hand = dealer.getHand();
		p->setHand(hand[0], hand[1]);
	}
	return roundOfBidding(start_playerNr);
}

void GameController::resetAfterRound()
{
	dealer.refresh();
	m_bid = chipstack();
	m_pot = chipstack();
	m_pot_perPlayer.clear();
	for (int i = 0; i < m_players.size(); i++) {
		m_pot_perPlayer.push_back(chipstack());
	}
}

bool GameController::flop(int start_playerNr)
{
	std::array<card, 3> c_flop = dealer.getFlop();
	for (int i = 0; i < c_flop.size(); i++) {
		m_communityCard[i] = c_flop[i];
	}
	return roundOfBidding(start_playerNr);
}

#define turn_pos 3
bool GameController::turn(int start_playerNr)
{
	m_communityCard[turn_pos] = dealer.getCard();
	return roundOfBidding(start_playerNr);
}

#define river_pos 4
bool GameController::river(int start_playerNr)
{
	m_communityCard[river_pos] = dealer.getCard();
	return roundOfBidding(start_playerNr);
}

void GameController::showdown(int start_playerNr)
{
	//TODO: showdown (need rules and Output)
	
	
	//check Rules:
	Rules rules;
	std::vector<playerNBestHand> player_besthands; //connects Players and BestHands
	for (std::shared_ptr<Player> player : m_playersInRound) {
		playerNBestHand pu = { player, rules.HasWon(player->getHand(), m_communityCard) };
		player_besthands.push_back(pu);
	}
	//print Showdown (all cards open + bestHand + pot)
	out.printShowdown(player_besthands, m_pot, m_communityCard);

	//determine winner(s)
	std::vector<playerNBestHand>& winners = detWinner(player_besthands);
	//add pot to winner(s)
	addPotToWinners(winners);
	out.printWinners(winners);
}

bool GameController::roundOfBidding(int start_playerNr) //return false if all players folded
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
				
				if (m_playersInRound.size() != 0) {
					playerNr %= m_playersInRound.size();
				}
				else {
					return false;
				}
				
			}
			playersThatActed++;
			if(playersThatActed >= m_playersInRound.size() && allPlayersSamePot()) {
				cont = false;
			}
		}
	}
	return true;
//TODO: noch prüfen, falls negative Werte im moneystack -> ungültiger Zug
//TODO: ALL-IN
}

plays GameController::movePlayer(int playerNr)
{
	plays play = check; //if player is bankrupt he went all in -> he can check until the end of the round
	bool moveAllowed = false;
	if (!m_players[playerNr]->bankrupt()) { //Player doesnt need to move if bankrupt, but stays in round (ALL IN)
		do { //let player choose move until correct
			chipstack delta = m_bid - m_pot_perPlayer[playerNr]; //operator-: result cant be negative
			outPlay move = m_playersInRound[playerNr]->play(delta, possiblePlays(playerNr));
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
	}

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

bool GameController::allPlayersSamePot()//returns if all Player bid the same sum
{
	bool same = true;
	for (int i = 0; i < m_playersInRound.size(); i++) {
		if (!(m_pot_perPlayer[i] == m_bid.sum())) {
			same = false;
		}
	}
	return same;
}


//Niedrigere Werte auch noch checken?

std::vector<playerNBestHand>& GameController::detWinner(std::vector<playerNBestHand>& players_besthands) //players: memberm_playersInRound
{
	//draws (Temp)
	DrawResolver dR;
	std::vector<playerNBestHand>& draws = *(new std::vector<playerNBestHand>());
	int winner_nr; //nr of player who has won (in case of draw: int_max)
	winTypes best = highCard;

	//iterate over all players and compare
	//already resolve same winType issues
	winTypes playerWinType = highCard; //winType of this player
	int musterNr = royalFlush; //to iterate over all winTypes (also determines starting point)
	bool cont = true;
	for (int playerNr = 0; playerNr < players_besthands.size(); playerNr++) { //i =: playerNr
		musterNr = royalFlush; // reset

		//determine best muster
		while(musterNr >= highCard && cont){
			if (players_besthands[playerNr].besthand.musterCorrect[musterNr]) {
				playerWinType = winTypes(musterNr);
				cont = false;
			}
			musterNr--;
		}

		//determine if best, draw, lose
		if (playerWinType > best) { //winner
			best = playerWinType;
			winner_nr = playerNr;
			draws.clear(); //all previous draws are meaningless
			draws.push_back(players_besthands[playerNr]);
		}
		else if (playerWinType < best) { //lost -> eliminate from vectors
			players_besthands.erase(players_besthands.begin() + playerNr);
		}
		else if (playerWinType == best) { //draw -> resolve or push to draws
			draws.push_back(players_besthands[playerNr]);
			if (draws.size() > 1) {
				dR.resolveDraws(draws, playerWinType);
			}
		}
	}
	return draws;
}

void GameController::addPotToWinners(std::vector<playerNBestHand>& winners)
{
	int cashPerPlayer = m_pot.sum() / winners.size();
	for (playerNBestHand p : winners) {
		p.player->addToWinnings(cashPerPlayer);
	}
}

void GameController::player_bid(int playerNr, chipstack chips)
{
	m_playersInRound[playerNr]->decFromWinnings(chips);
	if (m_playersInRound[playerNr]->getWinnings().isNegative) {
		m_playersInRound[playerNr]->setBankrupt();
	}
	m_pot_perPlayer[playerNr] = m_pot_perPlayer[playerNr] + chips;
	m_pot = m_pot + chips;
	if (m_pot_perPlayer[playerNr] > m_bid) {
		m_bid = m_pot_perPlayer[playerNr];
	}
}
