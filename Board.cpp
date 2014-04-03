#include <stdio.h>
#include <stdlib.h>

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

//Load board from text file
void Board::loadBoard(int level) {
	string filename = "board";
	char levelNumber[1];
	sprintf(levelNumber, "%d", level);
	filename.append(levelNumber, 1);
	filename.append(".txt", 4);

	ifstream inFile;
	inFile.open(filename.c_str());

	//Initialize board arrays
	tileChars = new char*[xSize];
	for (int i = 0; i < xSize; i++) {
		tileChars[i] = new char[ySize];
	}
	
	//Load level specs
	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize; j++) {
			inFile >> tileChars[j][i];
		}
	}

	//Initialize tiles based on level specs
	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize; j++) {
			string filename = "Tiles/";
			filename.append(&tileChars[i][j], 1);
			tiles[i][j].loadTexture(tileChars[i][j]);
		}
	}

	int numberSentinels;

	inFile >> numberSentinels;

	Sentinel *s;
	int sX, sY;
	char direction;

	//Initialize sentinels
	for (int i = 0; i < numberSentinels; i++) {
		s = new Sentinel();
		inFile >> sX;
		inFile >> sY;
		inFile >> direction;
		switch (direction) {
			case 'U':	s->direction = Sentinel::Up;
						break;
			case 'D':	s->direction = Sentinel::Down;
						break;
			case 'L':	s->direction = Sentinel::Left;
						break;
			case 'R':	s->direction = Sentinel::Right;
						break;
		}
		tiles[sX][sY].placeSentry(s);
	}
}

//Draws tiles and sentinels
void Board::drawBoard() {
	glColor3f(1.0, 1.0, 1.0);

    for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize; j++) {
			tiles[i][j].drawTile();
			
		}
    }

	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize; j++) {
			if (tiles[i][j].sentinelHere())
				tiles[i][j].drawSentinel();
		}
    }
}

Tile Board::getTile(int x, int y) {
	return tiles[x][y];
}
