#pragma once
#include <GameController.h>
#include "pch.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MockPlayer.h"
using namespace testing;


// This class is FriendClass to GameController
// Allows to test the private functions of GameController

class GCFriend :
    public GameController
{
public:
    GCFriend(std::vector<std::shared_ptr<Player>> players, int max, chipstack bigBlind, chipstack smallBlind);
    ~GCFriend();
    void bidding(int playerNr, chipstack chipstackPlayer);  //allows in Tests to let one Player to bid

    bool isPotSame();                                       //allows in tests to check if all players bid 
                                                            //the same amount of money

    plays playersNextMove(int playerNr);                    //allows in tests to return the evaluated next move of the player
};

