#include "Level.h"



Level::Level()
{



}

Level::~Level() {
	for (int i = 0; i < NUM_ARMIES; i++)
	{
		for (int j = 0; j < _armies[i].size(); j++)
		{
			delete _armies[i][j];
		}
	}

	delete _randomEngine;
}

bool Level::load(std::string LevelPath)
{ 
	std::ifstream LevelFile;
	LevelFile.open(LevelPath);
	if (LevelFile.fail())
	{
		
		
		return true;
	}




	std::uniform_int_distribution<int> randAdditionalHealth(0, 20);
	std::uniform_int_distribution<int> randDefence(0, 10);

	std::string inputLine;

	while (std::getline(LevelFile, inputLine))
	{
		_map.push_back(inputLine);

		_unitGrid.push_back(std::vector <unit *>());
		_unitGrid.back().resize(inputLine.size(), nullptr);

		static int y = 0;
		for (int x = 0; x < inputLine.size(); x++)
		{

			switch (inputLine[x])
			{
			case 'O':
				_armies[0].push_back(new unit('O', 0, 152 + randAdditionalHealth(*_randomEngine), 20, randDefence(*_randomEngine), x, y));
				_unitGrid[y][x] = _armies[0].back();
				break;

			case 'K':
				_armies[1].push_back(new unit('K', 1, 80 + (2 * randAdditionalHealth(*_randomEngine)), 30, randDefence(*_randomEngine), x, y));
				_unitGrid[y][x] = _armies[1].back();
				break;

			case '#':
			case ' ':
				break;

			default:
				std::cout << "WARNING: Unknown tile " << inputLine[x] << " at " << x << ", " << y << std::endl << "Press any key to exit..." << std::endl;

				_getch();
				exit(2);
			}

		}

		y++;
	}
	_setSymbolArr();
	shuffleArmies();

	return false;
}


void Level::Print()
{
	for (int i = 0; i < _map.size(); i++)
	{
		std::cout << _map[i] << std::endl;
	}

	printNumofUnits();

}

void Level::printNumofUnits()
{
	for (int i = 0; i < NUM_ARMIES; i++)
	{
		std::cout << "Number of " << symbolArr[i] << ": " << _armies[i].size()<<std::endl;
	}
}

void Level::moveUnit(unit *unit, int targetY, int targetX)
{

	
	 if (_map[targetY][targetX] == ' ')
	{
		_map[unit->returnY()][unit->returnX()] = ' ';
		_map[targetY][targetX] = unit->returnSymbol();

		_unitGrid[targetY][targetX] = unit;
		_unitGrid[unit->returnY()][unit->returnX()] = nullptr;

		unit->changeYX(targetY, targetX);
	}
	else if ((_map[targetY][targetX] != unit->returnSymbol()) && (unit->returnArmy() != _unitGrid[targetY][targetX]->returnArmy()))
	{
		if (battle(unit, _unitGrid[targetY][targetX]))
		{
			_map[targetY][targetX] = ' ';
			_unitGrid[targetY][targetX] = nullptr;
		}

	}




}

bool Level::processMove(unit *unit)
{
	char moveDirection = unit->getMove(_armies, NUM_ARMIES, _map);
	int targetY = unit->returnY();
	int targetX = unit->returnX();

	switch (moveDirection)
	{
	case 'w':
		targetY--;
		break;

	case 's':
		targetY++;
		break;

	case 'a':
		targetX--;
		break;

	case 'd':
		targetX++;
		break;
	case ' ':
		return true;
	default:
		return false;
		
	}

	moveUnit(unit, targetY, targetX);
	return false;
}

int Level::update()
{
	for (int i = 0; i < NUM_ARMIES; i++)
	{
		if (!_armies[i].empty())
		{
			for (int j = 0; j < _armies[i].size(); j++)
			{
				if (_armies[i][j] != nullptr)
				{
					if (processMove(_armies[i][j]))
					{
						return i;
					}
				
				}
				
			}
		}

	}
	return NUM_ARMIES + 1;
}


void Level::shuffleArmies()
{
	unit *tmp;
	for (int i = 0; i < NUM_ARMIES; i++)
	{
		for (int j = _armies[i].size() - 1; j > 1; j--)
		{
			std::uniform_int_distribution<int> randomSwap(0, j - 1);
			int swap = randomSwap(*_randomEngine);
			tmp = _armies[i][j];
			_armies[i][j] = _armies[i][swap];
			_armies[i][swap] = tmp;
		}

	}

}


bool Level::battle(unit *attacker, unit *defender)
{
	std::uniform_int_distribution<int> randDamage(0, attacker->returnDamage());

	if (defender->takeDamage(randDamage(*_randomEngine)) == 1)
	{
		for (int i = 0; i < _armies[defender->returnArmy()].size(); i++)
		{
			if (defender == _armies[defender->returnArmy()][i])
			{
				_armies[defender->returnArmy()][i] = _armies[defender->returnArmy()].back();
				_armies[defender->returnArmy()].pop_back();

				break;
			}
		}
		return true;
	}
	else if (defender->returnDefence() > 0)
	{
		defender->decreaseDefence();
	}
	return false;

}


void Level::_setSymbolArr() 
{
	for (int i = 0; i < NUM_ARMIES; i++)
	{
		symbolArr[i] = _armies[i][0]->returnSymbol();
	}

}