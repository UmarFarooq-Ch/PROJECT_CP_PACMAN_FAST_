//============================================================================
// Name        : Pacman_.cpp
// Author      : Muhammad Umar Farooq i15-0108
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Pacman...
//============================================================================

#ifndef PACMAN_CPP_
#define PACMAN_CPP_
#include "Board.h"
#include "util.h"
#include <iostream>
#include <string>
#include "creaturePacman.h"
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
Board **b;
// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
*  that is what dimensions (x and y) your game will have
*  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
* */
void SetCanvasSize(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void DrawGhost(int x/*starting x*/, int y/*starting y*/,
	ColorNames color/*color*/, float gw = 6/*Ghost Width in Units*/,
	float gh = 7/*Ghost Height in Units*/) {
	int ogw = 6, ogh = 7;

	glPushMatrix();
	float sx = (float)gw / ogw, sy = (float)gh / ogh;
	glTranslatef(x, y, 1);
	glScalef(sx, sy, 1);

	// Draw ghost
	DrawRoundRect(0, 1, 6, 3, colors[color]);
	DrawCircle(3, 4, 3.01, colors[color]);
	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	//  legs
	DrawCircle(0.75, 1, 0.75, colors[color]);
	DrawCircle(3.25, 1, 0.75, colors[color]);
	DrawCircle(5.85, 1, 0.75, colors[color]);

	glPopMatrix();
	//	glPopMatrix();

	// eyes

	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	DrawCircle(1.85, 3.95, 0.75, colors[WHITE]);
	DrawCircle(4.95, 3.95, 0.75, colors[WHITE]);
	glPopMatrix();

	// eyes
	DrawCircle(1.65, 4.25, 0.45, colors[BLUE]);
	DrawCircle(4.45, 4.25, 0.45, colors[BLUE]);
	glPopMatrix();
}

//Number of Vertices used to draw Pacman Circle...
// x= r cos (theta), y= r sin(theta)
const int npmvertices = 1220;
GLfloat pmvertices[npmvertices][2];
void InitPMVertices(float radius) {

	float hdegree = (M_PI - M_PI / 2.0) / 360.0;
	float angle = M_PI + M_PI / (b[1]->getRadian());
	for (int i = 0; i < npmvertices; ++i) {
		pmvertices[i][0] = radius * cos(angle);
		pmvertices[i][1] = radius * sin(angle);
		angle += hdegree;
	}
}

void DrawPacMan(float sx/*center x*/, float sy/*center y*/,
	float radius/*Radius*/, const ColorNames &colorname/*Pacman Colour*/) {

	glColor3fv(colors[colorname]); // set the circle color
	InitPMVertices(radius);
	glBegin(GL_TRIANGLE_FAN);
	glVertex4f(sx, sy, 0, 1);
	for (int i = 0; i < npmvertices; ++i)
		glVertex4f(sx + pmvertices[i][0], sy + pmvertices[i][1], 0, 1);
	glEnd();
	//Dandi of Pacman
	int local_variable = b[1]->getDandi();
	if (local_variable % 2 == 0)
		DrawCircle(b[1]->getX(), b[1]->getY(), 18, colors[YELLOW]);
	//End of Dandi
	//Direction of Pacman
	switch (b[1]->getEyesDirection())
	{
	case 3:	//When pacman is looking left
	case 4:	//when pacman is looking upward
		DrawCircle(b[1]->getX() - radius + radius / 2, b[1]->getY() + (radius - radius / 2), radius / 10, colors[BLACK]);
		break;
	case 1:	//when pacman is looking right
		DrawCircle(b[1]->getX() + (radius - radius / 2), b[1]->getY() + (radius - radius / 2), radius / 10, colors[BLACK]);
		break;
	case 2:	//when pacman is looking down
		DrawCircle(b[1]->getX() + (radius - radius / 2), b[1]->getY() -radius + radius / 2, radius / 10, colors[BLACK]);
		break;
	}
	
}
/*
* Main Canvas drawing function.
* */

//Creature *cp;

void Display()/**/ {
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0.0/*Green Component*/,
		0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors
	for (int y = 700;y > 0;y -= 20)
		DrawLine(0, y, 560, y, 1);
	for (int x = 0; x < 660;x += 20)
		DrawLine(x, 0, x, 720, 1);
	(*b)->Draw();
	int x, y;
	(*b)->GetInitPinkyPosition(x, y);
	DrawGhost(x, y, PINK, 2 * (*b)->GetCellSize(), 2 * (*b)->GetCellSize());

	b[1]->getPosition(x, y);
	DrawPacMan(x, y, (*b)->GetCellSize() - 2, YELLOW);


	x = (*b)->GetMidX();
	DrawString(x - 60, 680, "Score = 000", colors[5]);
	//	glPopMatrix();
	glutSwapBuffers(); // do not modify this line..
	b[1]->increaseDandi();
	if (b[1]->getMove())
	{
		int local_variable = b[1]->getPendingDirection();
		if (local_variable != 0)
			b[1]->setEyesDirection(local_variable);
		b[1]->nextMove();
		glutPostRedisplay();
	}
	//glutPostRedisplay();
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
* is pressed from the keyboard
*
* You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
*
* This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
* program coordinates of mouse pointer when key was pressed.
*
* */
void NonPrintableKeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...

			b[1]->setEyesDirection(3);
			//b[1]->setMove(true);
			//b[1]->setRadian(6.0);
			//glutPostRedisplay();

	}
	else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

			b[1]->setEyesDirection(1);
			//b[1]->setMove(true);
			//b[1]->setRadian(-1.2);
			//glutPostRedisplay();
	}
	else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

			b[1]->setEyesDirection(4);
			//b[1]->setRadian(-3.0);
			//b[1]->setMove(true);
			//glutPostRedisplay();

	}

	else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

			b[1]->setEyesDirection(2);
			//b[1]->setRadian(1.5);
			//b[1]->setMove(true);
			//glutPostRedisplay();
			//system("pause");

	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	* this function*/
	/*
	glutPostRedisplay();
	*/
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
* is pressed from the keyboard
* This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
* program coordinates of mouse pointer when key was pressed.
* */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == KEY_ESC/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
}

/*
* This function is called after every 1000.0/FPS milliseconds
* (FPS is defined on in the beginning).
* You can use this function to animate objects and control the
* speed of different moving objects by varying the constant FPS.
*
* */
void Timer(int m) {
	// implement your functionality here
	//if (b[1]->getMove())
	//{
	//	b[1]->nextMove();
	//	glutPostRedisplay();
	//}
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1.0 / FPS, Timer, 0);
}

/*
* our gateway main function
* */
int main(int argc, char*argv[]) {

	b = new Board *[2]; // create a new board object to use in the Display Function ...
	b[0] = new Board/*creaturePacman*/;
	b[1] = new creaturePacman;
	int width = 560, height = 720; // i have set my window size to be 800 x 600
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(800, 5); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("CP's Pacman"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

								  // Register your functions to the library,
								  // you are telling the library names of function to call for different tasks.
								  //glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
									 // This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(200.0 / FPS, Timer, 0);

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* PACMAN_CPP_ */
