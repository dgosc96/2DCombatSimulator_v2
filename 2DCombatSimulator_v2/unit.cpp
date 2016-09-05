#include "unit.h"



unit::unit(char symbol, int army, int health, int damage, int defence, int X, int Y)
{
	_symbol = symbol;
	_army = army;
	_health = health;
	_damage = damage;
	_defence = defence;
	_X = X;
	_Y = Y;

}

int unit::takeDamage(int amount)
{
	_health -= amount;
	if (_health <= 0)
		return 1;

	else
		return 0;


}


char unit::getMove(std::vector <unit *> armies[], int numArmies, std::vector<std::string> &levelData)
{
	char returnKey = NULL;
	unit *closestEnemy = _getClosestEnemy(armies, numArmies);

	bool **isActiveTileGrid = new bool*[levelData.size()];
	for (int y = 0; y < levelData.size(); y++)
	{
		isActiveTileGrid[y] = new bool[levelData[0].size()];
		for (int x = 0; x < levelData[0].size(); x++)
		{
			isActiveTileGrid[y][x] = false;
		}
	}

	if (closestEnemy != nullptr)
	{
		_tile mainTile, destinationTile;

		mainTile.X = _X;
		mainTile.Y = _Y;



		destinationTile.X = closestEnemy->returnX();
		destinationTile.Y = closestEnemy->returnY();



		_tile closestTile = _returnClosestTile(levelData, isActiveTileGrid, mainTile, mainTile, destinationTile, closestEnemy->returnSymbol());



		if (closestTile.X == 0 && closestTile.Y == 0)
		{
			returnKey = 'b';
		}

		_tile difference;
		difference.X = closestTile.X - mainTile.X;
		difference.Y = closestTile.Y - mainTile.Y;


		if (difference.X == 0)
		{
			switch (difference.Y)
			{
			case -1:
				returnKey = 'w';
				break;
			case 1:
				returnKey = 's';
				break;
			default:
				break;
			}

		}
		else if (difference.Y == 0)
		{
			switch (difference.X)
			{
			case -1:
				returnKey = 'a';
				break;
			case 1:
				returnKey = 'd';
				break;
			default:
				break;
			}

		}

	}
	else
	{
		returnKey = ' ';
		
	}



	for (int i = 0; i < levelData.size(); ++i) {
		delete[] isActiveTileGrid[i];
	}
	delete[] isActiveTileGrid;


	return returnKey;
}

_tile unit::_returnClosestTile(std::vector<std::string> &levelData, bool *tileGrid[], _tile &startTile, _tile &activeTile, _tile &destinationTile, char enemySymbol)
{
	int min_fScore = INT_MAX;
	int fScore = 0;
	int gScore = 0;
	int hScore = 0;
	_tile dir, min_fScoreTile;

	if (activeTile.X != 0 && activeTile.Y != 0)
	{

		tileGrid[activeTile.Y][activeTile.X] = true;
		for (int i = 0; i < 4; i++)
		{
			switch (i)
			{
			case 0:
				dir.Y = activeTile.Y - 1;
				dir.X = activeTile.X;
				break;

			case 1:
				dir.Y = activeTile.Y + 1;
				dir.X = activeTile.X;
				break;

			case 2:
				dir.Y = activeTile.Y;
				dir.X = activeTile.X - 1;
				break;

			case 3:
				dir.Y = activeTile.Y;
				dir.X = activeTile.X + 1;
				break;

			default:
				break;
			}

			if ((levelData[dir.Y][dir.X] == ' ' || levelData[dir.Y][dir.X] == enemySymbol) && (tileGrid[dir.Y][dir.X] == false))
			{
				gScore = abs(startTile.Y - dir.Y) + abs(startTile.X - dir.X);
				hScore = abs(destinationTile.Y - dir.Y) + abs(destinationTile.X - dir.X);

				fScore = gScore + hScore;

				if (fScore < min_fScore)
				{
					min_fScore = fScore;
					min_fScoreTile.Y = dir.Y;
					min_fScoreTile.X = dir.X;
					min_fScoreTile.fScore += min_fScore;
				}
				else if (fScore == min_fScore)
				{
					_tile tile1 = _returnClosestTile(levelData, tileGrid, startTile, min_fScoreTile, destinationTile, enemySymbol);

					_tile tile2 = _returnClosestTile(levelData, tileGrid, startTile, dir, destinationTile, enemySymbol);

					if (tile1.fScore < tile2.fScore)
					{
						min_fScoreTile.fScore = tile1.fScore;
					}
					else
					{
						min_fScoreTile.Y = dir.Y;
						min_fScoreTile.X = dir.X;
						min_fScoreTile.fScore += tile2.fScore;
					}
					
				}

			}

		}
	}
	return min_fScoreTile;


}


unit *unit::_getClosestEnemy(std::vector <unit *> armies[], int numArmies)
{
	unit *closestEnemy = nullptr;
	int closestDistance = INT_MAX;
	int enemyX, enemyY;
	int distance;

	for (int i = 0; i < numArmies; i++)
	{
		if (i != _army && !armies[i].empty())
		{
			for (int j = 0; j < armies[i].size(); j++)
			{
				if (armies[i][j] != nullptr)
				{
					enemyX = armies[i][j]->returnX();
					enemyY = armies[i][j]->returnY();

					distance = abs(enemyX - _X) + abs(enemyY - _Y);

					if (distance < closestDistance)
					{
						closestEnemy = armies[i][j];
						closestDistance = distance;
					}
				}
				else
				{
					return nullptr;
				}

			}
		}
	}

	return closestEnemy;


}