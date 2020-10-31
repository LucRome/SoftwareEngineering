#pragma once
#include "DeckOfCards.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace ::testing;

class MockRandom :
    public DeckOfCards
{
public:
    MOCK_METHOD1(randomNumberGenerator, int (int));
    MOCK_METHOD0(getRandomCard, card());

};

