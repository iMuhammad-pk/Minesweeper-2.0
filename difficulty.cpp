#include "difficulty.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
using namespace std;
using namespace sf;

/*Constructor*/

difficulty::difficulty() {
	diffwin = new RenderWindow(VideoMode(500, 200), "Difficulty", Style::Titlebar | Style::Close);
	
	
	loadimg();
}

/*Functions*/
void difficulty::loadimg() {
	level.loadFromFile("images/button.png");
	dstyle.loadFromFile("fonts/arial.ttf");
	
}
bool difficulty::iswin() {
	return diffwin->isOpen();
}
void difficulty::render() {
	string text = "Beginner";
	diff[0].setTexture(level);
	diff[0].setPosition(100, 50);
	diff[1].setTexture(level);
	diff[1].setPosition(300, 50);
	Text ftext(text, dstyle, 30);
	ftext.setFillColor(Color::Black);
	text = "Expert";
	Text f1text(text, dstyle, 30);
	f1text.setFillColor(Color::Black);
	ftext.setPosition(115, 55);
	f1text.setPosition(330, 55);
	diffwin->draw(diff[0]);
	diffwin->draw(diff[1]);
	diffwin->draw(ftext);
	diffwin->draw(f1text);
}
void difficulty::event() {
	while (diffwin->pollEvent(press)) {
		if (press.type == Event::Closed) {
			diffwin->close();
			return;
		}
		if (press.key.code == Keyboard::Escape) {
			diffwin->close();
			return;
		}
		if (press.type == Event::MouseButtonPressed) {
			if (press.mouseButton.button == Mouse::Left) {
				int x = press.mouseButton.x;
				int y = press.mouseButton.x;
				if (x <= 250 && x >= 100 && y <= 255 && y >= 105) {
					beg = true;
					return;
				}
				else if (x <= 460 && x >= 300 && y <= 460 && y >= 300) {
					exp = true;
					return;
				}
			}
		}

	}
}
/*Destructor*/
difficulty::~difficulty() {
	delete diffwin;
}

/*MAIN WINDOW*/
void difficulty::mainrender() {
	diffwin->clear(Color::White);
	render();

	diffwin->display();
}

