#pragma once
#include <memory>

//forward declarations
class Player;
struct BestHand;

struct playerNBestHand { //combines players and besthands (only as reference)
	std::shared_ptr<Player> player;
	BestHand besthand;
};