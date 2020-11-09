#pragma once
#include <string>

//the possible suits and values (print symbols should be added by the UI component)
enum suits
{
	diamonds, clubs, hearts, spades, s_none
};

enum values {
	two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace, v_none
};

//for Rules: maybe add operators/functions for smaller/bigger/...

struct card { //suits, value
	suits suit = s_none;
	values value = v_none;
	bool operator== (const card& c2) const {
		return this->suit == c2.suit && this->value == c2.value;
	}
};

struct hand { //suits, value
	card firstCard;
	card secondCard;
};