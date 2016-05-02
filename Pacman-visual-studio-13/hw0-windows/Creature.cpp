#include "Creature.h"

Creature::Creature()
{
}

Creature::Creature(const int & pX, const int & pY, const string & pNameOfCreature,const ColorNames & pValue, const bool & pAliveStatus, const int & pEyesDirection)
{
	this->m_n_xVertex = pX;
	this->m_n_yVertex = pY;
	this->m_s_nameofCreature = pNameOfCreature;
	this->m_e_c_color = pValue;
	this->m_b_alive = pAliveStatus;
	if (pEyesDirection >= 0 && pEyesDirection <= 3)
		this->m_n_eyesDirection = pEyesDirection;
	else
		this->m_n_eyesDirection = 0;
}

Creature::~Creature()
{
}

