#pragma once
#include <Player.h>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace ::testing; 

class MockPlayer :
    public Player
{
public:
    MockPlayer(chipstack pStartingChips, std::string pName);
    ~MockPlayer();
    MOCK_METHOD2(play, outPlay(chipstack, std::vector<plays>));
};

