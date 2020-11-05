#pragma once
#include<map>
#include "CardAndSymbols.h"
#include <string>

class StringMaps
{
public:
	std::string suit_string(suits s);
	std::string value_string(values v);

private:
	//Map for values <-> string
	std::map<values, std::string> valueMap = {
		{two, "2" },
		{three, "3" },
		{four, "4" },
		{five, "5" },
		{six, "6" },
		{seven, "7" },
		{eight, "8" },
		{nine, "9" },
		{ten, "10" },
		{jack, "J"},
		{queen, "Q" },
		{king, "K" },
		{ace, "A"},
		{v_none, "X"}
	};

	//TODO: find better strings
	//Map for suits <-> string
	std::map<suits, std::string> suitMap = {
		{diamonds, "D"},
		{clubs, "C"},
		{hearts, "H"},
		{spades, "S"},
		{s_none, "X"}
	};
};
