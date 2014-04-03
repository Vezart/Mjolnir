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
			tiles[i][j].xTile = i;
			tiles[i][j].yTile = j;
		}
    }
}

void Board::loadBoard(string filename) {
	ifstream inFile;
	inFile.open(filename.c_str());

	tileChars = new char*[xSize];
	for (int i = 0; i < xSize; i++) {
		tileChars[i] = new char[ySize];
	}
	
	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize; j++) {
			inFile >> tileChars[j][i];
		}
	}


	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize; j++) {
			string filename = "Tiles/";
			filename.append(&tileChars[i][j], 1);
			bool solid = false; // set based on char spec
			tiles[i][j].loadTexture(tileChars[i][j]);
		}
	}

	Sentinel *s = new Sentinel();
	s->direction = Sentinel::Up;
	tiles[1][8].placeSentry(s);
}

void Board::drawBoard() {
	glColor3f(1.0, 0.0, 0.0);

    for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize; j++) {
			tiles[i][j].drawTile();
			if (tiles[i][j].tileChar == 'W')
				glColor3f(0.0, 0.0, 1.0);
			else
				glColor3f(1.0, 0.0, 0.0);
			
			drawCircle(i * tileSize + tileSize / 2, j * tileSize + tileSize / 2, tileSize / 2);
		}
    }

	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize; j++) {
			if (tiles[i][j].sentinelHere())
				tiles[i][j].drawSentinel();
		}
    }
}

void Board::update() {

}

Tile Board::getTile(int x, int y) {
	return tiles[x][y];
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
