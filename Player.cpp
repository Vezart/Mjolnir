#include "Player.h"
#include "math.h"

using namespace std;

Player::Player(int xStart, int yStart, int tileSize, Board* board) {
	sourceTileX = xStart;
	sourceTileY = yStart;
	xTile = xStart;
	yTile = yStart;
	this->tileSize = tileSize;
	this->board = board;
	isMoving = false;
	blastActive = false;
	direction = Sentinel::Right;
}

//Loads all four player sprites
void Player::loadPlayerTexture() {
	string filename = "Player/playerUp.jpg";
	init_texture((char*)filename.c_str(), textureUp, xDim, yDim);
	filename = "Player/playerDown.jpg";
	init_texture((char*)filename.c_str(), textureDown, xDim, yDim);
	filename = "Player/playerLeft.jpg";
	init_texture((char*)filename.c_str(), textureLeft, xDim, yDim);
	filename = "Player/playerRight.jpg";
	init_texture((char*)filename.c_str(), textureRight, xDim, yDim);
}

//Draws all sprites pertaining to player (soundblast and player sprite)
void Player::drawPlayer() {
	
	
	
	glColor3f(1.0, 1.0, 1.0);
	int xLeft = xTile * tileSize;
	int xRight = (xTile+1) * tileSize;
	int yTop = yTile * tileSize;
	int yBottom = (yTile+1) * tileSize;

	switch (direction) {
		case Sentinel::Up:		drawUp(xLeft, xRight, yTop, yBottom);
								break;
		case Sentinel::Down:	drawDown(xLeft, xRight, yTop, yBottom);
								break;
		case Sentinel::Left:	drawLeft(xLeft, xRight, yTop, yBottom);
								break;
		case Sentinel::Right:	drawRight(xLeft, xRight, yTop, yBottom);
								break;
	}

	if (blastActive)
		blast->drawBlast();
}

//Draws up-facing player sprite
void Player::drawUp(int xLeft, int xRight, int yTop, int yBottom) {
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xDim, yDim, 0, GL_RGB, GL_UNSIGNED_BYTE, textureUp);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(xLeft, yTop);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(xRight, yTop);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(xRight, yBottom);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(xLeft, yBottom);
	glEnd();
}

//Draws down-facing player sprite
void Player::drawDown(int xLeft, int xRight, int yTop, int yBottom) {
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xDim, yDim, 0, GL_RGB, GL_UNSIGNED_BYTE, textureDown);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(xLeft, yTop);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(xRight, yTop);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(xRight, yBottom);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(xLeft, yBottom);
	glEnd();
}

//Draws left-facing player sprite
void Player::drawLeft(int xLeft, int xRight, int yTop, int yBottom) {
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xDim, yDim, 0, GL_RGB, GL_UNSIGNED_BYTE, textureLeft);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(xLeft, yTop);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(xRight, yTop);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(xRight, yBottom);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(xLeft, yBottom);
	glEnd();
}

//Draws right-facing player sprite
void Player::drawRight(int xLeft, int xRight, int yTop, int yBottom) {
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xDim, yDim, 0, GL_RGB, GL_UNSIGNED_BYTE, textureRight);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(xLeft, yTop);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(xRight, yTop);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(xRight, yBottom);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(xLeft, yBottom);
	glEnd();
}


