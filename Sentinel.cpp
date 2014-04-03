#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "Sentinel.h"

using namespace std;

Sentinel::Sentinel() {
	
}

void Sentinel::loadTexture() {
	string filename = "Sentinel/sentinelUp.jpg";
	init_texture((char*)filename.c_str(), textureUp, xDim, yDim);
	filename = "Sentinel/sentinelDown.jpg";
	init_texture((char*)filename.c_str(), textureDown, xDim, yDim);
	filename = "Sentinel/sentinelLeft.jpg";
	init_texture((char*)filename.c_str(), textureLeft, xDim, yDim);
	filename = "Sentinel/sentinelRight.jpg";
	init_texture((char*)filename.c_str(), textureRight, xDim, yDim);
}

void Sentinel::drawSentinel(int xLeft, int xRight, int yTop, int yBottom) {
	switch(direction) {
		case Sentinel::Up:		drawUp(xLeft, xRight, yTop, yBottom);
								break;
		case Sentinel::Down:	drawDown(xLeft, xRight, yTop, yBottom);
								break;
		case Sentinel::Left:	drawLeft(xLeft, xRight, yTop, yBottom);
								break;
		case Sentinel::Right:	drawRight(xLeft, xRight, yTop, yBottom);
								break;
	}
}

void Sentinel::drawUp(int xLeft, int xRight, int yTop, int yBottom) {
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

void Sentinel::drawDown(int xLeft, int xRight, int yTop, int yBottom) {
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

void Sentinel::drawLeft(int xLeft, int xRight, int yTop, int yBottom) {
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

void Sentinel::drawRight(int xLeft, int xRight, int yTop, int yBottom) {
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


void Sentinel::init_texture(char *name, unsigned char *&texture, int &xdim, int &ydim)
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
