#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

class Tile {
    public:
		Tile();
		Tile(int size);
		void drawTile(int xCoord, int yCoord);
		void loadTexture(string filename, bool solid);
		bool isSolid();
		int tileSize;
    private:
		//Image texture;
		bool solid;
};

/// Dylan, you'll have to implement getting textures in, so do the loadTexture function and drawTile function
