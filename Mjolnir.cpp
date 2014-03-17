#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <time.h>

#include "Board.h"

using namespace std;

//Functions
void initialize();
void displayFunction();
void fixedUpdate(int value);

//Constants
const int WINDOW_SIZE_X = 768;
const int WINDOW_SIZE_Y = 768;
const int TILE_SIZE = 48;

//Variables
Board *board;
//Player player;


//Main!
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
    glutInitWindowPosition(200, 200);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Mjolnir");
    glutDisplayFunc(displayFunction);
    glutTimerFunc(33, fixedUpdate, 1);
    initialize();
    glutMainLoop();
}

void initialize() {
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_SIZE_X, WINDOW_SIZE_Y, 0, 0, 200);

    board = new Board(WINDOW_SIZE_X / TILE_SIZE, WINDOW_SIZE_Y / TILE_SIZE, TILE_SIZE);

}

void displayFunction() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	

    board->drawBoard();
    //player.drawPlayer();

	glFlush();
}

void fixedUpdate(int deltaTime) {
    glutTimerFunc(deltaTime, fixedUpdate, 1);
    glutPostRedisplay();
}
