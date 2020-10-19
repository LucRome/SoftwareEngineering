#pragma once
#include <vector>
#include "Player.h"
#include <memory>
class Output
{
public:
	Output();
	~Output();
	void rulesOut();

	void printTable(std::vector<std::shared_ptr<const Player>>& players);
};