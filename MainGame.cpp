#include "MainGame.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <time.h>
#include <chrono>
using namespace std;
using namespace sf;



/***************Constructors*********************************************/
MainGame::MainGame() {
	srand(time(0));
	windowp = new RenderWindow(VideoMode(500, 600), "Minesweeper v2.5", Style::Titlebar | Style::Close);
	totalscore = time1 = minecount =fakeminecount= 0;
	gamereset = gamewin = gameover= darkbool=handle=false;
	sx = 222; sy = 41; /*Smiley Coords*/
	bx = 40; by = 50; bx1 = 360; /*Border and Border 1 Coords*/
	sizex = 85; sizey = 50; /*Border Size*/
	fx = 361; fy = 60; fx1 = 41; /*Font , Font 1 Coords*/
	smousex = 280; smousex1 = 210; smousey = 100; smousey1 = 30;
	gsize = 9; /*Grid Size*/
	fixminecount = 10; /*Default Mines*/
	framerate = 30; /*FPS*/
	op = nullptr;
	di = nullptr;
	windowp->setFramerateLimit(framerate); /*Setting appropiate FPS*/
	grid = new Sprite * [gsize + 1]; /* Allocating Memory to sprite*/
	gridmine = new int* [gsize + 1]; /*Allocating Memorty to sprite*/
	for (int row = 0; row < gsize; row++) {
		gridmine[row] = new int[gsize] {0};
		grid[row] = new Sprite[gsize];
	}
	loadimgandfont();
}

MainGame::MainGame(bool dark, int mine, int gsize1) {
	srand(time(0));
	windowp = new RenderWindow(VideoMode(500, 600), "Minesweeper v2.5", Style::Titlebar | Style::Close);
	totalscore = time1 = minecount = 0;
	gamereset = gamewin = gameover= false;
	darkbool = dark;
	fixminecount = mine;
	gsize = gsize1; /*Grid Size*/
	handle = false;
	sx = 222; sy = 41; /*Smiley Coords*/
	bx = 40; by = 50; bx1 = 360; /*Border and Border 1 Coords*/
	sizex = 85; sizey = 50; /*Border Size*/
	fx = 361; fy = 60; fx1 = 41; /*Font , Font 1 Coords*/
	smousex = 280; smousex1 = 210; smousey = 100; smousey1 = 30;
	framerate = 30; /*FPS*/
	op = nullptr;
	di = nullptr;
	windowp->setFramerateLimit(framerate); /*Setting appropiate FPS*/
	grid = new Sprite * [gsize + 1]; /* Allocating Memory to sprite*/
	gridmine = new int* [gsize + 1]; /*Allocating Memorty to sprite*/
	for (int row = 0; row < gsize; row++) {
		gridmine[row] = new int[gsize] {0};
		grid[row] = new Sprite[gsize];
	}
	loadimgandfont();
}

/***********Window Handling Functions*************************************/

