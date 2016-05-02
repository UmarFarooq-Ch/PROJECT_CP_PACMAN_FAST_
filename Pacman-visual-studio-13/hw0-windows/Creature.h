#pragma once
#include "Board.h"


class Creature : public Board// Abstract class for creature
{
protected:
	int m_n_xVertex;	//member_numeric
	int m_n_yVertex;	//member_numeric
	string m_s_nameofCreature;	//member_string
	ColorNames m_e_c_color;	//member_enum_composition
	bool m_b_alive;	//member_bool
	enum eyesDirection
	{
		NILL_,	//Creature is looking to user
		RIGHT_,	//Creature is looking right
		DOWN_,	//Creatre is looking down
		LEFT_,	//Creature is looking left
		UP_,	//Creature is looking up
	};
	int m_n_eyesDirection; //member_numeric ///0 for front, 1 for right, 2 for down, 3 for left, 4 for up	
public:
	Creature();
	Creature(const int & pX, const int & pY, const string & pNameOfCreature, const ColorNames & pValue, const bool & pAliveStatus = true, const int & pEyesDirection = NILL_);
	virtual ~Creature();
	inline void getPosition(int & pX, int & pY) const { pX = this->m_n_xVertex;pY = this->m_n_yVertex;return; }
	inline void setPosition(const int & pX, const int & pY) { this->m_n_xVertex = pX;this->m_n_yVertex = pY;return; }
	inline int getX(void) const { return this->m_n_xVertex; }
	inline int getY(void) const { return this->m_n_yVertex; }
	inline void setX(const int & pX) { this->m_n_xVertex = pX;return; }
	inline void setY(const int & pY) { this->m_n_yVertex = pY;return; }
	inline int getEyesDirection(void)const { return this->m_n_eyesDirection; }
	inline void setEyesDirection(const int & pEyesDirection)
	{ 
		int tempX = this->m_n_xVertex / 20;
		int tempY = this->m_n_yVertex / 20;
		switch (pEyesDirection)
		{
		case 4:
			tempX = this->m_n_xVertex / 20;
			tempY = (this->m_n_yVertex) / 20 + 2;
			cout << this->m_n_yVertex / 20 << endl << endl << tempY << endl;
			if (Board::getBoardPart(tempX,36- tempY) == 16 || Board::getBoardPart(tempX,36- tempY) == 17)
			{
				Board::setBoardPart(tempX, tempY, 17);
				this->m_n_eyesDirection = pEyesDirection;
				cout << "b:" << Board::getBoardPart(tempX, tempY) << endl;
			}
			break;
		case 1:
		case 2:
		case 3:
			m_n_eyesDirection = pEyesDirection;
		}

		
		return; 
	}

};

