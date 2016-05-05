#pragma once
#include "Board.h"
class CBlock// :public Board
{
protected:
	int m_n_xVertex;	//member_numeric_xVertex of Block
	int m_n_yVertex;	//member_numeric_yVertex of Block
	CBlock *__RIGHT, *__DOWN, *__LEFT, *__UP;
	bool maenCheckHoGyaHun;
	bool yahinPerHe;
	bool yahanSeAgeKuchNahi;
	CBlock *m_c_predecesor;
public:
	CBlock();
	void initializeNeighbours(CBlock & pR, CBlock &  pD, CBlock & pL, CBlock & pU);
	void setVertex(const int & pX, const int & pY);
	void reset(void);
	bool fire(const int & PX/*to be capture xVertex*/, const int & PY/*to be capture yVertex*/, CBlock & pPre, int & endStop);
	inline bool getMaenCheckHoGyaHun(void) const { return this->maenCheckHoGyaHun; }
	inline bool getYahanSeAgeKuchNahin(void) const { return this->yahanSeAgeKuchNahi; }
	inline void setYahanSeAgeKuchNahin(void) { this->yahanSeAgeKuchNahi = true; }
	inline void setPredecesorToNull(void) { this->m_c_predecesor = NULL; }
	inline CBlock * getPredecedor(void) { return this; }
	bool tempN(void) const;
	~CBlock();
};

