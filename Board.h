#pragma once

#include <math.h>
#include <GL/glut.h>

#include "Tile.h"

class Board {
    public:
        Board();
		Board(int xSize, int ySize, int tileSize);
		void loadBoard(int level);
		void drawBoard();
		Tile getTile(int x, int y);
		int xSize;
		int ySize;
		int tileSize;
		Tile **tiles;
    private:
		char **tileChars;
};
