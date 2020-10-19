#pragma once
#include <array>
enum chipvalues{_5, _10, _20, _50, _100, _500};


const int nr_chipvalues = 6;

struct chipstack {
	//chip values: 5, 10, 20, 50, 100, 500
	std::array<int, nr_chipvalues> m_chips = { 0 }; //standard: all are 0

public:
	chipstack& operator+(const chipstack& a);
	chipstack& operator-(const chipstack& a);
	static chipstack readChipstackFromConsole();
};