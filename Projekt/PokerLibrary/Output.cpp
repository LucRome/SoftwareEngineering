#include "pch.h"
#include "Output.h"
#include <iostream>
#include <fstream>
#include <string>


Output::Output()
{

}

Output::~Output()
{

}

void Output::rulesOut()
{
	std::ifstream file;
	file.open("Rules.txt");
	std::string line;
	while(std::getline(file, line)){
		std::cout << line << std::endl;
	}
	file.close();
}
