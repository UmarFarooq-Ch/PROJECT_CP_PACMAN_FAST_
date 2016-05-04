#pragma once
#include "Creature.h"
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
public:
	CGhost(const int & pX, const int & pY, const string & pNameOfCreature, const ColorNames & pValue, const bool & pAliveStatus = true, const int & pEyesDirection = NILL_, const int & pGhostMode = NILL_);
	virtual ~CGhost();
};

