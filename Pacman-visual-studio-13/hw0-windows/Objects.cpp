#include "Objects.h"



CObjects::CObjects()
{
	for (int i = 0, y = 10; i < 36;++i, y += 20)
		for (int j = 0, x = 10; j < 28;x += 20, ++j)
		{
			blocks[i][j].setVertex(x, y);
			CBlock *temp = NULL;
			blocks[i][j].initializeNeighbours(*temp, *temp, *temp, *temp);
			blocks[i][j].setPredecesorToNull();
		}
	B = new Board *[6]; // create a new board object to use in the Display Function ...
	B[0] = new Board;

	B[1] = &PaCman;


	B[2] = new CGhost(260, 410, "BLINKY", RED, true, 0, 2, blocks, &PaCman, true);
	B[3] = new CGhost(260, 350, "INKY", LIGHT_SKY_BLUE, true, 0, 2, blocks, &PaCman, true);
	B[4] = new CGhost(220, 350, "PINKY", LIGHT_PINK, true, 0, 2, blocks, &PaCman);
	B[5] = new CGhost(300, 350, "CYLIDE", SANDY_BROWN, true, 0, 2, blocks, &PaCman);
	for (int i = 3; i <= 31; ++i)
		for (int j = 1; j <= 26; ++j)
		{
			int local = B[0]->getBoardPart(j, 35 - i);	//ye if check ker rha he ke ager wo koi chalne wali jaga he tu os ke neighbour save kere warna na kre

			if (local == 16 || local == 17 || local == 18)
			{
				CBlock *array[4];
				int localR = B[0]->getBoardPart(j + 1, 35 - i);
				//if (i == 3 && j == 1)
				//B[0]->setBoardPart(j + 1, 35 - i, 17);
				if (localR == 17 || localR == 16 || localR == 18)
					array[0] = &blocks[i][j + 1];
				else
					array[0] = NULL;
				int localD = B[0]->getBoardPart(j, 35 - i + 1);
				/*	if (i == 3 && j == 1)
				B[0]->setBoardPart(j, 35 - i + 1,17);
				*/	if (localD == 17 || localD == 16 || localD == 18)
					array[1] = &blocks[i - 1][j];
				else
					array[1] = NULL;
				int localL = B[0]->getBoardPart(j - 1, 35 - i);
				//if (i == 3 && j == 1)
				//	B[0]->setBoardPart(j - 1, 35 - i, 17);
				if (localL == 17 || localL == 16 || localL == 18)
					array[2] = &blocks[i][j - 1];
				else
					array[2] = NULL;
				int localU = B[0]->getBoardPart(j, 35 - i - 1);
				//if (i == 3 && j == 1)
				//	B[0]->setBoardPart(j, 35 - i - 1, 17);
				if (localU == 17 || localU == 16 || localU == 18)
					array[3] = &blocks[i + 1][j];
				else
					array[3] = NULL;
				blocks[i][j].initializeNeighbours(*array[0], *array[1], *array[2], *array[3]);
			}
		}
	//Manually Initializing some blocks
	CBlock *tempEmptyBlock = NULL;
	blocks[18][1].initializeNeighbours(blocks[18][2], *tempEmptyBlock, blocks[18][0], *tempEmptyBlock);
	blocks[18][0].initializeNeighbours(blocks[18][1], *tempEmptyBlock, blocks[18][27], *tempEmptyBlock);
	blocks[18][27].initializeNeighbours(blocks[18][0], *tempEmptyBlock, blocks[18][26], *tempEmptyBlock);
	blocks[18][26].initializeNeighbours(blocks[18][27], *tempEmptyBlock, blocks[18][25], *tempEmptyBlock);
	blocks[18][11].initializeNeighbours(blocks[18][12], *tempEmptyBlock, *tempEmptyBlock, *tempEmptyBlock);
	blocks[18][12].initializeNeighbours(blocks[18][13], *tempEmptyBlock, blocks[18][11], *tempEmptyBlock);
	blocks[18][13].initializeNeighbours(blocks[18][14], *tempEmptyBlock, blocks[18][12], blocks[19][13]);
	blocks[18][14].initializeNeighbours(blocks[18][15], *tempEmptyBlock, blocks[18][13], *tempEmptyBlock);
	blocks[18][15].initializeNeighbours(blocks[18][16], *tempEmptyBlock, blocks[18][14], *tempEmptyBlock);
	blocks[18][16].initializeNeighbours(*tempEmptyBlock, *tempEmptyBlock, blocks[18][15], *tempEmptyBlock);
	blocks[19][13].initializeNeighbours(*tempEmptyBlock, blocks[18][13], *tempEmptyBlock, blocks[20][13]);
	blocks[20][13].initializeNeighbours(*tempEmptyBlock, blocks[19][13], *tempEmptyBlock, blocks[21][13]);
	B[2]->setTargetBoxes(1, 4, 12, 3, 9, 8, 9, 18);
	B[3]->setTargetBoxes(12, 30, 1, 30, 3, 24, 12, 21);
	B[4]->setTargetBoxes(15, 30, 21, 24, 19, 18, 26, 24);
	B[5]->setTargetBoxes(26, 11, 26, 3, 15, 5, 15, 12);
}


CObjects::~CObjects()
{
}
