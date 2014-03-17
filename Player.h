#pragma once

#include <GL/glut.h>
#include <string>
#include <iostream>

#include "Board.h"

class Player {
    public:
		Player(int xStart, int yStart, int tileSize, Board *board);
		void loadPlayerTexture(string filename);
		void drawPlayer();
		void update();
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
    private:
		int xTile;
		int yTile;
		int tileSize;
		bool isMoving;
		Board* board;
};
