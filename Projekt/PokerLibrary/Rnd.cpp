#include "pch.h"
#include "Rnd.h"

namespace rnd {
	extern std::mt19937 mt_rand(time(NULL));
}

int randomNr(int max)
{
	int random = 0;
	if (max != 0) {
		random = rnd::mt_rand() % max;
	}
	return random;
}
