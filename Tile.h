#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>

#include <GL/glut.h>


#include "Sentinel.h"

using namespace std;

class Tile {
    public:
		Tile();
		Tile(int size);
		void drawTile();
		void drawSentinel();
		void loadTexture(char tiletype);
		void placeSentry(Sentinel* sentinel);
		bool isSolid();
		bool sentinelHere();
		bool contains(int xCoord, int yCoord);
		int tileSize;
		int xTile;
		int yTile;
		char tileChar;
		Sentinel* getSentinel();
    private:
		bool solid;
		bool hasSentinel;
		Sentinel sentinel;
		unsigned char* texture;
		int xDim;
		int yDim;
		void drawUp();
		void drawDown();
		void drawLeft();
		void drawRight();
		void init_texture(char *name, unsigned char *&texture, int &xdim, int &ydim);
};
