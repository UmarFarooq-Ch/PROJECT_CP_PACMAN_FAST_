#include "Block.h"
#include "creaturePacman.h"
#include <cstdlib>


void CBlock::initializeNeighbours(CBlock & pR, CBlock &  pD, CBlock & pL, CBlock & pU)
{
	__RIGHT = &pR;
	__DOWN = &pD;
	__LEFT = &pL;
	__UP = &pU;
}

CBlock::CBlock()
{
	this->m_n_xVertex = this->m_n_yVertex = -1;
	maenCheckHoGyaHun = yahinPerHe = yahanSeAgeKuchNahi = false;
}

void CBlock::setVertex(const int & pX, const int & pY)
{
	this->m_n_xVertex = pX;
	this->m_n_yVertex = pY;
}

void CBlock::reset(void)
{
	maenCheckHoGyaHun = false;
	yahinPerHe = false;
	yahanSeAgeKuchNahi = false;
	m_c_predecesor = NULL;
}

bool CBlock::fire(const int & PX, const int & PY, CBlock & pPre)
{
	if (m_c_predecesor == NULL)
	{
		m_c_predecesor = &pPre;
	}
	else if (m_c_predecesor != &pPre)	//Yani ager jis ne is fire ko call kiya he os se pehle koi call ker chuka he tu wo isko dobara call na krne de
		return false;

	if (maenCheckHoGyaHun == true)
	{
		//first check for yahan se age kuch nahin
		if (__RIGHT == NULL && __DOWN == NULL && __LEFT == NULL && m_c_predecesor == __UP)
			yahanSeAgeKuchNahi = true;
		else if (__RIGHT == NULL && __DOWN == NULL && __LEFT == m_c_predecesor && __UP == NULL)
			yahanSeAgeKuchNahi = true;
		else if (__RIGHT == NULL && __DOWN == m_c_predecesor && __LEFT == NULL && __UP == NULL)
			yahanSeAgeKuchNahi = true;
		else if (__RIGHT == m_c_predecesor && __DOWN == NULL && __LEFT == NULL && __UP == NULL)
			yahanSeAgeKuchNahi = true;



		if (__RIGHT != NULL && __RIGHT->yahanSeAgeKuchNahi == false && m_c_predecesor != __RIGHT)
			if (__RIGHT->fire(PX, PY, *this) == true)
				return true;
		if (__DOWN != NULL && __DOWN->yahanSeAgeKuchNahi == false && m_c_predecesor != __DOWN)
			if (__DOWN->fire(PX, PY, *this) == true)
				return true;
		if (__LEFT != NULL && __LEFT->yahanSeAgeKuchNahi == false && m_c_predecesor != __LEFT)
			if (__LEFT->fire(PX, PY, *this) == true)
				return true;
		if (__UP != NULL && __UP->yahanSeAgeKuchNahi == false && m_c_predecesor != __UP)
			if (__UP->fire(PX, PY, *this) == true)
				return true;
		return false;
	}
	else
	{
		maenCheckHoGyaHun = true;
		if (abs(PX - m_n_xVertex) <= 20 && abs(PY - m_n_yVertex) <= 20)
		{
			yahinPerHe = true;
			return true;
		}
		return false;
	}
}

bool CBlock::tempN(void) const
{
	if (__LEFT == NULL && __RIGHT == NULL && __DOWN == NULL && __UP == NULL)
		return true;
	return false;
}

CBlock::~CBlock()
{

}
