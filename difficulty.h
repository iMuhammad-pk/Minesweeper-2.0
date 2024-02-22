#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
using namespace std;
using namespace sf;



class difficulty {
	
	Texture level;
	Sprite diff[2];
	Font dstyle;
	Event press;

public:
	RenderWindow* diffwin;
	bool exp, beg;
	difficulty();
	void loadimg();
	void render();
	void event();
	bool iswin();
	void mainrender();
	~difficulty();

	
};