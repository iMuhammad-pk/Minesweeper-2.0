#include "MainGame.h"
using namespace std;
using namespace sf;


void Beginner(MainGame*&basic,bool &level) {
	int gridsize = 9,defaultmine=10;
	int egridsize = 16,emines=50;
	bool darkmode = false,el=false;
	if (!level) {
		basic = new MainGame(darkmode, defaultmine, gridsize);
		level = true;
	}
	while (basic->winopencheck()) {
		basic->mainWindow();
		basic->eventmanager();
		if (basic->gamereset && !el) {
			gridsize = basic->gsize;
			defaultmine = basic->fixminecount;
			darkmode = basic->darkbool;
			delete basic;
			basic = new MainGame(darkmode, defaultmine, gridsize);
			basic->mainWindow();
			basic->eventmanager();
			continue;
		}
		else if (basic->gamereset && el) {
			defaultmine = basic->fixminecount;
			darkmode = basic->darkbool;
			delete basic;
		
			basic = new LevelExpert(darkmode, defaultmine, egridsize);
			basic->handle = true;
			basic->mainWindow();
			basic->eventmanager();
			continue;


		}
		if (basic->expert) {
			el = true;
			defaultmine = emines;
			darkmode = basic->darkbool;
			delete basic;
			basic = new LevelExpert(darkmode,defaultmine,egridsize);
			basic->handle = true;
			basic->mainWindow();
			basic->eventmanager();
			continue;
		}
		else if (basic->beginner) {
			el = false;
			gridsize = 10;
			defaultmine = basic->fixminecount;
			darkmode = basic->darkbool;
			delete basic;
			basic = new MainGame(darkmode, defaultmine, gridsize);
			basic->mainWindow();
			basic->eventmanager();
			continue;


		}

	}
}



void main() {
	MainGame* basic = nullptr;
	bool level = false;
	Beginner(basic,level);




	






	delete basic;
	system("pause=0");
}