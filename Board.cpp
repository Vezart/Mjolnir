#include <math.h>
#include "Board.h"

using namespace std;

Board::Board() {
    xSize = 16;
    ySize = 16;
	tileSize = 32;
    tiles = new Tile*[xSize];
    for (int i = 0; i < xSize; i++) {
		tiles[i] = new Tile[ySize];
		for (int j = 0; j < ySize; j++) {
	    	tiles[i][j].tileSize = tileSize;
		}
    }
}

Board::Board(int xSize, int ySize, int tileSize) {
	this->xSize = xSize;
	this->ySize = ySize;
	this->tileSize = tileSize;
    tiles = new Tile*[xSize];
    for (int i = 0; i < xSize; i++) {
		tiles[i] = new Tile[ySize];
		for (int j = 0; j < ySize; j++) {
			tiles[i][j].tileSize = tileSize;
			//tiles[i][j].loadTexture("a");
		}
    }
}

void Board::loadBoard(string filename) {
	tileChars = new char*[xSize];
	for (int i = 0; i < xSize; i++) {
		tileChars[i] = new char[ySize];
		for (int j = 0; j < ySize; j++) {
			tileChars[i][j] = 'a'; //load from file
		}
	}


	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize; j++) {
			string filename = "Directory/";
			filename.append(&tileChars[i][j], 1);
			tiles[i][j].loadTexture(filename);
		}
	}
}

void Board::drawBoard() {
    for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize; j++) {
			tiles[i][j].drawTile(i * tileSize, j * tileSize);
			drawCircle(i * tileSize + tileSize / 2, j * tileSize + tileSize / 2, tileSize / 2);
		}
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
