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
}

void Tile::loadTexture(string filename, bool solid) {
	this->solid = solid;
	//cout << filename << endl;
}

bool Tile::isSolid() {
	return solid;
}

bool Tile::contains(int xCoord, int yCoord) {
	return (xCoord > xTile * tileSize && xCoord < xTile * tileSize + tileSize && yCoord > yTile * tileSize && yCoord < yTile * tileSize + tileSize);
}
