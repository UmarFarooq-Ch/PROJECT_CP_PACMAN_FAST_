#pragma once
#include "Creature.h"
#include "Block.h"
#include "creaturePacman.h"
class CGhost : public Creature
{
protected:
	const int fixXVertex, fixYVertex;
	const string fixName;
	const ColorNames fixColor;
	enum Mode
	{
		NILL,
		CHASE,
		SCATTER,
		FRIGHTENED
	};
	int m_n_ghostMode;	//member_numeric
	int m_n_targetBoxes[8];	//member_numeric
	int currentTargentxVertex, currentTargetyVertex;
	creaturePacman * PACMAN;
	int nextMove;
	bool temp;
	//int time;
	bool canMove;//this variable is true when noOfFood remains less then 30 according to different ghost
	int index; // ye variable targetBox ke index ko change kerna ke liye he
	CBlock  *blocks_array[36][28];
public:
	CGhost(const int & pX, const int & pY, const string & pNameOfCreature, const ColorNames & pValue, const bool & pAliveStatus = true, const int & pEyesDirection = NILL_, const int & pGhostMode = NILL_, CBlock array[][28] = NULL, creaturePacman * ptrPACMAN = NULL, const bool & pCanMove = false);
	void setTargetBoxes(const int & x0, const int & y0, const int & x1, const int & y1, const int & x2, const int & y2, const int & x3, const int & y3);
	bool BFS(void);
	void nextMoveGhost();
	virtual ~CGhost();
	//inline void increaseTime(void) { ++time; }
	//inline void setTimeZero(void) { time = 0; }
	//inline int getTime(void) { return time; }
	inline int getGhostMode(void) const { return this->m_n_ghostMode; }
	inline void setGhostMode(const int & pMode) { this->m_n_ghostMode = pMode; }
	inline void getCurrentTarget(int & pX, int & pY) const { pX = currentTargentxVertex; pY = currentTargetyVertex; return; }
	inline void resetGhost(void)
	{
		m_n_ghostMode = SCATTER;
		m_n_xVertex = fixXVertex;
		m_n_yVertex = fixYVertex;
		m_b_reset = false;
		m_b_alive = true;
		m_e_c_color = fixColor;
		temp = false;
		time = 0;
		index = 0;
		//nextMoveGhost(20, 60);
	}
	inline void setCanMove(const bool & pM) { canMove = pM; }
	inline void frightenedMode(void)
	{
		currentTargentxVertex = m_n_targetBoxes[index] * 20;
		currentTargetyVertex = m_n_targetBoxes[index + 1] * 20;
		m_e_c_color = BLUE;
		m_n_ghostMode = FRIGHTENED;
	}
	inline void stopFrightenedMode(void)
	{

		m_e_c_color = fixColor;
		m_n_ghostMode = SCATTER;
	}
};

