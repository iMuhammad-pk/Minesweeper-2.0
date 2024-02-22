#include "MainGame.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>





LevelExpert::LevelExpert():MainGame() {
	windowp = new RenderWindow(VideoMode(700, 720), "Minesweeper v2", Style::Titlebar | Style::Close);
	totalscore = time1 = minecount = 0;
	gamereset = gamewin = gameover = false;
	gsize = 16;
	fakeminecount = 0;
	grid = new Sprite *[gsize];
	gridmine = new int* [gsize];

	for (int row = 0; row < gsize; row++) {
		gridmine[row] = new int[gsize] {0};
		grid[row] = new Sprite[gsize];
	}

	sizex = 85; sizey = 50; sx = 300; sy = 41; bx = 150; by = 50; bx1 = 400; fx = 400; fy = 60; fx1 = 150;
	smousex = 355; smousex1 = 300; smousey = 100; smousey1 = 50;
	darkbool = false;
	fixminecount = 50;
	windowp->setFramerateLimit(30);

	loadimgandfont();
}

LevelExpert::LevelExpert(bool dark, int mine, int gsize1) {
	delete windowp;
	windowp = new RenderWindow(VideoMode(700, 720), "Minesweeper v2", Style::Titlebar | Style::Close);
	sizex = 85; sizey = 50; sx = 300; sy = 41; bx = 150; by = 50; bx1 = 400; fx = 400; fy = 60; fx1 = 150;
	smousex = 355; smousex1 = 300; smousey = 100; smousey1 = 50;
	totalscore = time1 = minecount = 0;
	fakeminecount = 0;
	fixminecount = mine;
	darkbool = dark;
	gsize = gsize1;
	grid = new Sprite * [gsize];
	gridmine = new int* [gsize];

	for (int row = 0; row < gsize; row++) {
		gridmine[row] = new int[gsize] {0};
		grid[row] = new Sprite[gsize];
	}
	gamereset = gamewin = gameover = false;
	windowp->setFramerateLimit(30);
	loadimgandfont();
}
LevelExpert::~LevelExpert() {
	for (int j = 0; j < gsize; j++) {		
			delete[] grid[j];
			delete[] gridmine[j];
	}
	delete[] grid;
	delete[] gridmine;
	delete windowp;
}