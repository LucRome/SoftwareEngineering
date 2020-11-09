#include "pch.h"
#include "DrawResolver.h"
#include "Player_Besthand_struct.h"

// allways just compare player(last in vector) to first in vector(first and the others are the same)

//TODO: kl�ren ob immer highestCard als n�chstes oder einfach draw
void DrawResolver::resolveDraws(std::vector<playerNBestHand>& players_besthands, winTypes drawCase)
{
	
	switch (drawCase)
	{
	case highCard:
		resolveHighCard(players_besthands);
		break;
	case pair:
		resolvePair(players_besthands);
		break;
	case twoPair:
		resolveTwoPair(players_besthands);
		break;
	case threeOfAKind:
		resolveThreeOfAKind(players_besthands);
		break;
	case straight:
		resolveStraight(players_besthands);
		break;
	case flush:
		resolveFlush(players_besthands);
		break;
	case fullHouse:
		resolvefullHouse(players_besthands);
		break;
	case fourOfAKind:
		resolveFourOfAKind(players_besthands);
		break;
	case straightFlush:
		resolveStraightFlush(players_besthands);
		break;
	case royalFlush:
		//always a draw
		resolveHighCard(players_besthands);
		break;
	default:
		break;
	}
}

void DrawResolver::resolveHighCard(std::vector<playerNBestHand>& players_besthands)
{
	int playerNr = players_besthands.size() - 1;
	values opponent = players_besthands[0].besthand.HighCard.value;
	values own = players_besthands[playerNr].besthand.HighCard.value;
	bool cont = true; //if nextlowercard needs to be evalued
	while (cont) {
		if (resolveValues(players_besthands, own, opponent)) {
			cont = false;
		}
		else { //draw -> interpret lowCard
			//determine lowercard of opponent
			if (opponent == players_besthands[0].player->getHand().firstCard.value) {
				opponent = players_besthands[0].player->getHand().secondCard.value;
			}
			else
			{
				opponent = players_besthands[0].player->getHand().firstCard.value;
			}
			//determine lowercard of player
			if (opponent == players_besthands[playerNr].player->getHand().firstCard.value) {
				opponent = players_besthands[playerNr].player->getHand().secondCard.value;
			}
			else
			{
				opponent = players_besthands[playerNr].player->getHand().firstCard.value;
			}
		}
	}
}

void DrawResolver::resolvePair(std::vector<playerNBestHand>& players_besthands)
{
	int playerNr = players_besthands.size() - 1;
	//first check pair
	values opponent = players_besthands[0].besthand.PairCard;
	values own = players_besthands[playerNr].besthand.PairCard;

	if (!resolveValues(players_besthands, own, opponent)) { //draw
		//nextStep:: check HighCards
		resolveHighCard(players_besthands);
	}
}

void DrawResolver::resolveTwoPair(std::vector<playerNBestHand>& players_besthands)
{
	int playerNr = players_besthands.size() - 1;
	//first: higher pair
	values opponent = players_besthands[0].besthand.TwoPairCards[0];
	values own = players_besthands[playerNr].besthand.TwoPairCards[0];
	if (!resolveValues(players_besthands, own, opponent)) {
		//then: lower pair
		values opponent = players_besthands[0].besthand.TwoPairCards[1];
		values own = players_besthands[playerNr].besthand.TwoPairCards[1];

		if (!resolveValues(players_besthands, own, opponent)) {//next: highCards
			resolveHighCard(players_besthands);
		}
	}
}

void DrawResolver::resolveThreeOfAKind(std::vector<playerNBestHand>& players_besthands)
{
	int playerNr = players_besthands.size() - 1;
	values opponent = players_besthands[0].besthand.ThreeOfAKindCard;
	values own = players_besthands[playerNr].besthand.ThreeOfAKindCard;
	if (!resolveValues(players_besthands, own, opponent)) { //next: highCards (if pair were there it would be a full house)
		resolveHighCard(players_besthands);
	}
}

void DrawResolver::resolveStraight(std::vector<playerNBestHand>& players_besthands)
{
	int playerNr = players_besthands.size() - 1;
	values opponent = players_besthands[0].besthand.StraightHighestCard.value;
	values own = players_besthands[playerNr].besthand.StraightHighestCard.value;
	if (!resolveValues(players_besthands, own, opponent)) { // next: HighCard
		resolveHighCard(players_besthands);
	}
	
}

void DrawResolver::resolveFlush(std::vector<playerNBestHand>& players_besthands)
{
	//TODO: resolve Flush
}

void DrawResolver::resolvefullHouse(std::vector<playerNBestHand>& players_besthands)
{
	int playerNr = players_besthands.size() - 1;
	//first: threeOfAKinds
	values opponent = players_besthands[0].besthand.FullHouseCards[0];
	values own = players_besthands[playerNr].besthand.FullHouseCards[0];
	if (!resolveValues(players_besthands, own, opponent)) { // next: Pairs
		values opponent = players_besthands[0].besthand.FullHouseCards[1];
		values own = players_besthands[playerNr].besthand.FullHouseCards[1];
		if (!resolveValues(players_besthands, own, opponent)) { // next: HighCard
			resolveHighCard(players_besthands);
		}
	}
}

void DrawResolver::resolveFourOfAKind(std::vector<playerNBestHand>& players_besthands)
{
	int playerNr = players_besthands.size() - 1;
	values opponent = players_besthands[0].besthand.FourOfAKindCard;
	values own = players_besthands[playerNr].besthand.FourOfAKindCard;
	if (!resolveValues(players_besthands, own, opponent)) { // next: HighCard
		resolveHighCard(players_besthands);
	}
}

void DrawResolver::resolveStraightFlush(std::vector<playerNBestHand>& players_besthands)
{
	int playerNr = players_besthands.size() - 1;
	values opponent = players_besthands[0].besthand.StraightFlushHighestCard.value;
	values own = players_besthands[playerNr].besthand.StraightFlushHighestCard.value;
	if (!resolveValues(players_besthands, own, opponent)) { // next: HighCard
		resolveHighCard(players_besthands);
	}
}

bool DrawResolver::resolveValues(std::vector<playerNBestHand>& players_besthands, values own, values opponent)
{
	if (opponent > own) { //lost
		eraseLastOne(players_besthands);
		return true;
	}
	else if (opponent < own) { //won
		eraseAllButLastOne(players_besthands);
		return true;
	}
	else {//draw
		resolveHighCard(players_besthands);
		return false;
	}
}

void DrawResolver::eraseLastOne(std::vector<playerNBestHand>& players_besthands)
{
	players_besthands.erase(players_besthands.begin() + players_besthands.size()-1);
}

void DrawResolver::eraseAllButLastOne(std::vector<playerNBestHand>& players_besthands)
{
	playerNBestHand& temp = players_besthands[players_besthands.size() - 1]; //last one
	players_besthands.clear();
	players_besthands.push_back(temp);
}