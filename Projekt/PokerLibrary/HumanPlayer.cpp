#include "pch.h"
#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(card pFirstCard, card pSecondCard, chipstack pStartingChips) {
	setHand(pFirstCard, pSecondCard);
	setWinnings(pStartingChips);
}
