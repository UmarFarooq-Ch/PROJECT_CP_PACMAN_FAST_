#pragma once
#include "Creature.h"
#include "Block.h"
class CGhost : public Creature
{
protected:
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
	int nextMove;
	bool temp;
	CBlock  *blocks_array[36][28];
public:
	CGhost(const int & pX, const int & pY, const string & pNameOfCreature, const ColorNames & pValue, const bool & pAliveStatus = true, const int & pEyesDirection = NILL_, const int & pGhostMode = NILL_, CBlock array[][28] = NULL);
	void setTargetBoxes(const int & x0, const int & y0, const int & x1, const int & y1, const int & x2, const int & y2, const int & x3, const int & y3);
	void BFS(void);
	void nextMoveGhost(const int & PacmanX, const int & PacmanY);
	virtual ~CGhost();
};

