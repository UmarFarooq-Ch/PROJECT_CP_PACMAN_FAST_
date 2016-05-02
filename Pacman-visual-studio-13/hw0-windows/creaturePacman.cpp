#include "creaturePacman.h"

creaturePacman::creaturePacman(const int & pX, const int & pY, const string & pNameOfCreature, const ColorNames & pValue, const bool & pAliveStatus, const int & pEyesDirection, const float & pValueRadian) : Creature(pX, pY, pNameOfCreature, pValue, pAliveStatus, pEyesDirection), m_n_move(false), m_n_radians(pValueRadian)
{
}

creaturePacman::~creaturePacman()
{
}

void creaturePacman::nextMove(void)
{
	int tempX = this->m_n_xVertex / 20;
	int tempY = this->m_n_yVertex / 20;
	int tempMidValueOftempX = (tempX - 1) * 19 + 10;	cout << "tempMidValueOftempX: " << tempMidValueOftempX << endl;
	int tempMidValueOftempY = (tempY - 1) * 19 + 10; tempMidValueOftempY = 720 - tempMidValueOftempY; cout << "tempMidValueOftempY" << tempMidValueOftempY << endl;
	//now first i will check where is the direction of mouth of pacman
	if (m_n_eyesDirection == LEFT_)
	{
		tempX = this->m_n_xVertex - 2;
		tempY = this->m_n_yVertex;
		int nextItem = Board::getBoardPart(tempX / 20, (720 - tempY) / 20);	//checking which item lies in tempX,tempY position
		cout << (tempX / 20) << endl;
		if (nextItem == 16) //&& (Board::getBoardPart((tempX / 20) - 1, (720 - tempY) / 20) == 16 && ((tempX / 20) * 19 + 15) < m_n_xVertex))	//if it is a food then change the x vertex and y vertex accordingly and increase the score
		{
			m_n_xVertex -= 5;
			if (getBoardPart(this->m_n_xVertex / 20, (720 - this->m_n_yVertex) / 20) == 16)
			{
				//score += 10;
				setBoardPart(this->m_n_xVertex / 20, ((720 - this->m_n_yVertex) / 20), 17);
			}
		}

		else if (nextItem == 17)
		{
			m_n_xVertex-=5;
		}

		else
		{
			m_n_xVertex += 10;
			m_n_move = false;
			cout << "Else executed" << endl;
		}
	}

	else if (m_n_eyesDirection == RIGHT_)
	{
		tempX = this->m_n_xVertex + 2;
		tempY = this->m_n_yVertex;
		int nextItem = Board::getBoardPart(tempX / 20, (720 - tempY) / 20);	//checking which item lies in tempX,tempY position
		if (nextItem == 16) //&& (Board::getBoardPart((tempX / 20) + 1, (720 - tempY) / 20) == 16 || ((tempX / 20) * 19 - 15) > m_n_xVertex))	//if it is a food then change the x vertex and y vertex accordingly and increase the score
		{
			m_n_xVertex += 5;
			if (getBoardPart(this->m_n_xVertex / 20, (720 - this->m_n_yVertex) / 20) == 16)
			{
				//score += 10;
				setBoardPart(this->m_n_xVertex / 20, ((720 - this->m_n_yVertex) / 20), 17);
			}
			//if (Board::getBoardPart((tempX / 20) + 1, (720 - tempY) / 20) != 16 && Board::getBoardPart((tempX / 20) + 1, (720 - tempY) / 20) != 17)
			//	move = false;
		}

		else if (nextItem == 17)
		{
			m_n_xVertex += 5;
		}
		else
		{
			m_n_move = false;
			m_n_xVertex -= 10;
			cout << "Else executed" << endl;
		}
	}
}
