#include "Soundblast.h"

Soundblast::Soundblast(int xDelta, int yDelta) {
	this->xDelta = xDelta;
	this->yDelta = yDelta;
	draw = true;
}

void Soundblast::update(int deltaTime) {
	if (!draw)
		return;

	x += xDelta;
	y += yDelta;

	int xTile = currentTile->xTile;
	int yTile = currentTile->yTile;

	if (xTile < board->xSize - 1 && board->tiles[xTile+1][yTile].contains(x, y)) {
		if (board->tiles[xTile+1][yTile].isSolid()) {
			if (hasBounced) {
				draw = false;
			}
			hasBounced = true;
			xDelta = -xDelta;
			x += xDelta;
		}
		else if (board->tiles[xTile+1][yTile].sentinelHere()) {
			draw = false;
			board->tiles[xTile+1][yTile].getSentinel()->direction = Sentinel::Left;
		}
		else {
			currentTile = &(board->tiles[xTile+1][yTile]);
		}
	}
	else if (xTile > 0 && board->tiles[xTile-1][yTile].contains(x, y)) {
		if (board->tiles[xTile-1][yTile].isSolid()) {
			if (hasBounced) {
				draw = false;
			}
			hasBounced = true;
			xDelta = -xDelta;
			x += xDelta;
		}
		else if (board->tiles[xTile-1][yTile].sentinelHere()) {
			draw = false;
			board->tiles[xTile-1][yTile].getSentinel()->direction = Sentinel::Right;//turn sentinel
		}
		else {
			currentTile = &(board->tiles[xTile-1][yTile]);
		}
	}
	else if (yTile < board->ySize - 1 && board->tiles[xTile][yTile+1].contains(x, y)) {
		if (board->tiles[xTile][yTile+1].isSolid()) {
			if (hasBounced) {
				draw = false;
			}
			hasBounced = true;
			yDelta = -yDelta;
			y += yDelta;
		}
		else if (board->tiles[xTile][yTile+1].sentinelHere()) {
			draw = false;
			board->tiles[xTile][yTile+1].getSentinel()->direction = Sentinel::Up;//turn sentinel
		}
		else {
			currentTile = &(board->tiles[xTile][yTile+1]);
		}
	}
	else if (yTile > 0 && board->tiles[xTile][yTile-1].contains(x, y)) {
		if (board->tiles[xTile][yTile-1].isSolid()) {
			if (hasBounced) {
				draw = false;
			}
			hasBounced = true;
			yDelta = -yDelta;
			y += yDelta;
		}
		else if (board->tiles[xTile][yTile-1].sentinelHere()) {
			draw = false;
			board->tiles[xTile][yTile-1].getSentinel()->direction = Sentinel::Down;//turn sentinel
		}
		else {
			currentTile = &(board->tiles[xTile][yTile-1]);
		}
	}
	else if (xTile < board->xSize - 1 && yTile > 0 && board->tiles[xTile+1][yTile-1].contains(x, y)) {
		if (board->tiles[xTile][yTile-1].sentinelHere()) {
			draw = false;
			board->tiles[xTile][yTile-1].getSentinel()->direction = Sentinel::Down;//turn sentinel
		}
		else if (board->tiles[xTile+1][yTile].sentinelHere()) {
			draw = false;
			board->tiles[xTile+1][yTile].getSentinel()->direction = Sentinel::Left;//turn sentinel
		}
		else if (board->tiles[xTile][yTile-1].isSolid() && board->tiles[xTile+1][yTile].isSolid()) {
			if (hasBounced) {
				draw = false;
			}
			hasBounced = true;
			xDelta = -xDelta;
			x += xDelta;
			yDelta = -yDelta;
			y += yDelta;
		}
		else if (board->tiles[xTile][yTile-1].isSolid()) { //up is solid
			if (hasBounced) {
				draw = false;
			}
			hasBounced = true;
			yDelta = -yDelta;
			y += yDelta;
		}
		else if (board->tiles[xTile+1][yTile].isSolid()) {
			if (hasBounced) {
				draw = false;
			}
			hasBounced = true;
			xDelta = -xDelta;
			x += xDelta;
		}
		else if (board->tiles[xTile+1][yTile-1].sentinelHere()) {
			draw = false;
			board->tiles[xTile+1][yTile-1].getSentinel()->direction = Sentinel::Down;//turn sentinel
		}
		else {
			currentTile = &(board->tiles[xTile+1][yTile-1]);
		}
	}
	else if (xTile < board->xSize - 1 && yTile < board->ySize - 1 && board->tiles[xTile+1][yTile+1].contains(x, y)) {
		if (board->tiles[xTile][yTile+1].sentinelHere()) {
			draw = false;
			board->tiles[xTile][yTile+1].getSentinel()->direction = Sentinel::Up;//turn sentinel
		}
		else if (board->tiles[xTile+1][yTile].sentinelHere()) {
			draw = false;
			board->tiles[xTile+1][yTile].getSentinel()->direction = Sentinel::Left;//turn sentinel
		}
		else if (board->tiles[xTile][yTile+1].isSolid() && board->tiles[xTile+1][yTile].isSolid()) {
			if (hasBounced) {
				draw = false;
			}
			hasBounced = true;
			xDelta = -xDelta;
			x += xDelta;
			yDelta = -yDelta;
			y += yDelta;
		}
		else if (board->tiles[xTile][yTile+1].isSolid()) { //down is solid
			if (hasBounced) {
				draw = false;
			}
			hasBounced = true;
			yDelta = -yDelta;
			y += yDelta;
		}
		else if (board->tiles[xTile+1][yTile].isSolid()) {
			if (hasBounced) {
				draw = false;
			}
			hasBounced = true;
			xDelta = -xDelta;
			x += xDelta;
		}
		else if (board->tiles[xTile+1][yTile+1].sentinelHere()) {
			draw = false;
			board->tiles[xTile+1][yTile+1].getSentinel()->direction = Sentinel::Up;//turn sentinel
		}
		else {
			currentTile = &(board->tiles[xTile+1][yTile+1]);
		}
	}
	else if (xTile > 0 && yTile < board->ySize - 1 && board->tiles[xTile-1][yTile+1].contains(x, y)) {
		if (board->tiles[xTile][yTile+1].sentinelHere()) {
			draw = false;
			board->tiles[xTile][yTile+1].getSentinel()->direction = Sentinel::Up;//turn sentinel
		}
		else if (board->tiles[xTile-1][yTile].sentinelHere()) {
			draw = false;
			board->tiles[xTile-1][yTile].getSentinel()->direction = Sentinel::Right;//turn sentinel
		}
		else if (board->tiles[xTile][yTile+1].isSolid() && board->tiles[xTile-1][yTile].isSolid()) {
			if (hasBounced) {
				draw = false;
			}
			hasBounced = true;
			xDelta = -xDelta;
			x += xDelta;
			yDelta = -yDelta;
			y += yDelta;
		}
		else if (board->tiles[xTile][yTile+1].isSolid()) { //up is solid
			if (hasBounced) {
				draw = false;
			}
			hasBounced = true;
			yDelta = -yDelta;
			y += yDelta;
		}
		else if (board->tiles[xTile-1][yTile].isSolid()) {
			if (hasBounced) {
				draw = false;
			}
			hasBounced = true;
			xDelta = -xDelta;
			x += xDelta;
		}
		else if (board->tiles[xTile-1][yTile+1].sentinelHere()) {
			draw = false;
			board->tiles[xTile-1][yTile+1].getSentinel()->direction = Sentinel::Up;//turn sentinel
		}
		else {
			currentTile = &(board->tiles[xTile-1][yTile+1]);
		}
	}
	else if (xTile > 0 && yTile > 0 && board->tiles[xTile-1][yTile-1].contains(x, y)) {
		if (board->tiles[xTile][yTile-1].sentinelHere()) {
			draw = false;
			board->tiles[xTile][yTile-1].getSentinel()->direction = Sentinel::Down;//turn sentinel
		}
		else if (board->tiles[xTile-1][yTile].sentinelHere()) {
			draw = false;
			board->tiles[xTile-1][yTile].getSentinel()->direction = Sentinel::Right;//turn sentinel
		}
		else if (board->tiles[xTile][yTile-1].isSolid() && board->tiles[xTile-1][yTile].isSolid()) {
			if (hasBounced) {
				draw = false;
			}
			hasBounced = true;
			xDelta = -xDelta;
			x += xDelta;
			yDelta = -yDelta;
			y += yDelta;
		}
		else if (board->tiles[xTile][yTile-1].isSolid()) { //up is solid
			if (hasBounced) {
				draw = false;
			}
			hasBounced = true;
			yDelta = -yDelta;
			y += yDelta;
		}
		else if (board->tiles[xTile-1][yTile].isSolid()) {
			if (hasBounced) {
				draw = false;
			}
			hasBounced = true;
			xDelta = -xDelta;
			x += xDelta;
		}
		else if (board->tiles[xTile-1][yTile-1].sentinelHere()) {
			draw = false;
			board->tiles[xTile-1][yTile-1].getSentinel()->direction = Sentinel::Down;//turn sentinel
		}
		else {
			currentTile = &(board->tiles[xTile-1][yTile-1]);
		}
	}
}

void Soundblast::drawBlast() {
	if (!draw)
		return;

	glBegin(GL_POLYGON);

	int radius = 4;
	glColor3f(1.0, 0.0, 1.0);

    for (int angle = 0; angle < 360; angle += 10) {
		float radians = M_PI * angle/180.0;
		float X = x + radius * cos(radians);
		float Y = y + radius * sin(radians);
		glVertex2f(X, Y);
    }

    glEnd();
}

void Soundblast::setCoordinates(int x, int y) {
	this->x = x;
	this->y = y;
}

void Soundblast::setMoveVector(int x, int y) {
	this->xDelta = x;
	this->yDelta = y;
}
