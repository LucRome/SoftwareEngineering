#pragma once
#include <string>

//the possible suits and values (print symbols should be added by the UI component)
enum suits
{
	diamonds, clubs, hearts, spades, none //none: not yet assigned
};

enum values {
	two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace, none
	//none: not yet assigned
};

//for Rules: maybe add operators/functions for smaller/bigger/...

struct card { //suits, value
	suits suit;
	values value;
};