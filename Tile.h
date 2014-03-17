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
		void drawTile();
		void loadTexture(string filename, bool solid);
		bool isSolid();
		bool contains(int xCoord, int yCoord);
		int tileSize;
		int xTile;
		int yTile;
    private:
		//Image texture;
		bool solid;
};

/// Dylan, you'll have to implement getting textures in, so do the loadTexture function and drawTile function
