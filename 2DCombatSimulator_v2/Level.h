#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <random>

#include "unit.h"

const int NUM_ARMIES = 2;

class Level
{

public:
	char symbolArr[NUM_ARMIES];

	
	Level();
	~Level();

	bool load(std::string LevelPath);
	
	void Print();
	void printNumofUnits();

	void moveUnit(unit *unit, int targetX, int targetY);
	bool processMove(unit *unit);

	int update();
	void shuffleArmies();

	bool battle(unit *attacker, unit *defender );


private:
	
	std::random_device::result_type _seed = std::random_device()();
	std::mt19937 *_randomEngine = new std::mt19937(_seed);

	std::vector<std::string> _map;
	std::vector<std::vector<unit *> > _unitGrid;
	std::vector<unit *> _armies[NUM_ARMIES];
	
	void _setSymbolArr();
	
};

