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
	int m_n_directionPending;	//member_numeric
	bool m_b_reset;	//this bool is used to reset all creatures
	int time;
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
	inline bool getReset() { return m_b_reset; }
	inline void setReset(const bool & pB) { this->m_b_reset = pB; }
	inline void getPosition(int & pX, int & pY) const { pX = this->m_n_xVertex;pY = this->m_n_yVertex;return; }
	inline void setPosition(const int & pX, const int & pY) { this->m_n_xVertex = pX;this->m_n_yVertex = pY;return; }
	inline int getX(void) const { return this->m_n_xVertex; }
	inline int getY(void) const { return this->m_n_yVertex; }
	inline void setX(const int & pX) { this->m_n_xVertex = pX;return; }
	inline void setY(const int & pY) { this->m_n_yVertex = pY;return; }
	inline int getEyesDirection(void)const { return this->m_n_eyesDirection; }
	void setEyesDirection(const int & pEyesDirection);	
	inline int getPendingDirection(void) const { return this->m_n_directionPending; }
	inline ColorNames getColor(void) const { return this->m_e_c_color; }
	inline bool getAlive(void) const { return m_b_alive; }
	inline void setAlive(const bool & pB) { this->m_b_alive = pB; }
	inline void increaseTime(void) { ++time; }
	inline void setTimeZero(void) { time = 0; }
	inline int getTime(void) { return time; }
};

