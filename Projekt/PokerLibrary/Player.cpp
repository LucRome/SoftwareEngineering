#include "pch.h"
#include "Player.h"
#include <iostream>

bool Player::bankrupt() const
{
    return m_bankrupt;
}

void Player::setBankrupt()
{
    m_bankrupt = true;
}
