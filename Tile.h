#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>

#include "Sentinel.h"

using namespace std;

class Tile {
    public:
		Tile();
		Tile(int size);
		void drawTile();
		void loadTexture(char tiletype);
		void placeSentry(Sentinel* sentinel);
		bool isSolid();
		bool contains(int xCoord, int yCoord);
		int tileSize;
		int xTile;
		int yTile;
		char tileChar;
		
    private:
		//Image texture;
		bool solid;
		Sentinel sentinel;
};

/// Dylan, you'll have to implement getting textures in, so do the loadTexture function and drawTile function
