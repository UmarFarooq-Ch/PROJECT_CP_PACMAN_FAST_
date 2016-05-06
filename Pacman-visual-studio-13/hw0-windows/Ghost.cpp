#include "Ghost.h"



CGhost::CGhost(const int & pX, const int & pY, const string & pNameOfCreature, const ColorNames & pValue, const bool & pAliveStatus, const int & pEyesDirection, const int & pGhostMode, CBlock array[][28], creaturePacman * ptrPACMAN, const bool & pCanMove) :Creature(pX, pY, pNameOfCreature, pValue, pAliveStatus, pEyesDirection), m_n_ghostMode(pGhostMode), fixXVertex(pX), fixYVertex(pY), canMove(pCanMove)
{
	for (int i =0; i < 36;++i)
		for (int j = 0;j < 28;++j)
		{
			blocks_array[i][j] = & array[i][j];
		}
	time = 0;
	temp = false;
	m_b_alive = true;
	index = 0;
	PACMAN = ptrPACMAN;
}

inline void CGhost::setTargetBoxes(const int & x0, const int & y0, const int & x1, const int & y1, const int & x2, const int & y2, const int & x3, const int & y3)
{
	this->m_n_targetBoxes[0] = x0;
	this->m_n_targetBoxes[1] = y0;
	this->m_n_targetBoxes[2] = x1;
	this->m_n_targetBoxes[3] = y1;
	this->m_n_targetBoxes[4] = x2;
	this->m_n_targetBoxes[5] = y2;
	this->m_n_targetBoxes[6] = x3;
	this->m_n_targetBoxes[7] = y3;
}

bool CGhost::BFS(void)
{
	//Cell of Ghost is
	int xtileOfGhost = m_n_xVertex / 20 + 1;
	int ytileOfGhost = m_n_yVertex / 20 + 1;
	//int rightSide = Board::getBoardPart(xtileOfGhost + 1, 35 - ytileOfGhost);
	////Board::setBoardPart(xtileOfGhost + 1, 35 - ytileOfGhost,6);
	//int downSide = Board::getBoardPart(xtileOfGhost, 35 - ytileOfGhost + 1);
	////Board::setBoardPart(xtileOfGhost, 35 - ytileOfGhost + 1,6);
	//int leftSide = Board::getBoardPart(xtileOfGhost - 1, 35 - ytileOfGhost);
	////Board::setBoardPart(xtileOfGhost - 1, 35 - ytileOfGhost,6);
	//int upSide = Board::getBoardPart(xtileOfGhost, 35 - ytileOfGhost - 1);
	//Board::setBoardPart(xtileOfGhost, 35 - ytileOfGhost - 1, 6);
	//glutPostRedisplay();
	bool rightSide = (*blocks_array[ytileOfGhost][xtileOfGhost + 1]).tempN();
	bool leftSide = (*blocks_array[ytileOfGhost][xtileOfGhost - 1]).tempN();
	bool downSide = (*blocks_array[ytileOfGhost - 1][xtileOfGhost]).tempN();
	bool upSide = (*blocks_array[ytileOfGhost + 1][xtileOfGhost]).tempN();
	int endStop = 0;
	// This function will chose 2 points and find the shortest distance betwwen them
	while (true)
	{
		//Calling fire function of all neighbours again and again unless fire return true
		// Starting from right side

		//for right
		if (rightSide == false)//16 || rightSide == 17 || rightSide == 18)
		{
			if (blocks_array[ytileOfGhost][xtileOfGhost + 1] != NULL)
			{
				if ((*blocks_array[ytileOfGhost][xtileOfGhost + 1]).fire(currentTargentxVertex, currentTargetyVertex, *blocks_array[ytileOfGhost][xtileOfGhost], endStop) == true)
				{
					nextMove = 1;
					for (int i = 0; i < 36; ++i)
						for (int j = 0; j < 28;++j)
							(*blocks_array[i][j]).reset();
					break;
				}
			}
		}

		//for Down
		if (downSide == false)//16 || downSide == 17 || downSide == 18)
		{
			if (blocks_array[ytileOfGhost - 1][xtileOfGhost] != NULL)
			{
				if ((*blocks_array[ytileOfGhost - 1][xtileOfGhost]).fire(currentTargentxVertex, currentTargetyVertex, *blocks_array[ytileOfGhost][xtileOfGhost], endStop) == true)
				{
					nextMove = 2;
					for (int i = 0; i < 36; ++i)
						for (int j = 0; j < 28;++j)
							(*blocks_array[i][j]).reset();
					break;
				}
			}
		}

		//for left
		if (leftSide == false)//16 || leftSide == 17 || leftSide == 18)
		{
			if (blocks_array[ytileOfGhost][xtileOfGhost - 1] != NULL)
			{
				if ((*blocks_array[ytileOfGhost][xtileOfGhost - 1]).fire(currentTargentxVertex, currentTargetyVertex, *blocks_array[ytileOfGhost][xtileOfGhost], endStop) == true)
				{
					nextMove = 3;
					for (int i = 0; i < 36; ++i)
						for (int j = 0; j < 28;++j)
							(*blocks_array[i][j]).reset();
					break;
				}
			}
		}

		//for up
		if (upSide == false)//16 || upSide == 17 || upSide == 18)
		{
			if (blocks_array[ytileOfGhost + 1][xtileOfGhost] != NULL)
			{
				if ((*blocks_array[ytileOfGhost + 1][xtileOfGhost]).fire(currentTargentxVertex, currentTargetyVertex, *blocks_array[ytileOfGhost][xtileOfGhost], endStop) == true)
				{
					nextMove = 4;
					for (int i = 0; i < 36; ++i)
						for (int j = 0; j < 28;++j)
							(*blocks_array[i][j]).reset();
					break;
				}
			}
		}
	}

	if (endStop == 1 && m_n_ghostMode == SCATTER)
	{
		endStop = 0;
		currentTargentxVertex = m_n_targetBoxes[index] * 20;
		currentTargetyVertex = m_n_targetBoxes[index + 1] * 20;
		index += 2;
		if (index + 1 == 9)
			index = 0;
	}
	return false;
}

