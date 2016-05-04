#include "Ghost.h"



CGhost::CGhost(const int & pX, const int & pY, const string & pNameOfCreature, const ColorNames & pValue, const bool & pAliveStatus, const int & pEyesDirection, const int & pGhostMode) :Creature(pX, pY, pNameOfCreature, pValue, pAliveStatus, pEyesDirection), m_n_ghostMode(pGhostMode)
{
}

CGhost::~CGhost()
{
}
