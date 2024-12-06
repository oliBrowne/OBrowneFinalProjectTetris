/*
 * Game.h
 *
 *  Created on: Dec 3, 2024
 *      Author: Ofhbr
 */
#include "stm32f4xx_hal.h"
#include "stdbool.h"
#ifndef INC_GAME_H_
#define INC_GAME_H_

#define BoardWidth 10
#define BoardHeight 21
#define Free 0
#define Occupied 1

typedef enum {
	line = 0,
	Square,
	LeftZigZag,
	RightZigZag,
	RightL,
	LeftL,
	smollPP
}BlockType;

typedef enum {
	state1 = 0,
	state2,
	state3,
	state4,
}BlockState;


struct currentBlock{// position 1 is x position 2 is y
	int BlockOne[2];
	int BlockTwo[2];
	int BlockThree[2];
	int BlockFour[2];
	BlockType type;
	BlockState state;
};
void board_init();
bool currBlock_verifyDown(struct currentBlock *currBlock);
void currBlock_Rotate(struct currentBlock *currBlock);
bool currBlock_verifyRotate(struct currentBlock currBlock);
#endif /* INC_GAME_H_ */
