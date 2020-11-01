#pragma once
#include <GameController.h>
#include "pch.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MockPlayer.h"
using namespace testing;


class GCFriend :
    public GameController
{
public:
    GCFriend(std::vector<std::shared_ptr<Player>> players, int max, chipstack bigBlind, chipstack smallBlind);
    ~GCFriend();
    void bidding(int playerNr, chipstack chipstackPlayer);
    bool isPotSame();
    plays playersNextMove(int playerNr);
};

