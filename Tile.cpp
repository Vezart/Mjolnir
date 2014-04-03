#include "Tile.h"

Tile::Tile() {
	hasSentinel = false;
}

Tile::Tile(int size) {
    tileSize = size;
	hasSentinel = false;
}


void Tile::drawTile() {
	int xTopLeft = xTile * tileSize;
	int yTopLeft = yTile * tileSize;
	int xBottomRight = xTile * tileSize + tileSize;
	int yBottomRight = yTile * tileSize + tileSize;

	//Here

	//if (hasSentinel) {
	//	sentinel->drawSentinel();
	//}

	if (!hasSentinel)
		return;


}

void Tile::drawSentinel() {
	switch(sentinel.direction) {
		case Sentinel::Up:		drawUp();
								break;
		case Sentinel::Down:	drawDown();
								break;
		case Sentinel::Left:	drawLeft();
								break;
		case Sentinel::Right:	drawRight();
								break;
	}
}

void Tile::drawUp() {
	glBegin(GL_POLYGON);

	glColor4f(0.0, 1.0, 0.0, 0.5);

    glVertex2f(xTile * tileSize, yTile * tileSize);
	glVertex2f(xTile * tileSize, (yTile - 2) * tileSize);
	glVertex2f((xTile + 1) * tileSize, (yTile - 2) * tileSize);
	glVertex2f((xTile + 1) * tileSize, yTile * tileSize);

    glEnd();
}

void Tile::drawDown() {
	glBegin(GL_POLYGON);

	glColor4f(0.0, 1.0, 0.0, 0.5);

    glVertex2f(xTile * tileSize, (yTile + 1) * tileSize);
	glVertex2f(xTile * tileSize, (yTile + 3) * tileSize);
	glVertex2f((xTile + 1) * tileSize, (yTile + 3) * tileSize);
	glVertex2f((xTile + 1) * tileSize, (yTile + 1) * tileSize);

    glEnd();
}

void Tile::drawLeft() {
	glBegin(GL_POLYGON);

	glColor4f(0.0, 1.0, 0.0, 0.5);

    glVertex2f(xTile * tileSize, (yTile + 1) * tileSize);
	glVertex2f((xTile - 2) * tileSize, (yTile + 1) * tileSize);
	glVertex2f((xTile - 2) * tileSize, yTile * tileSize);
	glVertex2f(xTile * tileSize, yTile * tileSize);

    glEnd();
}

void Tile::drawRight() {
	glBegin(GL_POLYGON);

	glColor4f(0.0, 1.0, 0.0, 0.5);

    glVertex2f((xTile + 1) * tileSize, (yTile + 1) * tileSize);
	glVertex2f((xTile + 3) * tileSize, (yTile + 1) * tileSize);
	glVertex2f((xTile + 3) * tileSize, yTile * tileSize);
	glVertex2f((xTile + 1) * tileSize, yTile * tileSize);

    glEnd();
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

	//Load image here!!!
}

void Tile::placeSentry(Sentinel* sentinel) {
	this->sentinel = *sentinel;
	hasSentinel = true;
}

bool Tile::isSolid() {
	return solid;
}

bool Tile::sentinelHere() {
	return hasSentinel;
}

bool Tile::contains(int xCoord, int yCoord) {
	return (xCoord > xTile * tileSize && xCoord < xTile * tileSize + tileSize && yCoord > yTile * tileSize && yCoord < yTile * tileSize + tileSize);
}

Sentinel* Tile::getSentinel() {
	return &sentinel;
}
