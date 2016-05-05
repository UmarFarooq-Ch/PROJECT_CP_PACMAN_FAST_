/*
* Board.h
*
*  Created on: April 28, 2016
*      Author: Umar Farooq
*/
#ifndef _BOARD_H_
#define _BOARD_H_

#include <gl/glew.h>
#include <GL/glut.h>
#include <iostream>
#include "util.h"
using namespace std;
class Board {
private:
	int pebbles_left;
	int xcellsize, ycellsize;
	int lwidth;
	float cwidth;
	int m_n_pacmanDandi;
	//array for eating
	int tp_array[31][28];
	ColorNames pcolor, bcolor, gcolor;

public:
	static const int BOARD_X;
	static const int BOARD_Y;
	Board(int xsize = 20, int ysize = 20);

	~Board(void);

	//draw the board
	void Draw(void);

	static int GetBoardX() {
		return BOARD_X;
	}
	static int GetBoardY() {
		return BOARD_Y;
	}
	int GetMidX() {
		return BOARD_X * xcellsize / 2.0;
	}
	int GetMidY() {
		return BOARD_Y * ycellsize / 2.0;
	}
	int GetCellSize() {
		return xcellsize;
	}
	void GetInitPacmanPosition(int &x, int &y) {
		x = 14 * xcellsize;
		y = 9 * ycellsize + ycellsize / 2;
	}
	void GetInitPinkyPosition(int &x, int &y) {
		x = 11 * xcellsize/* - xcellsize / 2.0*/;
		y = 18 * ycellsize - ycellsize / 2.0;
	}
	void GetInitTextPosition(int &x, int &y) {
		x = 13 * xcellsize;
		y = 14 * ycellsize;
	}
	virtual inline ColorNames getColor(void) const { return RED; }
	inline int getDandi(void) const { return this->m_n_pacmanDandi; }
	inline void increaseDandi(void) { ++this->m_n_pacmanDandi; }
	int getBoardPart(const int & pXVertex, const int & pYVertex) const; // return the value at location pXVertex, pYVertex in Board_array
	void setBoardPart(const int & pXVertex, const int & pYVertex, const int & obj);
	virtual void nextMove(const bool & aliveOfPinky);
	virtual void setMove(const bool & pCheck = false);
	virtual void setEyesDirection(const int & pEyesDirection);
	virtual inline int getEyesDirection(void)const { return 0; }
	virtual bool getMove(void) const;
	virtual int getX(void) const;
	virtual int getY(void) const;
	virtual inline void setPosition(const int & pX, const int & pY) {}
	virtual inline void getPosition(int & pX, int & pY) const {}
	virtual inline float getRadian(void) const { return 0; }
	virtual inline void setRadian(const float & pValueRadian) {}
	virtual inline int getPendingDirection(void) const { return 0; }
	virtual inline bool getAlive() const { return false; }
	virtual inline string getScore(void) const { return ""; }
	virtual inline int getPacmanLifes(void)const { return 0; }
	virtual inline void decreasePacmanLifes(void) { }
	virtual inline void resetPacman(void) {}
	//GhostFunctions
	virtual void setTargetBoxes(const int & x0, const int & y0, const int & x1, const int & y1, const int & x2, const int & y2, const int & x3, const int & y3);
	virtual bool BFS(void);
	virtual inline void setPredecesorToNull(void) {}
	virtual void nextMoveGhost(const int & PacmanX, const int & PacmanY);
	virtual inline void increaseTime(void) { }
	virtual inline void setTimeZero(void) {  }
	virtual inline int getTime(void) { return 0; }
	virtual inline int getGhostMode(void) const { return 0; }
	virtual inline void setGhostMode(const int & pMode) { return; }
	virtual inline void getCurrentTarget(int & pX, int & pY) const {}
	//virtual inline void setPacmanPosition(const int & pX, const int & pY) {}
}
;
#endif