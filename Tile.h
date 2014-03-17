#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

class Tile {
    public:
	Tile();
	Tile(int size);
	void drawTile(int xCoord, int yCoord);
	void loadTexture(string filename);

	int tileSize;
    private:
	//Image texture;

};

/// Dylan, you'll have to implement getting textures in, so do the loadTexture function and drawTile function