void MainGame::loadimgandfont() {
	int index = 1, randtemp = 0;
	/*Loading Games Logo*/
	iconimg.loadFromFile("images/Logo.png");
	windowp->setIcon(iconimg.getSize().x, iconimg.getSize().y, iconimg.getPixelsPtr());
	fontstyle.loadFromFile("fonts/led.ttf");
	defaultimg[0].loadFromFile("images/cell.png"); defaultimg[2].loadFromFile("images/minered.png"); defaultimg[1].loadFromFile("images/emptycell.png"); defaultimg[3].loadFromFile("images/mine.png"); defaultimg[4].loadFromFile("images/minex.png");
	Smileyimg[0].loadFromFile("images/smileyn.png"); Smileyimg[1].loadFromFile("images/smileya.png");
	Smileyimg[2].loadFromFile("images/smileyo.png"); Smileyimg[3].loadFromFile("images/smileyw.png");
	Numbers[1].loadFromFile("images/1.png"); Numbers[2].loadFromFile("images/2.png");
	Numbers[3].loadFromFile("images/3.png"); Numbers[4].loadFromFile("images/4.png");
	Numbers[5].loadFromFile("images/5.png"); Numbers[6].loadFromFile("images/6.png");
	Numbers[7].loadFromFile("images/7.png"); Numbers[8].loadFromFile("images/8.png");
	Numbers[9].loadFromFile("images/9.png");
	flagimg.loadFromFile("images/flag.png");
	backimg.loadFromFile("images/backimg.png");
	if (darkbool) {
		backimg.loadFromFile("images/dbackimg.png");
		background.setTexture(backimg);
		darkbool = false;
	}
	else {
		background.setTexture(backimg);
	}
	/*Random Mines Setting*/
	for (int r = 0; r < gsize; r++) {
		for (int c = 0; c < gsize; c++) {
			if (fixminecount > 10) {
				randtemp = rand() % 4+1;
			}
			else {
				randtemp = rand() % 4;
			}

			
			if (randtemp ==1 && index <= fixminecount) {
				if (index == fixminecount) {
					gridmine[r][c] = 1;
					r = gsize;
					break;
				}
				gridmine[r][c] = 1;
				index++;	
			}
		}}
	/*Counting Number of Mines*/
	for (int r1 = 0; r1 < gsize; r1++) {
		for (int c1 = 0; c1 < gsize; c1++) {
			if (gridmine[r1][c1] == 1) {
				fakeminecount++;
			}
		}
	}
	Smiley.setTexture(Smileyimg[0]);
}

void MainGame::renderingmain() {
	float time = 0.09;
	int fontsize = 32;
	RectangleShape Border, Border1;
	Sprite MenuBorder;
	string str, str1;
	/*Time Setting*/
	if (!gameover && !gamewin) {
		time1 = elapsed.asSeconds();
	}
	/*Smiley Setting*/
	if (Smiley.getTexture() == &Smileyimg[1] && Smiley.getTexture() != &Smileyimg[2] && Smiley.getTexture() != &Smileyimg[3]) {
		sleep(seconds(time));
		Smiley.setTexture(Smileyimg[0]);
	}
	Smiley.setPosition(sx, sy);
	/*Setting up Timerr/FakeMineScore Font*/
	if (time1 == 0 || time1 < 10 || time1 >= 10 && time1 < 100) {
		if (time1 == 0) {
			str = "000";
		}
		else if (time1 < 10) {
			str = "00";
			str += to_string(time1);
		}
		else if (time1 >= 10) {
			str = "0";
			str += to_string(time1);
		}
	}
	else {
		str = to_string(time1);
	}
	/*Fake Mine Counter*/
	if (fakeminecount == 0 || fakeminecount < 10 || fakeminecount >= 10 && fakeminecount < 100) {
		if (fakeminecount == 0) {
			str1 = "000";
		}
		else if (fakeminecount < 10) {
			str1 = "00";
			str1 += to_string(fakeminecount);
		}
		else if (fakeminecount >= 10) {
			str1 = "0";
			str1 += to_string(fakeminecount);
		}
	}
	else {
		str1 = to_string(fakeminecount);
	}

	/*Border*/
	Border.setFillColor(Color::Black); Border.setSize(Vector2f(sizex, sizey));
	Border.setPosition(bx, by);
	Border1.setFillColor(Color::Black); Border1.setSize(Vector2f(sizex, sizey));
	Border1.setPosition(bx1, by);
	/*Menu Border*/
	Font style1; style1.loadFromFile("fonts/arial.ttf");
	Texture temp; temp.loadFromFile("images/titlebox.png");
	MenuBorder.setTexture(temp); MenuBorder.setPosition(0, 0);

	/*Score and Timer Text edit*/
	Text fortext(str, fontstyle, fontsize), fortext1(str1, fontstyle, fontsize);
	fortext.setFillColor(Color::Red);
	fortext.setPosition(fx, fy);
	fortext1.setFillColor(Color::Red);
	fortext1.setPosition(fx1, fy);

	/*Menu bar Text*/
	str = " Difficulty \t Options \t    Help";
	Text fortext2(str, style1, 10);
	fortext2.setFillColor(Color::Black);
	fortext2.setPosition(0, 0);



	/*Drawing*/
	windowp->draw(Smiley);
	windowp->draw(Border);
	windowp->draw(fortext1);
	windowp->draw(Border1);
	windowp->draw(fortext);
	windowp->draw(MenuBorder);
	windowp->draw(fortext2);




}
/*Used By Event Manager*/
void MainGame::BoundCheck(int& bx, int& by, int mx, int my) {
	FloatRect bound;
	for (int row = 0; row < gsize; row++) {
		for (int col = 0; col < gsize; col++) {
			bound = grid[row][col].getGlobalBounds();
			if (bound.contains(mx, my)) {
				bx = row;
				by = col;
				return;
			}
		}
	}

}

