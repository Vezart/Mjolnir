#include "Board.h"

Board::Board() {
    tiles = new Tile[16][16];
}

Board::Board(int xSize, int ySize) {
    tiles = new Tile[xSize][ySize];
}

void Board::drawBoard() {
    //Nothing for now
}

//void Board::setPlayer(Player player) {
//    this.player = player;
//}