void CGhost::nextMoveGhost()
{
	if (m_b_alive == false)
	{
		return;
	}

	if (!canMove)
		return;

	if (m_n_ghostMode == CHASE)
	{
		currentTargentxVertex = PACMAN->getX();
		currentTargetyVertex = PACMAN->getY();
	}
	if (m_n_ghostMode == SCATTER)
	{
		currentTargentxVertex = m_n_targetBoxes[index] * 20;
		currentTargetyVertex = m_n_targetBoxes[index + 1] * 20;
	}
	//this->currentTargentxVertex = PacmanX;
	//this->currentTargetyVertex = PacmanY;
	if ((m_n_xVertex % 20 == 10 && m_n_yVertex % 20 == 10) || temp == false)
	{
		BFS();
		temp = true;
	}
	if (nextMove == RIGHT_)
	{
		m_n_xVertex += 5;
	}
	else if (nextMove == DOWN_)
	{
		m_n_yVertex -= 5;
	}
	else if (nextMove == LEFT_)
	{
		m_n_xVertex -= 5;
	}
	else if (nextMove == UP_)
	{
		m_n_yVertex += 5;
	}
	if (abs(m_n_xVertex + 20  - PACMAN->getX()) <= 20 && abs(m_n_yVertex + 20 - PACMAN->getY()) <= 20)
	{
		PACMAN->decreasePacmanLifes();
		if (PACMAN->getPacmanLifes() > 0)
		{
			m_b_reset = true;
			for (int i = 0; i < 36;++i)
				for (int j = 0;j < 28;++j)
					(*blocks_array[i][j]).reset();
		}
		else
			m_b_alive = false;
	}
}

CGhost::~CGhost()
{
}
