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

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xDim, yDim, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(xTopLeft, yTopLeft);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(xBottomRight, yTopLeft);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(xBottomRight, yBottomRight);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(xTopLeft, yBottomRight);
	glEnd();

	if (hasSentinel) {
		sentinel.drawSentinel(xTopLeft, xBottomRight, yTopLeft, yBottomRight);
	}

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
	filename.append(".jpg", 4);
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

	init_texture((char*)filename.c_str(), texture, xDim, yDim);
	
}

void Tile::placeSentry(Sentinel* sentinel) {
	this->sentinel = *sentinel;
	this->sentinel.loadTexture();
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

void Tile::init_texture(char *name, unsigned char *&texture, int &xdim, int &ydim)
{
   // Read jpg image
   im_color image;
   image.ReadJpg(name);
   printf("Reading image %s\n", name);
   xdim = 1; while (xdim < image.R.Xdim) xdim*=2; xdim /=2;
   ydim = 1; while (ydim < image.R.Ydim) ydim*=2; ydim /=2;
   image.Interpolate(xdim, ydim);
   printf("Interpolating to %d by %d\n", xdim, ydim);

   // Copy image into texture array
   texture = (unsigned char *)malloc((unsigned int)(xdim*ydim*3));
   int index = 0;
   for (int y = 0; y < ydim; y++)
      for (int x = 0; x < xdim; x++)
      {
         texture[index++] = (unsigned char)(image.R.Data2D[y][x]);
         texture[index++] = (unsigned char)(image.G.Data2D[y][x]);
         texture[index++] = (unsigned char)(image.B.Data2D[y][x]);
      }
}
