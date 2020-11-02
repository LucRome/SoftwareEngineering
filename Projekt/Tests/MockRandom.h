#pragma once
#include "DeckOfCards.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
using namespace ::testing;

//this is a mock Class of GameController
//it is possible to mock some non-deterministic functions to return expected values

class MockRandom :
    public DeckOfCards
{
public:
    MOCK_METHOD1(randomNumberGenerator, int (int));
    MOCK_METHOD0(getRandomCard, card());

};

