#pragma once

#include <GL/glut.h>
#include <string>
#include <iostream>

#include "Board.h"
#include "Soundblast.h"

class Player {
    public:
		Player(int xStart, int yStart, int tileSize, Board *board);
		void loadPlayerTexture();
		void drawPlayer();
		bool update(int deltaTime);
		void shootBlast(int x, int y);
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
    private:
		int sourceTileX;
		int sourceTileY;
		int xTile;
		int yTile;
		int tileSize;
		bool isMoving;
		Board* board;
		Soundblast* blast;
		bool blastActive;
		unsigned char* textureUp;
		unsigned char* textureDown;
		unsigned char* textureLeft;
		unsigned char* textureRight;
		int xDim;
		int yDim;
		void init_texture(char *name, unsigned char *&texture, int &xdim, int &ydim);
		void drawUp(int xLeft, int xRight, int yTop, int yBottom);
		void drawDown(int xLeft, int xRight, int yTop, int yBottom);
		void drawLeft(int xLeft, int xRight, int yTop, int yBottom);
		void drawRight(int xLeft, int xRight, int yTop, int yBottom);
		Sentinel::Direction direction;
};
