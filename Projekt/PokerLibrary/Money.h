#pragma once
#include <array>
#include <string>

const int nr_chipvalues = 6;

struct chipstack {
	//chip values: 5, 10, 20, 50, 100, 500
	chipstack();
	chipstack(std::array<int, nr_chipvalues> chips);
	std::array<int, nr_chipvalues> m_chips = { 0 }; //standard: all are 0
	static const std::array<int, nr_chipvalues> values;

public:
	chipstack& operator+(const chipstack& a) const;
	chipstack& operator-(const chipstack& a) const;
	bool operator<= (const chipstack& a) const;
	bool operator< (const int& a) const;
	bool operator> (const chipstack& a) const ;
	bool operator== (const int& a) const;
	int sum() const;

	static chipstack readChipstackFromConsole();
	std::string toString() const;
};