/*++++Event Manager+++++++*/
void MainGame::eventmanager() {
	int mousex = 0, mousey = 0, boundx = 0, boundy = 0;
	/*Loop to catch event of Program*/
	while (windowp->pollEvent(press)) {
		mousex = press.mouseButton.x;
		mousey = press.mouseButton.y;
		/*Title Window Config*/
		if (press.type == Event::Closed) {
			windowp->close();
			return;
		}
		/*Keyboard Config*/
		if (press.key.code == Keyboard::Escape) {
			windowp->close();
			return;
		}
		/*Mouse Config*/
		if (press.type == Event::MouseButtonPressed) {
			/*Left Function*/
			if (press.mouseButton.button == Mouse::Left) {

				
				/*Game over check*/
				if (gameover == true) {
					/*Smiley Click coords check*/
					if (mousex <= smousex && mousey <= smousey && mousex >= smousex1 && mousey >= smousey1) {
						gamereset = true;
						return;
					}
					else {
						return;
					}
				}
				else {
					/*Clicking Smiley Resetting Game*/
					if (mousex <= smousex && mousey <= smousey && mousex >= smousex1 && mousey >= smousey1) {
						gamereset = true;
						return;
					}
					else if (mousex <= 115 && mousey <= 15 && mousex >= 55) {
						optionsg(mousex, mousey);
						return;
					}
					else if (mousex <= 50 && mousey <= 15 && mousex >= 0) {
						expertlevel(mousex, mousey);
						return;
					}
					else if (mousex <= 170 && mousey <= 25 && mousex >115) {
						system("CLS");
						cout << "===============================HELP=============================================================================\n";
						cout << "->Minesweeper is a prbablity game where a user clicks on a cell avoiding a mine.								  \n";
						cout << "->Numbers tell you how many mines there adjacent to the number.												  \n";
						cout << "->If you find any bugs feel free to contact  developer.														  \n";
						cout << "->In the difficulty menu you can select 9x9(beginner) or 16x16(expert)			                                 \n";
						cout << "->In options if you want darkmode press the green button and close	the option window to take affect.\n";
						cout << "->viceVersa for red button and the mine button(selecting amount of mines)		                                 \n";
						cout << "================================================================================================================\n";

						return;
					}


					else if (mousex <= 500 && mousex >= 0 && mousey <= 145 && mousey>=16 && !handle) {
						return;
					}
					else if (mousex <= 500 && mousex >= 390 && mousey<=600&& mousey>=16 && !handle) {
						return;
					}
					else if (mousex <= 100 && mousex >= 0 && mousey <= 600 && mousey >= 16 && !handle) {
						return;
					}

					/*Changing Smiley Expression*/
					Smiley.setTexture(Smileyimg[1]);
					windowp->draw(Smiley);
					windowp->display();
					/*Calling Bound Function to translate mouse axis*/
					BoundCheck(boundx, boundy, mousex, mousey);
					gridinput(boundx, boundy);

				}
				return;
			}
			/*Right Function*/
			else if (press.mouseButton.button == Mouse::Right) {
				mousex = press.mouseButton.x;
				mousey = press.mouseButton.y;
				BoundCheck(boundx, boundy, mousex, mousey);
				flagcheck(boundx, boundy);
			}
		}

	}
}

