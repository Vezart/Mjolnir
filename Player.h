#pragma once

#include <GL/glut.h>
#include <string>
#include <iostream>

#include "Board.h"
#include "Soundblast.h"

class Player {
    public:
		Player(int xStart, int yStart, int tileSize, Board *board);
		void loadPlayerTexture(string filename);
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
};
