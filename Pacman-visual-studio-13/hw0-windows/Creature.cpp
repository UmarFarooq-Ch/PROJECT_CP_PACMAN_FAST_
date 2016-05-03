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
	this->m_n_directionPending = NILL_;
	if (pEyesDirection >= 0 && pEyesDirection <= 3)
		this->m_n_eyesDirection = pEyesDirection;
	else
		this->m_n_eyesDirection = 0;
}

Creature::~Creature()
{
}

void Creature::setEyesDirection(const int & pEyesDirection)
{
	int tempX = this->m_n_xVertex / 20;
	int tempY = this->m_n_yVertex / 20;
	switch (pEyesDirection)
	{
	case LEFT_:	// for LEFT_ direction
		if (this->m_n_eyesDirection != pEyesDirection)	//yani jo eyes ki direction currently os ko new direction mile jab tab ye ho
		{
			short local_variable = Board::getBoardPart(tempX - 1, 35 - tempY);
			//Firstly check that pacman should lies on modulus 10 == 0 position not on modulus 20 == 0, yani box ke darmiyan khara hoa ho and there is no wall on left side				
			if (this->m_n_xVertex % 20 == 10 && this->m_n_yVertex % 20 == 10 && (local_variable == 16 || local_variable == 17 || local_variable == 18))
			{
				//if condition is true then it means pacman lies in middle of tile and it can change its direction
				this->m_n_eyesDirection = pEyesDirection;	//changing its eyes direction
				this->setRadian(6.0);
				this->setMove(true);
				m_n_directionPending = NILL_;
				glutPostRedisplay();
			}
			else	//else wait for rasta where there is an open end on LEFT_ hand side
			{
				m_n_directionPending = LEFT_;
			}
		}
		else
		{
			m_n_eyesDirection = pEyesDirection;
			this->setMove(true);
			glutPostRedisplay();
		}
		break;
	case RIGHT_:
		if (this->m_n_eyesDirection != pEyesDirection)	//yani jo eyes ki direction currently os ko new direction mile jab tab ye ho
		{
			int local_variable = Board::getBoardPart(tempX + 1, 35 - tempY);
			//Firstly check that pacman should lies on modulus 10 == 0 position not on modulus 20 == 0, yani box ke darmiyan khara hoa ho and there is no wall on left side				
			if (this->m_n_xVertex % 20 == 10 && this->m_n_yVertex % 20 == 10 && (local_variable == 16 || local_variable == 17 || local_variable == 18))
			{
				//if condition is true then it means pacman lies in middle of tile and it can change its direction
				this->m_n_eyesDirection = pEyesDirection;	//changing its eyes direction
				this->setRadian(-1.2);
				this->setMove(true);
				m_n_directionPending = NILL_;
				glutPostRedisplay();
			}
			else	//else wait for rasta where there is an open end on LEFT_ hand side
			{
				m_n_directionPending = RIGHT_;
			}
		}
		else
		{
			m_n_eyesDirection = pEyesDirection;
			this->setMove(true);
			glutPostRedisplay();
		}
		break;
	case UP_:
		if (this->m_n_eyesDirection != pEyesDirection)	//yani jo eyes ki direction currently os ko new direction mile jab tab ye ho
		{
			int local_variable = Board::getBoardPart(tempX, 35 - tempY - 1);
			//Firstly check that pacman should lies on modulus 10 == 0 position not on modulus 20 == 0, yani box ke darmiyan khara hoa ho and there is no wall on left side				
			if (this->m_n_xVertex % 20 == 10 && this->m_n_yVertex % 20 == 10 && (local_variable == 16 || local_variable == 17 || local_variable == 18))
			{
				//if condition is true then it means pacman lies in middle of tile and it can change its direction
				this->m_n_eyesDirection = pEyesDirection;	//changing its eyes direction
				this->setRadian(-3.0);					this->setMove(true);
				m_n_directionPending = NILL_;
				glutPostRedisplay();
			}
			else	//else wait for rasta where there is an open end on LEFT_ hand side
			{
				m_n_directionPending = UP_;
			}
		}
		else
		{
			m_n_eyesDirection = pEyesDirection;
			this->setMove(true);
			glutPostRedisplay();
		}
		break;
	case DOWN_:
		if (this->m_n_eyesDirection != pEyesDirection)	//yani jo eyes ki direction currently os ko new direction mile jab tab ye ho
		{
			short local_variable = Board::getBoardPart(tempX, 35 - tempY + 1);
			//Firstly check that pacman should lies on modulus 10 == 0 position not on modulus 20 == 0, yani box ke darmiyan khara hoa ho and there is no wall on left side				
			if (this->m_n_xVertex % 20 == 10 && this->m_n_yVertex % 20 == 10 && (local_variable == 16 || local_variable == 17 || local_variable == 18))
			{
				//if condition is true then it means pacman lies in middle of tile and it can change its direction
				this->m_n_eyesDirection = pEyesDirection;	//changing its eyes direction
				this->setRadian(1.5);
				this->setMove(true);
				m_n_directionPending = NILL_;
				glutPostRedisplay();
			}
			else	//else wait for rasta where there is an open end on LEFT_ hand side
			{
				m_n_directionPending = DOWN_;
			}
		}
		else
		{
			m_n_eyesDirection = pEyesDirection;
			this->setMove(true);
			glutPostRedisplay();
		}
		break;
	}


	return;
}

