#include <math.h>
#include "Board.h"

using namespace std;

Board::Board() {
    xSize = 16;
    ySize = 16;
    tiles = new Tile*[xSize];
    for (int i = 0; i < xSize; i++) {
		tiles[i] = new Tile[ySize];
		for (int j = 0; j < ySize; j++) {
	    	tiles[i][j].setTileSize(32);
		}
    }
}

Board::Board(int xSize, int ySize, int tileSize) {
	this->xSize = xSize;
	this->ySize = ySize;
    tiles = new Tile*[xSize];
    for (int i = 0; i < xSize; i++) {
		tiles[i] = new Tile[ySize];
		for (int j = 0; j < ySize; j++) {
			tiles[i][j].setTileSize(tileSize);
		}
    }
}

void Board::drawBoard() {
    for (int i = 0; i < xSize; i++) {
		
    }
}

//void Board::setPlayer(Player player) {
//    this.player = player;
//}

void Board::drawCircle(int x, int y, float radius) {
    glBegin(GL_POLYGON);

    for (int angle = 0; angle < 360; angle += 10) {
		float radians = M_PI * angle/180.0;
		float X = x + radius * cos(radians);
		    float Y = y + radius * sin(radians);
		glVertex2f(X, Y);
    }

    glEnd();
}
