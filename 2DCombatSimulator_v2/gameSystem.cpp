#include "gameSystem.h"



gameSystem::gameSystem(){	
	std::string pathName;
	std::string defaultLvl = "default.txt";
	bool breakLoop = false;
	while (!breakLoop){
		std::cout << "1. Load default level\n2. Load custom level\n3. Exit\n\nInput:";
		switch (_getch()){
		case '1':
			system("cls");
			if (_level->load(defaultLvl)){
				perror(defaultLvl.c_str());
				std::cout << "\nPress any key to exit...\n";
				_getch();
				exit(1);
			}
			breakLoop = true;
			break;
		case '2':
			system("cls");
			std::cout << "Type level path to load custom level: \n";

			std::cin >> pathName;

			if (_level->load(pathName)){
				perror(pathName.c_str());
				std::cout << "\nPress any key to load default level...\n";
				_getch();

				if (_level->load(defaultLvl)){
					perror(defaultLvl.c_str());
					std::cout << "\nPress any key to exit...\n";
					_getch();
					exit(1);
				}
			}
			breakLoop = true;
			break;
		case '3':
			exit(0);
		default:
			break;
		}
		system("cls");
	}
	system("cls");
}


gameSystem::~gameSystem()
{
	delete _level;
}


char gameSystem::gameLoop() 
{
	while (true)
	{
		_level->Print();
		int isOver = _level->update();

		_level->shuffleArmies();

		Sleep(100);
		system("cls");

		if (isOver < NUM_ARMIES)
		{
			return _level->symbolArr[isOver];
		}

	}
	

}
void gameSystem::winner(char winner)
{
	_level->Print();
	std::cout << std::endl << "The winner is team: " << winner << " !!!" << std::endl;
}