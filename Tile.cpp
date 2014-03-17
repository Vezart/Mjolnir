#include "Tile.h"

Tile::Tile() {

}

Tile::Tile(int size) {
    tileSize = size;
}

void Tile::drawTile(int xCoord, int yCoord) {

}

void Tile::loadTexture(string filename, bool solid) {
	this->solid = solid;
	//cout << filename << endl;
}

bool Tile::isSolid() {
	return solid;
}
