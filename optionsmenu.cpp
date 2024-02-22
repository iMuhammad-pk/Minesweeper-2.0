#include "optionsmenu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;





/********Constructors*******************/
optionsmenu::optionsmenu() {
	optionp = new RenderWindow(VideoMode(300, 100), "Options", Style::Titlebar | Style::Close);
	darkmode = false;
	minecount = 10;
	optionsimgsload();
}
optionsmenu::optionsmenu(bool dark, int minecount1) {
	optionp = new RenderWindow(VideoMode(300, 100), "Options", Style::Titlebar | Style::Close);
	darkmode = dark;
	minecount = minecount1;
	optionsimgsload();
}

/*Functions*****/
void optionsmenu::optionsimgsload() {
	ostyle.loadFromFile("fonts/arial.ttf");
	otexture[0].loadFromFile("images/yes.png"); otexture[1].loadFromFile("images/no.png");
	otexture[2].loadFromFile("images/darkmode.png");
	otexture[3].loadFromFile("images/minelogo.png");
	dbackimg.loadFromFile("images/dbackimg.png");
}
int optionsmenu::mine() {
	cout << "Enter amount of mines to add: "; cin >> minecount;
	return minecount;
}

void optionsmenu::orender() {
	omine.setTexture(otexture[3]); omine.setPosition(200, 25);
	odark.setTexture(otexture[2]); odark.setPosition(10, 25);
	ydark.setTexture(otexture[0]); ydark.setPosition(65, 25);
	ndark.setTexture(otexture[1]); ndark.setPosition(120, 25);
	RectangleShape border;
	border.setSize(Vector2f(105, 50));
	border.setPosition(5, 70);
	border.setFillColor(Color(204, 204, 204));
	optionp->draw(odark);
	optionp->draw(ydark);
	optionp->draw(ndark);
	optionp->draw(omine);

}
bool optionsmenu::owindow() {
	return optionp->isOpen();
}
void optionsmenu::oevent() {
	while (optionp->pollEvent(click)) {
		if (click.type == Event::Closed) {
			optionp->close();
			return;
		}
		if (click.key.code == Keyboard::Escape) {
			optionp->close();
			return;
		}
		if (click.type == Event::MouseButtonPressed) {
			if (click.mouseButton.button == Mouse::Left) {
				int x = click.mouseButton.x;
				int y = click.mouseButton.y;
				if (x <= 85 && y <= 50 && x >= 50 && y >= 30) {
					darkmode = true;
					return;
				}
				else if (x <= 150 && x >= 120 && y >= 30 && y <= 60) {
					darkmode = false;
					return;
				}
				else if (x <= 225 && x >= 175 && y >= 30 && y <= 60) {
					mine1 = true;
					return;
				}

			}
		}
	}
}


optionsmenu::~optionsmenu() {
	delete optionp;
}


/**********Main Options window config************/
void optionsmenu::omain() {
	optionp->clear(Color::White);
	orender();
	optionp->display();

}
