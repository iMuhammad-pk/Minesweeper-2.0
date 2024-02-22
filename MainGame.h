#include "optionsmenu.h"
#include "difficulty.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;



class MainGame {
protected:
	Texture defaultimg[5], Smileyimg[5], Numbers[10], flagimg, backimg, optionimg[3];
	Image iconimg;
	Event press;
	Font fontstyle;
	Sprite** grid, Smiley, background;
	Clock clock; Time elapsed;
public:
	optionsmenu* op;
	RenderWindow* windowp;
	difficulty* di;
	int minecount, totalscore,time1, ** gridmine, gsize, fixminecount, fakeminecount,framerate;
	float sizex, sizey, sx, sy, bx, by, bx1, fx, fy, fx1;
	int smousex, smousex1, smousey, smousey1;
	bool gameover, gamereset, gamewin, darkbool, expert,handle, beginner;

	/*Constructors*/
	MainGame();
	MainGame(bool, int, int);
	/*Window Handling Functions*/

	bool winopencheck(); /*Checking if window is open or closed*/
	void loadimgandfont();
	void mainWindow(); /*Setting up main window render*/
	void renderingmain();/*Looping certain render functions to display*/
	void eventmanager();/*Checking if any key/mouse clicked/pressed*/
	void BoundCheck(int&, int&, int, int);
	/*Game Running Functions*/
	void gridmake();/*Setting up grid every frame*/
	void gridinput(int, int);/*Clicked Cell function*/
	void gridcheck(int, int);/*Checking to place which img in it*/
	void minecheck(int, int, int);/*Does cell contain mine?*/
	void flagcheck(int, int);/*If Rightclicked flag*/
	void gridtextcheck(bool&, int&, int&); /*Checking if any empty or flag img Grid*/
	void NumberCheck(bool&, int, int);/* Checking if the grid already has a number img*/
	void Revealmines(int, int);/*Revealing Mines when pressed*/
	void optionsg(int, int); /*Opening Options menu*/
	void expertlevel(int, int);/*Difficulty Menu*/




	/*Destructor*/
	~MainGame();

};

class LevelExpert :public MainGame {
public:
	LevelExpert();
	LevelExpert(bool, int, int);
	~LevelExpert();
};
