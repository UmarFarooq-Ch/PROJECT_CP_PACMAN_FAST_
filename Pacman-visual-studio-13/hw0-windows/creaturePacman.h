#pragma once
#include "Creature.h"
#include <string>
//testing new branch

class creaturePacman : public Creature
{
private:
	//static int score;
	int Lifes;
	bool  m_n_move;	//member_numeric
	int score;
	float m_n_radians;	//member_numeric
	short check;	//this data member is used to stop thokaren of Pacman with walls
public:
	creaturePacman(const int & pX = 280, const int & pY = 190, const string & pNameOfCreature = "pacman", const ColorNames & pValue = YELLOW, const bool & pAliveStatus = true, const int & pEyesDirection = LEFT_, const float & pValueRadian = 6.0);
	virtual ~creaturePacman();
	void nextMove(const bool & aliveOfPinky);	//draw function call it so it this fuunction will change pacman vertexs according to its direction and position
	inline void setMove(const bool & pCheck = false) { m_n_move = pCheck; }
	inline bool getMove(void) const { return this->m_n_move; }
	inline float getRadian(void) const { return this->m_n_radians; }
	inline void setRadian(const float & pValueRadian) { this->m_n_radians = pValueRadian; }
	inline string getScore(void) const
	{
		string tempS = "";
		tempS += to_string(score);
		return tempS;
	}
	inline int getPacmanLifes(void)const { return this->Lifes; }
	inline void decreasePacmanLifes(void) { --this->Lifes; }
	inline void resetPacman(void) 
	{
		m_n_move = false;
		m_n_radians = 6.0;
		check = 0;
		m_n_xVertex = 270;
		m_n_yVertex = 190;
		//glutPostRedisplay();
	}
};

