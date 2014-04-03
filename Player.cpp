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
}

void Player::loadPlayerTexture(string filename) {

}

void Player::drawPlayer() {
	//Draw on rectangle from (xTile * tileSize, yTile * tileSize) to (xTile * tileSize + tileSize, yTile * tileSize + tileSize)
	glColor3f(0.0, 1.0, 1.0);
	board->drawCircle(xTile * tileSize + tileSize / 2, yTile * tileSize + tileSize / 2, tileSize / 3);
	if (blastActive)
		blast->drawBlast();
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

	if (board->tiles[xTile][yTile].tileChar = 'D') {
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
	if (isMoving || yTile <= 0)
		return;

	if (board->getTile(xTile, yTile-1).isSolid()) {
		return;
	}

	isMoving = true;

	yTile -= 1;

	isMoving = false;

	if (board->getTile(xTile, yTile).tileChar == 'D') {
		//done!
	}
}

void Player::moveDown() {
	if (isMoving || yTile >= board->ySize - 1)
		return;

	if (board->getTile(xTile, yTile+1).isSolid()) {
		return;
	}

	isMoving = true;

	yTile += 1;

	isMoving = false;

	if (board->getTile(xTile, yTile).tileChar == 'D') {
		//done!
	}
}

void Player::moveLeft() {
	if (isMoving || xTile <= 0)
		return;

	if (board->getTile(xTile-1, yTile).isSolid()) {
		return;
	}

	isMoving = true;

	xTile -= 1;

	isMoving = false;

	if (board->getTile(xTile, yTile).tileChar == 'D') {
		//done!
	}
}

void Player::moveRight() {
	if (isMoving || xTile >= board->xSize - 1)
		return;

	if (board->getTile(xTile+1, yTile).isSolid()) {
		return;
	}

	isMoving = true;

	xTile += 1;

	isMoving = false;

	if (board->getTile(xTile, yTile).tileChar == 'D') {
		//done!
	}
}
