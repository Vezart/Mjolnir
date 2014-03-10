#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <time.h>

#include "Board.h"

//Functions
void initialize();
void displayFunction();
void fixedUpdate(int value);

//Constants
const int WINDOW_SIZE_X = 800;
const int WINDOW_SIZE_Y = 800;
const int TILE_SIZE = 50;

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
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_SIZE_X, WINDOW_SIZE_Y, 0, 0, 1);

    //board = new Board();

}

void displayFunction() {
    //board.drawBoard();
    //player.drawPlayer();
}

void fixedUpdate(int deltaTime) {
    glutTimerFunc(deltaTime, fixedUpdate, 1);
    glutPostRedisplay();
}
