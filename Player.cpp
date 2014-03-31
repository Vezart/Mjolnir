#include "Player.h"

using namespace std;

Player::Player(int xStart, int yStart, int tileSize, Board* board) {
	xTile = xStart;
	yTile = yStart;
	this->tileSize = tileSize;
	this->board = board;
	isMoving = false;
}

void Player::loadPlayerTexture(string filename) {

}

void Player::drawPlayer() {
	//Draw on rectangle from (xTile * tileSize, yTile * tileSize) to (xTile * tileSize + tileSize, yTile * tileSize + tileSize)
	glColor3f(0.0, 1.0, 1.0);
	board->drawCircle(xTile * tileSize + tileSize / 2, yTile * tileSize + tileSize / 2, tileSize / 3);
}

void Player::update() {

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
