#include <GL/glut.h>
#include "Tile.h"


class Board {
    public:
        Board();
	Board(int xSize, int ySize, int tileSize);
	void drawBoard();
	//void setPlayer(Player player);
	int xSize;
	int ySize;
	int tileSize;
    private:
	Tile **tiles;
	
	void drawCircle(int x, int y, float radius); //Temporary
	//Player player;
};
