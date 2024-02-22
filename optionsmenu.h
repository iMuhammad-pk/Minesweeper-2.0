
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;


class optionsmenu {
	RenderWindow* optionp;
	Font ostyle;
	Texture otexture[4], dbackimg;
	Sprite odark, omine, ydark, ndark, background;
	Event click;
public:
	bool darkmode, mine1;
	int minecount;
	/*Constructors*/
	optionsmenu();
	optionsmenu(bool, int);
	/*Functions*/
	void optionsimgsload();
	bool owindow();
	void omain();
	void orender();
	void oevent();
	int mine();
	/*Destructor*/
	~optionsmenu();












};