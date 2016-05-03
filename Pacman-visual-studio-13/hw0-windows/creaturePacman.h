#pragma once
#include "Creature.h"
//testing new branch

class creaturePacman : public Creature
{
private:
	//static int score;
	bool  m_n_move;	//member_numeric
	float m_n_radians;	//member_numeric
	short check;	//this data member is used to stop thokaren of Pacman with walls
	//bool startOfGame;
public:

	/*nextAllowed*/
	creaturePacman(const int & pX = 280, const int & pY = 190, const string & pNameOfCreature = "pacman", const ColorNames & pValue = YELLOW, const bool & pAliveStatus = true, const int & pEyesDirection = LEFT_, const float & pValueRadian = 6.0);
	virtual ~creaturePacman();
	void nextMove(void);	//draw function call it so it this fuunction will change pacman vertexs according to its direction and position
	inline void setMove(const bool & pCheck = false) { m_n_move = pCheck; }
	inline bool getMove(void) const { return this->m_n_move; }
	inline float getRadian(void) const { return this->m_n_radians; }
	inline void setRadian(const float & pValueRadian) { this->m_n_radians = pValueRadian; }
	//inline bool getStartOfGame(void) const { return this->startOfGame; }
};