/*!===================================================================================*/
/*!===================================================================================*/

/*!***************************GAME HANDLING FUNCTIONS *********************************/

void MainGame::gridmake() {
	float gridx = 0, gridy = 0;
	bool checkimg = false, checknum = false;
	for (int i = 0; i < gsize; i++) {
		for (int c = 0; c < gsize; c++) {
			/*Calling Number and image check to see if gridcell contains a number or its empty*/
			gridtextcheck(checkimg, i, c);
			NumberCheck(checknum, i, c);
			if (!checkimg && !checknum && grid[i][c].getTexture() != &flagimg && grid[i][c].getTexture() != &defaultimg[2] && grid[i][c].getTexture() != &defaultimg[3] && grid[i][c].getTexture() != &defaultimg[4]) {
				grid[i][c].setTexture(defaultimg[0]);
				gridx = (i * 32) + 100;
				gridy = (c * 32) + 150;
				grid[i][c].setPosition(gridx, gridy);
			}
			else {
				gridx = (i * 32) + 100;
				gridy = (c * 32) + 150;
				grid[i][c].setPosition(gridx, gridy);
			}
			checkimg = checknum = false;
		}
	}

	/*Drawing the grid every frame*/
	for (int r = 0; r < gsize; r++) {
		for (int c = 0; c < gsize; c++) {
			windowp->draw(grid[r][c]);
		}
	}

}

void MainGame::gridinput(int x1, int y1) {
	bool checkm = false, checknum = false;
	int randx = rand() % 5, randy = rand() % 5;
	/*Mine Reveal Setting*/
	if (gridmine[x1][y1] == 1) {
		grid[x1][y1].setTexture(defaultimg[2]);
		Revealmines(x1, y1);
		gameover = true;
		Smiley.setTexture(Smileyimg[2]);
		return;
	}
	/*Revealing Numbers Settings*/
	gridcheck(x1, y1);
	gridtextcheck(checkm, x1, y1);
	NumberCheck(checknum, x1, y1);
	if (!checkm && !checknum) {
		grid[x1][y1].setTexture(defaultimg[1]);
	}
	if (x1 + randx >= gsize || y1 + randy >= gsize) {
		if (x1 + randx >= gsize)return;
		if (y1 + randy >= gsize)return;
	}
	else if (randx == 0 || randy == 0)return;

	int totalx = x1 + randx;
	int totaly = y1 + randy;
	for (int i = x1; i < totalx; i++) {
		for (int c = y1; c < totaly; c++) {
			gridcheck(i, c);
		}
	}




}

void MainGame::Revealmines(int x5, int y5) {
	for (int row = 0; row < gsize; row++) {
		for (int col = 0; col < gsize; col++) {
			if (row == x5 && col == y5) {
				continue;
			}
			else if (gridmine[row][col] == 1 && grid[row][col].getTexture() != &flagimg) {
				grid[row][col].setTexture(defaultimg[3]);
			}
			else if (grid[row][col].getTexture() == &flagimg && gridmine[row][col] != 1) {
				grid[row][col].setTexture(defaultimg[4]);
			}
		}
	}
}

void MainGame::optionsg(int x6, int y6) {
	op = new optionsmenu;
	darkbool = false;
	while (op->owindow()) {
		op->omain();
		op->oevent();
		if (op->darkmode) {
			if (op->mine1) {
				fixminecount = op->mine();
				op->mine1 = false;
			}
			darkbool = true;
			continue;
		}
		else if (op->mine1) {
			fixminecount = op->mine();
			op->mine1 = false;
			continue;
		}
	}
	gamereset = true;
	return;
}

