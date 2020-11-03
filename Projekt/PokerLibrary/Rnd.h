#pragma once


#ifndef RND

#define RND
#include <random>
#include <time.h>
namespace rnd {
	extern std::mt19937 mt_rand;
}
#endif // !RND


int randomNr(int max = INT16_MAX);
