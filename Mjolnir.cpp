#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <time.h>

#include "Board.h"
#include "Player.h"

//To compile: g++ Mjolnir.cpp Board.cpp Tile.cpp Player.cpp Sentinel.cpp -lglut

using namespace std;

//Functions
void initialize();
void displayFunction();
void fixedUpdate(int value);
void keyboardInput(unsigned char key, int xMouse, int yMouse);
void mouseInput(int button, int state, int x, int y);

//Constants
const int WINDOW_SIZE_X = 768;
const int WINDOW_SIZE_Y = 768;
const int TILE_SIZE = 48;
const int MAX_LEVELS = 2;

//Variables
Board *board;
Player *player;
int currentLevel;

//Main!
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
    glutInitWindowPosition(200, 200);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Mjolnir");
    glutDisplayFunc(displayFunction);
	glutKeyboardFunc(keyboardInput);
	glutMouseFunc(mouseInput);
    glutTimerFunc(33, fixedUpdate, 1);
	currentLevel = 1;
    initialize();
    glutMainLoop();
}

void initialize() {
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_SIZE_X, WINDOW_SIZE_Y, 0, 0, 200);

	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

    board = new Board(WINDOW_SIZE_X / TILE_SIZE, WINDOW_SIZE_Y / TILE_SIZE, TILE_SIZE);
	board->loadBoard(currentLevel);

	int startTileX;
	int startTileY;

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			if (board->tiles[i][j].tileChar == 'S') {
				startTileX = i;
				startTileY = j;
			}
		}
	}

	player = new Player(startTileX, startTileY, TILE_SIZE, board);
	player->loadPlayerTexture();

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void displayFunction() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	

    board->drawBoard();
    player->drawPlayer();

	glFlush();
}

void keyboardInput(unsigned char key, int xMouse, int yMouse) {
	glutIgnoreKeyRepeat(true);

	switch (key) {
		case 'w':
			player->moveUp();
			break;
		case 's':
			player->moveDown();
			break;
		case 'a':
			player->moveLeft();
			break;
		case 'd':
			player->moveRight();
			break;
	}
	
	glutPostRedisplay();
}

void mouseInput(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		player->shootBlast(x, y);
	}
}

void fixedUpdate(int deltaTime) {
	//board->update();
	if (player->update(deltaTime)) {
		if (currentLevel < MAX_LEVELS) {
			currentLevel++;
			initialize();
		}
		else {
			exit(0);
		}
	}

    glutTimerFunc(deltaTime, fixedUpdate, 1);
    glutPostRedisplay();
}
