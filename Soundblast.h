#pragma once

#include "Tile.h"
#include "Board.h"

class Soundblast {
    public:
		Soundblast(int xDelta, int yDelta);
		void update(int deltaTime);
		void setCoordinates(int x, int y);
		void setMoveVector(int x, int y);
    private:
		int xDelta;
		int yDelta;
		int x;
		int y;
		Board* board;
		Tile* currentTile;
};
