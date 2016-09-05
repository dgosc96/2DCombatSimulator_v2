#pragma once
#include <vector>

struct _tile 
{ 
	int X = 0;
	int Y = 0; 
	int fScore = 0;
};
class unit
{

public:
	unit(char symbol,int army, int health, int damage, int defence, int X, int Y);
	
	char returnSymbol() { return _symbol; }
	int  returnHealth() { return _health; }
	int  returnDamage() { return _damage; }
	int  returnX()		{ return _X; }
	int  returnY()		{ return _Y; }
	int  returnArmy()	{ return _army; }
	int  returnDefence(){ return _defence; }

	int takeDamage(int amount);
	void changeYX(int Y, int X) { _X = X; _Y = Y; }
	char getMove(std::vector <unit *> armies[], int armieNum, std::vector<std::string> &levelData);
	void decreaseDefence() { _defence--; }

private:
	char _symbol;
	int _health, _damage, _X, _Y, _army, _defence;

	

	_tile _returnClosestTile(std::vector<std::string> &levelData,bool *tileGrid[] , _tile &startTile,  _tile &activeTile, _tile &destinatonTile, char enemySymbol);
	
	unit *_getClosestEnemy(std::vector <unit *> armies[], int armieNum);
	

};

