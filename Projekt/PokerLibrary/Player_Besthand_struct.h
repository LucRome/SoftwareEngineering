#pragma once
#include <memory>
#include "Rules.h"

//forward declarations
class Player;
struct BestHand;

struct playerNBestHand { //combines players and besthands (only as reference)
	std::shared_ptr<Player> player;
	BestHand besthand;
};