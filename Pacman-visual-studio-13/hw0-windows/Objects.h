#pragma once
#include "Board.h"
#include "creaturePacman.h"
#include "Ghost.h"
#include "Block.h"
#include <iostream>
using namespace std;

class CObjects
{
protected:



public:
	CBlock blocks[36][28];
	Board **B;
	creaturePacman PaCman;
	CObjects();
	virtual ~CObjects();
};

