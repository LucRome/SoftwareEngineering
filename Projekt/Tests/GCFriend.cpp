#include "GCFriend.h"


GCFriend::GCFriend(std::vector<std::shared_ptr<Player>> players, int max, chipstack bigBlind, chipstack smallBlind)
	:GameController(players, max, bigBlind, smallBlind)
{
}

GCFriend::~GCFriend()
{
}

void GCFriend::bidding(int playerNr, chipstack chipstackPlayer)
{
	player_bid(playerNr, chipstackPlayer);
}

bool GCFriend::isPotSame()
{
	return allPlayersSamePot();
}

plays GCFriend::playersNextMove(int playerNr)
{
	return movePlayer(playerNr);
}