void MainGame::expertlevel(int mousex,int mousey) {
	di = new difficulty;
	expert = beginner = false;
	while (di->iswin()) {
		di->mainrender();
		di->event();
		if (di->exp) {
			expert = true;
		}
		else if (di->beg) {
			beginner = true;
	
		}
	}
	return;
}
/*====GAME HANDING CHECKS===========*/
void MainGame::gridcheck(int x2, int y2) {
	/*Will check a 3 by 3 boundary of a coordinate*/
	int countm = 0, row1 = 1, row2 = 2, column1 = 1, column2 = 2;
	if (x2 == gsize || y2 == gsize) {
		if (x2 == gsize) {
			row1 = x2 - 1;
			row2 = 2;
		}
		else if (y2 == gsize) {
			column1 = y2 - 1;
			column2 = 2;
		}
	}
	else if (x2 == 0 || y2 == 0) {
		if (x2 == 0 && y2 > 0) {
			row1 = 0;
			row2 = 2;

		}
		else if (y2 == 0 && x2 > 0) {
			column1 = 0;
			column2 = 2;
		}
		else if (x2 == 0 && y2 == 0) {
			row1 = 0;
			row2 = 2;
			column1 = 0;
			column2 = 2;
		}
	}
	int totalx = x2 - row1;
	int totalx1 = x2 + row2;
	int totaly = y2 - column1;
	int totaly1 = y2 + column2;
	for (int ro = totalx; ro < totalx1; ro++) {
		if (ro == gsize)break;
		for (int co = totaly; co < totaly1; co++) {
			if (co == gsize)
				break;
			if (gridmine[ro][co] == 1)
				countm++;
		}
	}




	minecheck(x2, y2, countm);
	countm = 0;
}

void MainGame::gridtextcheck(bool& checki, int& x, int& y) {

	/*Checking if the cell contain a blank*/
	if (grid[x][y].getTexture() == &defaultimg[1] || grid[x][y].getTexture() == &defaultimg[2]) {
		checki = true;
		return;
	}
}

void MainGame::minecheck(int x3, int y3, int count) {
	bool checkm = false;
	NumberCheck(checkm, x3, y3);

	if (!checkm && grid[x3][y3].getTexture() != &defaultimg[2] && grid[x3][y3].getTexture() != &defaultimg[3] && grid[x3][y3].getTexture() != &flagimg) {
		if (count == 0) {
			grid[x3][y3].setTexture(defaultimg[1]);
			return;
		}
		grid[x3][y3].setTexture(Numbers[count]);
		return;
	}
}

void MainGame::flagcheck(int x4, int y4) {
	bool checkm = false, checki = false;
	/*Checking if flag already exists and removing the flag*/
	if (grid[x4][y4].getTexture() == &flagimg) {
		grid[x4][y4].setTexture(defaultimg[0]);
		if (gridmine[x4][y4] == 1) {
			totalscore--;
			fakeminecount++;
		}
		else {
			fakeminecount++;
		}

		return;
	}
	gridtextcheck(checki, x4, y4);
	NumberCheck(checkm, x4, y4);
	if (!checki && !checkm) {
		grid[x4][y4].setTexture(flagimg);
		if (gridmine[x4][y4] == 1) {
			totalscore++;
			fakeminecount--;
		}
		else {
			fakeminecount--;
		}
	}
	if (totalscore == fixminecount) {
		gamewin = true;
		return;
	}

	return;
}

void MainGame::NumberCheck(bool& checkm, int x, int y) {
	for (int i = 0; i < gsize; i++) {
		if (grid[x][y].getTexture() == &Numbers[i] && gridmine[x][y] != 1) {
			checkm = true;
			return;
		}
	}


}

bool MainGame::winopencheck() {
	return windowp->isOpen();
}


/*Destructor*/
MainGame::~MainGame() {
	for (int i = 0; i < gsize; i++) {
		delete[] grid[i];
		delete[] gridmine[i];
	}
	delete[] grid;
	delete[] gridmine;
	delete windowp;
	delete op;
	delete di;
}


/*!**MAIN HANDLING FUNCTION***/
void MainGame::mainWindow() {
	windowp->clear();
	windowp->draw(background);
	elapsed = clock.getElapsedTime();
	renderingmain();
	gridmake();
	if (gamereset) { windowp->close(); }
	else if (gamewin) {
		Smiley.setTexture(Smileyimg[3]);
	}
	windowp->display();
}