bool Player::update(int deltaTime) {
	if (blastActive) {
		blast->update(deltaTime);
	}

	//check 2 above, 2 below, 2 left, and 2 right for sentinels
	if (yTile > 0 && board->tiles[xTile][yTile-1].sentinelHere()) { //1 tile up
		if (board->tiles[xTile][yTile-1].getSentinel()->direction == Sentinel::Down) {
			xTile = sourceTileX;
			yTile = sourceTileY;
		}
	}
	else if (yTile > 1 && board->tiles[xTile][yTile-2].sentinelHere()) { //2 tiles up
		if (board->tiles[xTile][yTile-2].getSentinel()->direction == Sentinel::Down) {
			xTile = sourceTileX;
			yTile = sourceTileY;
		}
	}
	else if (yTile < board->ySize-1 && board->tiles[xTile][yTile+1].sentinelHere()) { //1 tile down
		if (board->tiles[xTile][yTile+1].getSentinel()->direction == Sentinel::Up) {
			xTile = sourceTileX;
			yTile = sourceTileY;
		}
	}
	else if (yTile < board->ySize-2 && board->tiles[xTile][yTile+2].sentinelHere()) { //2 tiles down
		if (board->tiles[xTile][yTile+2].getSentinel()->direction == Sentinel::Up) {
			xTile = sourceTileX;
			yTile = sourceTileY;
		}
	}
	else if (xTile > 0 && board->tiles[xTile-1][yTile].sentinelHere()) { //1 tile left
		if (board->tiles[xTile-1][yTile].getSentinel()->direction == Sentinel::Right) {
			xTile = sourceTileX;
			yTile = sourceTileY;
		}
	}
	else if (xTile > 1 && board->tiles[xTile-2][yTile].sentinelHere()) { //2 tiles left
		if (board->tiles[xTile-2][yTile].getSentinel()->direction == Sentinel::Right) {
			xTile = sourceTileX;
			yTile = sourceTileY;
		}
	}
	else if (xTile < board->xSize-1 && board->tiles[xTile+1][yTile].sentinelHere()) { //1 tile Right
		if (board->tiles[xTile+1][yTile].getSentinel()->direction == Sentinel::Left) {
			xTile = sourceTileX;
			yTile = sourceTileY;
		}
	}
	else if (xTile < board->xSize-2 && board->tiles[xTile+2][yTile].sentinelHere()) { //2 tiles Right
		if (board->tiles[xTile+2][yTile].getSentinel()->direction == Sentinel::Left) {
			xTile = sourceTileX;
			yTile = sourceTileY;
		}
	}

	if (board->tiles[xTile][yTile].tileChar == 'D') {
		cout << "Destination reached." << endl;
		return true;
	}
	return false;
}

void Player::shootBlast(int deltaX, int deltaY) {
	float length = sqrt((deltaX - (xTile * tileSize + tileSize / 2)) * (deltaX - (xTile * tileSize + tileSize / 2)) + (deltaY - (yTile * tileSize + tileSize / 2)) * (deltaY - (yTile * tileSize + tileSize / 2)));

	if (blastActive) {
		blast->setCoordinates(xTile * tileSize + tileSize / 2, yTile * tileSize + tileSize / 2);
		blast->setMoveVector(((float)(deltaX - (xTile * tileSize + tileSize / 2.0)) / length) * 5.0, ((float)(deltaY - (yTile * tileSize + tileSize / 2.0)) / length) * 5.0);
		blast->currentTile = &(board->tiles[xTile][yTile]);
	}
	else {
		blast = new Soundblast(deltaX - (xTile * tileSize + tileSize / 2), deltaY - (yTile * tileSize + tileSize / 2));
		blast->setCoordinates(xTile * tileSize + tileSize / 2, yTile * tileSize + tileSize / 2);
		blast->setMoveVector(((float)(deltaX - (xTile * tileSize + tileSize / 2.0)) / length) * 5.0, ((float)(deltaY - (yTile * tileSize + tileSize / 2.0)) / length) * 5.0);
		blast->currentTile = &(board->tiles[xTile][yTile]);
		blast->board = board;
		blastActive = true;
	}

	blast->hasBounced = false;
	blast->draw = true;
}

void Player::moveUp() {
	direction = Sentinel::Up;

	if (isMoving || yTile <= 0)							//Don't move if leaving board
		return;

	if (board->getTile(xTile, yTile-1).isSolid()) {		//Don't move into wall
		return;
	}

	isMoving = true;
	yTile -= 1;
	isMoving = false;
}

void Player::moveDown() {
	direction = Sentinel::Down;

	if (isMoving || yTile >= board->ySize - 1)			//Don't move if leaving board
		return;

	if (board->getTile(xTile, yTile+1).isSolid()) {		//Don't move into wall
		return;
	}

	isMoving = true;
	yTile += 1;
	isMoving = false;
}

void Player::moveLeft() {
	direction = Sentinel::Left;

	if (isMoving || xTile <= 0)							//Don't move if leaving board
		return;

	if (board->getTile(xTile-1, yTile).isSolid()) {		//Don't move into wall
		return;
	}

	isMoving = true;
	xTile -= 1;
	isMoving = false;
}

void Player::moveRight() {
	direction = Sentinel::Right;

	if (isMoving || xTile >= board->xSize - 1)			//Don't move if leaving board
		return;

	if (board->getTile(xTile+1, yTile).isSolid()) {		//Don't move into wall
		return;
	}

	isMoving = true;
	xTile += 1;
	isMoving = false;
}

void Player::init_texture(char *name, unsigned char *&texture, int &xdim, int &ydim)
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
