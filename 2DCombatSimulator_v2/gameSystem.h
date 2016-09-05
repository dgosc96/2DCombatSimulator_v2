#pragma once

#include <windows.h>
#include <iostream>
#include <conio.h>

#include "Level.h"

class gameSystem
{
public:
	gameSystem();
	~gameSystem();

	char gameLoop();
	void winner(char winner);

private:
	std::string _pathName;
	Level *_level = new Level;
};

