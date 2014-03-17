#pragma once

#include <math.h>

#include <GL/glut.h>

#include "Tile.h"

class Board {
    public:
        Board();
		Board(int xSize, int ySize, int tileSize);
		void loadBoard(string filename);
		void drawBoard();
		void update();
		Tile getTile(int x, int y);
		//void setPlayer(Player player);
		int xSize;
		int ySize;
		int tileSize;
		void drawCircle(int x, int y, float radius); //Temporary
    private:
		Tile **tiles;
		char **tileChars;
		
		//Player player;
};
