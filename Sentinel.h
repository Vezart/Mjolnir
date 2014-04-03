#pragma once

#include <GL/glut.h>

#include "libim/im_color.h"

class Sentinel {
    public:
		enum Direction { Up, Down, Left, Right };
		Sentinel();
		void loadTexture();
		void drawSentinel(int xLeft, int xRight, int yTop, int yBottom);
		Direction direction;
    private:
		unsigned char* textureUp;
		unsigned char* textureDown;
		unsigned char* textureLeft;
		unsigned char* textureRight;
		int xDim;
		int yDim;
		void init_texture(char *name, unsigned char *&texture, int &xdim, int &ydim);
		void drawUp(int xLeft, int xRight, int yTop, int yBottom);
		void drawDown(int xLeft, int xRight, int yTop, int yBottom);
		void drawLeft(int xLeft, int xRight, int yTop, int yBottom);
		void drawRight(int xLeft, int xRight, int yTop, int yBottom);
};
