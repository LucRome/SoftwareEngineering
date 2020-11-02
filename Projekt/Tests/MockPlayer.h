#pragma once
#include <Player.h>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace ::testing; 

//This is a Mocking Class of Player
//allows in Tests to mock some PlayerFunctions (here: play and Bankrupt)
//also it is possible to construct simple players without logic for specific test cases

class MockPlayer :
    public Player
{
public:
    MockPlayer(chipstack pStartingChips, std::string pName);
    ~MockPlayer();
    MOCK_METHOD2(play, outPlay(chipstack, std::vector<plays>));
    MOCK_METHOD0(bankrupt, bool());
};

