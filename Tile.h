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
		//Image texture;
		bool solid;
		bool hasSentinel;
		Sentinel sentinel;
		void drawUp();
		void drawDown();
		void drawLeft();
		void drawRight();
};

/// Dylan, you'll have to implement getting textures in, so do the loadTexture function and drawTile function
