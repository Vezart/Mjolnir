#include "Tile.h"

Tile::Tile() {

}

Tile::Tile(int size) {
    tileSize = size;
}

void Tile::drawTile() {
	int xTopLeft = xTile * tileSize;
	int yTopLeft = yTile * tileSize;
	int xBottomRight = xTile * tileSize + tileSize;
	int yBottomRight = yTile * tileSize + tileSize;

	//Here
}

void Tile::loadTexture(char tiletype) {
	string filename = "Tiles/";
	filename.append(&tiletype, 1);
	tileChar = tiletype;
	switch (tiletype) {
		case 'F':	solid = false;
					break;
		case 'W':	solid = true;
					break;
		case 'S':	solid = false;
					break;
		case 'D':	solid = false;
					break;	
	}
}

void Tile::placeSentry(Sentinel* sentinel) {
	this->sentinel = *sentinel;
}

bool Tile::isSolid() {
	return solid;
}

bool Tile::contains(int xCoord, int yCoord) {
	return (xCoord > xTile * tileSize && xCoord < xTile * tileSize + tileSize && yCoord > yTile * tileSize && yCoord < yTile * tileSize + tileSize);
}
