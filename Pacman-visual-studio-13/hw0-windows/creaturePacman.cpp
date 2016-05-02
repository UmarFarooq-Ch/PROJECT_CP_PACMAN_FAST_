#include "creaturePacman.h"

creaturePacman::creaturePacman(const int & pX, const int & pY, const string & pNameOfCreature, const ColorNames & pValue, const bool & pAliveStatus, const int & pEyesDirection, const float & pValueRadian) : Creature(pX, pY, pNameOfCreature, pValue, pAliveStatus, pEyesDirection), m_n_move(false), m_n_radians(pValueRadian), check(0)
{
}

creaturePacman::~creaturePacman()
{
}

void creaturePacman::nextMove(void)
{
	int tempX = this->m_n_xVertex / 20; //it gives -1 x block
	int tempY = this->m_n_yVertex / 20;	//it gives -1 y block from uper side
	int currentXVertex = (tempX ) * 20 + 10;
	int currentYVertex = (tempY ) * 20 + 10;
	//now first i will check where is the direction of mouth of pacman
	if (m_n_eyesDirection == LEFT_)
	{
		int nextMidValueOftempX = (tempX) * 20 - 10; cout << "Next MidValue : " << nextMidValueOftempX << endl;
		int sameMidValueOftempY = (tempY) * 20 + 10; cout << "Next Mid Value of Y: " << sameMidValueOftempY << endl;
		//now check which board part lies in tempX and tempY+1 /*yani same Y block*/
		int nextPart = Board::getBoardPart(tempX - 1, 35 - tempY);
		if (nextPart == 16 || nextPart == 17)	//if there is eatable or empty space then move the pacman
		{
			m_n_xVertex -= 5;
			check = 0;
		}
		else	//else move pacman only two times so that pacman reach to the mid point of that tile
		{
			if (check >= 2)
				m_n_move = false;
			++check;
			if (check < 2)
				m_n_xVertex -= 5;
		}
		Board::setBoardPart(tempX,35- tempY, 17); //set eatable to moveable empty space
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
