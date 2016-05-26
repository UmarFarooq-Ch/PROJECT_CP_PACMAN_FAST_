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
#include "Ghost.h"
#include "Block.h"
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

//
//time_t tm = time(0);
//int t = (int)tm;

void Display()/**/ {
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0.0/*Green Component*/,
		0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors
	//for (int y = 700;y > 0;y -= 20)
	//	DrawLine(0, y, 560, y, 1);
	//for (int x = 0; x < 660;x += 20)
	//	DrawLine(x, 0, x, 720, 1);
	(*b)->Draw();
	
	if (b[1]->getNumberOfFood() >= 245)
	{
		for (int i = 1; i < 6; ++i)
		{
			b[i]->setAlive(false);
		}
			DrawCircle(280, 360, 250, colors[WHITE]);
			DrawString(215, 350, "YOU WON", colors[BLACK]);
	}
	switch (b[1]->getPacmanLifes())
	{
	case 3:
		DrawCircle(100, 30, 18, colors[YELLOW]);
	case 2:
		DrawCircle(60, 30, 18, colors[YELLOW]);
	case 1:
		DrawCircle(20, 30, 18, colors[YELLOW]);
		break;
	default:
		DrawCircle(280, 360, 400, colors[GREEN]);
		DrawCircle(280, 360, 300, colors[RED]);
		DrawCircle(280, 360, 260, colors[LIGHT_GRAY]);
		DrawCircle(280, 360, 240, colors[RED]);
		DrawCircle(280, 360, 200, colors[BLUE]);
		DrawCircle(280, 360, 100, colors[WHITE]);
		DrawString(205, 350, "GAME OVER", colors[BLACK]);
	}	
	if (b[1])
	//Conditions for BonusFood
	if (b[1]->getBonusFood())
	{
		for (int i = 2;i < 6;++i)
		{
			b[i]->setGhostMode(3);
			b[i]->frightenedMode();
		}
		b[1]->setBonusFoood(false);
		b[1]->setTimeZero();
	}
	b[1]->increaseTime();
	//When Pacman eates bonus food then the timer of pacman set to zero
	//and pacman remaining lifes will be noted to variable 'lifesWhenEatedBonusFood'
	//if this lifesWhenEatedBonusFood and actual pacman life remain same then we will
	//limit this ability of pacman by value of 150
	//if time increased by 150 then stopFreightendMode of ghost(who are in frientened mode) will be called
	if (b[1]->getLifeWhenBonusEated() == b[1]->getPacmanLifes())
	{
		if (b[1]->getTime() > 150)
		{
			for (int i = 2; i < 6;++i)
			{
				if (b[i]->getGhostMode() == 3)
					b[i]->stopFrightenedMode();
			}
			b[1]->setLifeWhenBonusEated(0);
		}
	}
	if (b[1]->getLifeWhenBonusEated() > b[1]->getPacmanLifes())
	{
		b[2]->setReset(true);
	}
	int x, y;
	//(*b)->GetInitPinkyPosition(x, y);
	//DrawGhost(x, y, PINK, 2 * (*b)->GetCellSize(), 2 * (*b)->GetCellSize());
	b[1]->getPosition(x, y);
	DrawPacMan(x, y, (*b)->GetCellSize() - 2, YELLOW);
	
	
	b[2]->increaseTime();

	if (b[2]->getTime() < 300 && b[2]->getGhostMode() != 3)
	{
		//b[1]->getPosition(x, y);
		b[2]->setGhostMode(1);
	}
	else if (b[2]->getTime() >= 300 && b[2]->getGhostMode() != 3)
	{
		b[2]->setGhostMode(2);
		/////x = 30, y = 70;
		if (b[2]->getTime() > 450)
			b[2]->setTimeZero();
	}
	b[2]->nextMoveGhost();
	b[2]->getPosition(x, y);
	DrawGhost(x, y, b[2]->getColor(), 2 * (*b)->GetCellSize(), 2 * (*b)->GetCellSize());

	//for inky
	b[3]->increaseTime();



	if (b[3]->getTime() < 400 && b[3]->getGhostMode() != 3)
	{
		//b[1]->getPosition(x, y);
		b[3]->setGhostMode(2);
	}
	else if (b[3]->getTime() >= 400 && b[3]->getGhostMode() != 3)
	{
		b[3]->setGhostMode(1);
		/////x = 30, y = 70;
		if (b[3]->getTime() > 600)
			b[3]->setTimeZero();
	}
	b[3]->nextMoveGhost();
	b[3]->getPosition(x, y);
	DrawGhost(x, y, b[3]->getColor(), 2 * (*b)->GetCellSize(), 2 * (*b)->GetCellSize());


	//for Pinky
	b[4]->increaseTime();

	if (b[4]->getTime() < 400 && b[4]->getGhostMode() != 3)
	{
		//b[1]->getPosition(x, y);
		b[4]->setGhostMode(2);
	}
	else if (b[4]->getTime() >= 400 && b[4]->getGhostMode() != 3)
	{
		b[3]->setGhostMode(1);
		/////x = 30, y = 70;
		if (b[4]->getTime() > 600)
			b[4]->setTimeZero();
	}
	b[4]->nextMoveGhost();
	b[4]->getPosition(x, y);
	DrawGhost(x, y, b[4]->getColor(), 2 * (*b)->GetCellSize(), 2 * (*b)->GetCellSize());



	//for cylide
	b[5]->increaseTime();

	if (b[5]->getTime() < 200 && b[5]->getGhostMode() != 3)
	{
		//b[1]->getPosition(x, y);
		b[5]->setGhostMode(1);
	}
	else if (b[5]->getTime() >= 200 && b[5]->getGhostMode() != 3)
	{
		b[5]->setGhostMode(2);
		/////x = 30, y = 70;
		if (b[5]->getTime() > 500)
			b[5]->setTimeZero();
	}
	b[5]->nextMoveGhost();
	b[5]->getPosition(x, y);
	DrawGhost(x, y, b[5]->getColor(), 2 * (*b)->GetCellSize(), 2 * (*b)->GetCellSize());


	x = (*b)->GetMidX();
	DrawString(x - 60, 680, "SCORE: " + b[1]->getScore(), colors[5]);
	//	glPopMatrix();
	glutSwapBuffers(); // do not modify this line..

	//Below is timer Function implementation
	//save pacman vertex to ghost class so it will check when ever pacman is detected it will kill
	/*b[1]->getPosition(x, y);
	b[2]->setPacmanPosition(x, y);
*/

	//if (b[2]->getAlive() && b[3]->getAlive() && b[4]->getAlive() && b[5]->getAlive())	//Game ko stop krne ke liye ye conditions lagai haen
	b[1]->increaseDandi();
	if (b[1]->getMove())
	{
		int local_variable = b[1]->getPendingDirection();
		if (local_variable != 0)
			b[1]->setEyesDirection(local_variable);
		b[1]->nextMove(b[2]->getAlive());
		//glutPostRedisplay();
	}


	//Conditions to start game of 2 other pacman
	if (b[1]->getNumberOfFood() >= 82)
		b[4]->setCanMove(true);
	if (b[1]->getNumberOfFood() >= 163)
		b[5]->setCanMove(true);


	//conditions for GameOver

	if (b[1]->getPacmanLifes() <= 0)
	{
		for (int i = 1;i < 6;++i)
			b[i]->setAlive(false);
	}
	for (int i = 2; i <6 ;++i)
		if (b[i]->getReset())
		{
			b[1]->resetPacman();
			for (int x = 0; x < 6;++x)
				b[x]->resetGhost();
		}
	glutPostRedisplay();
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
	}

	else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

			b[1]->setEyesDirection(1);
	}

	else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

			b[1]->setEyesDirection(4);
	}

	else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

			b[1]->setEyesDirection(2);
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

	if  (key == 112 || key == 80)
		system("pause");

	if (key == 82 || key == 114)
		b[2]->setReset(true);
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

	///////////////y///x//
	CBlock blocks[36][28];
	for (int i = 0, y = 10; i < 36;++i, y += 20)
		for (int j = 0, x = 10; j < 28;x += 20, ++j)
		{
			blocks[i][j].setVertex(x, y);
			CBlock *temp = NULL;
			blocks[i][j].initializeNeighbours(*temp, *temp, *temp, *temp);
			blocks[i][j].setPredecesorToNull();
		}
	b = new Board *[6]; // create a new board object to use in the Display Function ...
	b[0] = new Board;
	creaturePacman PaCman;
	b[1] = &PaCman;


	b[2] = new CGhost(260, 410, "BLINKY", RED, true, 0, 2, blocks, &PaCman, true);
	b[3] = new CGhost(260, 350, "INKY",LIGHT_SKY_BLUE, true, 0, 2, blocks, &PaCman, true);
	b[4] = new CGhost(220, 350, "PINKY", LIGHT_PINK, true, 0, 2, blocks, &PaCman);
	b[5] = new CGhost(300, 350, "CYLIDE", SANDY_BROWN, true, 0, 2, blocks, &PaCman);
	for (int i = 3; i <= 31; ++i)
		for (int j = 1; j <= 26; ++j)
		{
			int local = b[0]->getBoardPart(j, 35 - i);	//ye if check ker rha he ke ager wo koi chalne wali jaga he tu os ke neighbour save kere warna na kre

			if (local == 16 || local == 17 || local == 18)
			{
				CBlock *array[4];
				int localR = b[0]->getBoardPart(j + 1, 35 - i);
				//if (i == 3 && j == 1)
				//b[0]->setBoardPart(j + 1, 35 - i, 17);
				if (localR == 17 || localR == 16 || localR == 18)
					array[0] = &blocks[i][j + 1];
				else
					array[0] = NULL;
				int localD = b[0]->getBoardPart(j, 35 - i + 1);
				/*	if (i == 3 && j == 1)
						b[0]->setBoardPart(j, 35 - i + 1,17);
				*/	if (localD == 17 || localD == 16 || localD == 18)
						array[1] = &blocks[i - 1][j];
				else
					array[1] = NULL;
				int localL = b[0]->getBoardPart(j - 1, 35 - i);
				//if (i == 3 && j == 1)
				//	b[0]->setBoardPart(j - 1, 35 - i, 17);
				if (localL == 17 || localL == 16 || localL == 18)
					array[2] = &blocks[i][j - 1];
				else
					array[2] = NULL;
				int localU = b[0]->getBoardPart(j, 35 - i - 1);
				//if (i == 3 && j == 1)
				//	b[0]->setBoardPart(j, 35 - i - 1, 17);
				if (localU == 17 || localU == 16 || localU == 18)
					array[3] = &blocks[i + 1][j];
				else
					array[3] = NULL;
				blocks[i][j].initializeNeighbours(*array[0], *array[1], *array[2], *array[3]);
			}
		}
	//Manually Initializing some blocks
	CBlock *tempEmptyBlock = NULL;
	blocks[18][1].initializeNeighbours(blocks[18][2], *tempEmptyBlock, blocks[18][0], *tempEmptyBlock);
	blocks[18][0].initializeNeighbours(blocks[18][1], *tempEmptyBlock, blocks[18][27], *tempEmptyBlock);
	blocks[18][27].initializeNeighbours(blocks[18][0], *tempEmptyBlock, blocks[18][26], *tempEmptyBlock);
	blocks[18][26].initializeNeighbours(blocks[18][27], *tempEmptyBlock, blocks[18][25], *tempEmptyBlock);
	blocks[18][11].initializeNeighbours(blocks[18][12], *tempEmptyBlock, *tempEmptyBlock, *tempEmptyBlock);
	blocks[18][12].initializeNeighbours(blocks[18][13], *tempEmptyBlock, blocks[18][11], *tempEmptyBlock);
	blocks[18][13].initializeNeighbours(blocks[18][14], *tempEmptyBlock, blocks[18][12], blocks[19][13]);
	blocks[18][14].initializeNeighbours(blocks[18][15], *tempEmptyBlock, blocks[18][13], *tempEmptyBlock);
	blocks[18][15].initializeNeighbours(blocks[18][16], *tempEmptyBlock, blocks[18][14], *tempEmptyBlock);
	blocks[18][16].initializeNeighbours(*tempEmptyBlock, *tempEmptyBlock, blocks[18][15], *tempEmptyBlock);
	blocks[19][13].initializeNeighbours(*tempEmptyBlock, blocks[18][13], *tempEmptyBlock, blocks[20][13]);
	blocks[20][13].initializeNeighbours(*tempEmptyBlock, blocks[19][13], *tempEmptyBlock, blocks[21][13]);
	b[2]->setTargetBoxes(1, 4, 12, 3, 9, 8, 9, 18);
	b[3]->setTargetBoxes(12, 30, 1, 30, 3, 24, 12, 21);
	b[4]->setTargetBoxes(15, 30, 21, 24, 19, 18, 26, 24);
	b[5]->setTargetBoxes(26, 11, 26, 3, 15, 5, 15, 12);
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
