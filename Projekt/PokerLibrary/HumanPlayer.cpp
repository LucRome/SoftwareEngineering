#include "pch.h"
#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(card pFirstCard, card pSecondCard, chipstack pStartingChips) {
	hand[0] = pFirstCard;
	hand[1] = pSecondCard;
	winnings = pStartingChips;
}

hand HumanPlayer::getHand(){
	return playerHand;
}

HumanPlayer::setHand(card pFirstCard, card pSecondCard){
	playerHand.firstCard = pFirstCard;
	playerHand.secondCard = pSecondCard;
}

chipstack HumanPlayer::getWinnings() {
	return winnings;
}

HumanPlayer::setWinnings(chipstack pStartingChips) {
	winnings = pStartingChips;
}