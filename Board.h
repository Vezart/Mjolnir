#include <GL/glut.h>

#include "Tile.h"


class Board {
    public:
        Board();
		Board(int xSize, int ySize, int tileSize);
		void loadBoard(string filename);
		void drawBoard();
		//void setPlayer(Player player);
		int xSize;
		int ySize;
		int tileSize;
    private:
		Tile **tiles;
		char **tileChars;
		void drawCircle(int x, int y, float radius); //Temporary
		//Player player;
};
