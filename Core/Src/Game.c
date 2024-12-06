/*
 * Game.c
 *
 *  Created on: Dec 3, 2024
 *      Author: Ofhbr
 */

#include "Game.h"

bool board[BoardWidth][BoardHeight] = {};


void board_init(){
	int i = 0;
	while (i < BoardWidth){

		board[i][0] = Occupied;
		i++;
	}
}
bool currBlock_verifyDown(struct currentBlock *currBlock){
	int testVar[2];
	testVar[1] = currBlock->BlockOne[1];
	testVar[2] = currBlock->BlockOne[2] - 1;
	if(board[testVar[1]][testVar[2]] != Free){
		return false;
	}
	testVar[1] = currBlock->BlockTwo[1];
	testVar[2] = currBlock->BlockTwo[2] - 1;
	if(board[testVar[1]][testVar[2]] != Free){
		return false;
	}
	testVar[1] = currBlock->BlockThree[1];
	testVar[2] = currBlock->BlockThree[2] - 1;
	if(board[testVar[1]][testVar[2]] != Free){
		return false;
	}
	testVar[1] = currBlock->BlockFour[1];
	testVar[2] = currBlock->BlockFour[2] - 1;
	if(board[testVar[1]][testVar[2]] != Free){
		return false;
		return true;
	}
}
void currBlock_Rotate(struct currentBlock *currBlock){
	if(currBlock_verifyRotate(*currBlock)){
		int testVar[2];
		switch(currBlock->type){
		case line:
			switch(currBlock->state){// one block doest move
			case state1:
				testVar[1] = currBlock->BlockOne[1] + 3;
				testVar[2] = currBlock->BlockOne[2] - 3;
				currBlock->BlockOne[1] = testVar[1];
				currBlock->BlockOne[2] = testVar[2];

				testVar[1] = currBlock->BlockTwo[1] + 2;
				testVar[2] = currBlock->BlockTwo[2] - 2;
				currBlock->BlockTwo[1] = testVar[1];
				currBlock->BlockTwo[2] = testVar[2];

				testVar[1] = currBlock->BlockThree[1] + 1;
				testVar[2] = currBlock->BlockThree[2] - 1;
				currBlock->BlockThree[1] = testVar[1];
				currBlock->BlockThree[2] = testVar[2];

				currBlock->state = state2;
				break;
			case state2:
				testVar[1] = currBlock->BlockOne[1] - 3;
				testVar[2] = currBlock->BlockOne[2] + 3;
				currBlock->BlockOne[1] = testVar[1];
				currBlock->BlockOne[2] = testVar[2];

				testVar[1] = currBlock->BlockTwo[1] - 2;
				testVar[2] = currBlock->BlockTwo[2] + 2;
				currBlock->BlockTwo[1] = testVar[1];
				currBlock->BlockTwo[2] = testVar[2];

				testVar[1] = currBlock->BlockThree[1] - 1;
				testVar[2] = currBlock->BlockThree[2] + 1;
				currBlock->BlockThree[1] = testVar[1];
				currBlock->BlockThree[2] = testVar[2];

				currBlock->state = state1;
				break;
			default:
				break;
			}

			case Square:{
				break;
			}
			case LeftZigZag:{
				switch(currBlock->state){// only two rotations
				case state1:
					testVar[1] = currBlock->BlockOne[1];
					testVar[2] = currBlock->BlockOne[2] - 2;
					currBlock->BlockOne[1] = testVar[1];
					currBlock->BlockOne[2] = testVar[2];

					testVar[1] = currBlock->BlockTwo[1] - 2;
					testVar[2] = currBlock->BlockTwo[2];
					currBlock->BlockTwo[1] = testVar[1];
					currBlock->BlockTwo[2] = testVar[2];

					currBlock->state = state2;
					break;
				case state2:
					testVar[1] = currBlock->BlockOne[1];
					testVar[2] = currBlock->BlockOne[2] + 2;
					currBlock->BlockOne[1] = testVar[1];
					currBlock->BlockOne[2] = testVar[2];

					testVar[1] = currBlock->BlockTwo[1] + 2;
					testVar[2] = currBlock->BlockTwo[2];
					currBlock->BlockTwo[1] = testVar[1];
					currBlock->BlockTwo[2] = testVar[2];

					currBlock->state = state1;
					break;
				default:
					break;
				}
			}
			case RightZigZag:{
				switch(currBlock->state){//only two rotations
				case state1:
					testVar[1] = currBlock->BlockOne[1] - 2;// rightmost most block top to top left
					testVar[2] = currBlock->BlockOne[2];
					currBlock->BlockOne[1] = testVar[1];
					currBlock->BlockOne[2] = testVar[2];

					testVar[1] = currBlock->BlockTwo[1];// top middle to bottom middle
					testVar[2] = currBlock->BlockTwo[2] - 2;
					currBlock->BlockTwo[1] = testVar[1];
					currBlock->BlockTwo[2] = testVar[2];

					currBlock->state = state2;
					break;
				case state2:
					testVar[1] = currBlock->BlockOne[1] + 2;// rightmost most block top to top left inverse
					testVar[2] = currBlock->BlockOne[2];
					currBlock->BlockOne[1] = testVar[1];
					currBlock->BlockOne[2] = testVar[2];

					testVar[1] = currBlock->BlockTwo[1];// top middle to bottom middle inverse
					testVar[2] = currBlock->BlockTwo[2] + 2;
					currBlock->BlockTwo[1] = testVar[1];
					currBlock->BlockTwo[2] = testVar[2];

					currBlock->state = state1;
					break;
				default:
					break;
				}
			}
			case RightL:{
				switch(currBlock->state){// 4 rotations
				case state1:
					testVar[1] = currBlock->BlockOne[1] - 1;//  mid right to mid bottom
					testVar[2] = currBlock->BlockOne[2] - 1;
					currBlock->BlockOne[1] = testVar[1];
					currBlock->BlockOne[2] = testVar[2];

					testVar[1] = currBlock->BlockTwo[1] + 1;// middle left to top middle
					testVar[2] = currBlock->BlockTwo[2] + 1;
					currBlock->BlockTwo[1] = testVar[1];
					currBlock->BlockTwo[2] = testVar[2];

					testVar[1] = currBlock->BlockThree[1] + 2;// top left to top right
					testVar[2] = currBlock->BlockThree[2];
					currBlock->BlockThree[1] = testVar[1];
					currBlock->BlockThree[2] = testVar[2];

					currBlock->state = state2;
					break;
				case state2:
					testVar[1] = currBlock->BlockOne[1] - 1;//  mid bottom to mid left
					testVar[2] = currBlock->BlockOne[2] + 1;
					currBlock->BlockOne[1] = testVar[1];
					currBlock->BlockOne[2] = testVar[2];

					testVar[1] = currBlock->BlockTwo[1] + 1;//  top middle to middle right
					testVar[2] = currBlock->BlockTwo[2] - 1;
					currBlock->BlockTwo[1] = testVar[1];
					currBlock->BlockTwo[2] = testVar[2];

					testVar[1] = currBlock->BlockThree[1];//  top right to bottom right
					testVar[2] = currBlock->BlockThree[2] - 2;
					currBlock->BlockThree[1] = testVar[1];
					currBlock->BlockThree[2] = testVar[2];

					currBlock->state = state3;
					break;
				case state3:
					testVar[1] = currBlock->BlockOne[1] + 1;//  mid left to mid top
					testVar[2] = currBlock->BlockOne[2] + 1;
					currBlock->BlockOne[1] = testVar[1];
					currBlock->BlockOne[2] = testVar[2];

					testVar[1] = currBlock->BlockTwo[1] - 1;//  middle right mid bottom
					testVar[2] = currBlock->BlockTwo[2] - 1;
					currBlock->BlockTwo[1] = testVar[1];
					currBlock->BlockTwo[2] = testVar[2];

					testVar[1] = currBlock->BlockThree[1] - 2;//  bottom right to bottom left
					testVar[2] = currBlock->BlockThree[2];
					currBlock->BlockThree[1] = testVar[1];
					currBlock->BlockThree[2] = testVar[2];

					currBlock->state = state4;
					break;
				case state4:
					testVar[1] = currBlock->BlockOne[1] + 1;//  mid top to mid right
					testVar[2] = currBlock->BlockOne[2] - 1;
					currBlock->BlockOne[1] = testVar[1];
					currBlock->BlockOne[2] = testVar[2];

					testVar[1] = currBlock->BlockTwo[1] - 1;//  middle right mid bottom
					testVar[2] = currBlock->BlockTwo[2] - 1;
					currBlock->BlockTwo[1] = testVar[1];
					currBlock->BlockTwo[2] = testVar[2];

					testVar[1] = currBlock->BlockThree[1] - 2;//  bottom right to bottom left
					testVar[2] = currBlock->BlockThree[2];
					currBlock->BlockThree[1] = testVar[1];
					currBlock->BlockThree[2] = testVar[2];

					currBlock->state = state1;// set state back to 1
					break;
				default:
					break;
				}
			}
			case LeftL:{
				switch(currBlock->state){// 4 rotations
				case state1:
					testVar[1] = currBlock->BlockOne[1] + 1;//  mid left to mid top
					testVar[2] = currBlock->BlockOne[2] + 1;
					currBlock->BlockOne[1] = testVar[1];
					currBlock->BlockOne[2] = testVar[2];

					testVar[1] = currBlock->BlockTwo[1] - 1;// middle right to bottom middle
					testVar[2] = currBlock->BlockTwo[2] - 1;
					currBlock->BlockTwo[1] = testVar[1];
					currBlock->BlockTwo[2] = testVar[2];

					testVar[1] = currBlock->BlockThree[1];// top right to bottom right
					testVar[2] = currBlock->BlockThree[2] - 2;
					currBlock->BlockThree[1] = testVar[1];
					currBlock->BlockThree[2] = testVar[2];

					currBlock->state = state2;
					break;
				case state2:
					testVar[1] = currBlock->BlockOne[1] + 1;//   mid top to mid right
					testVar[2] = currBlock->BlockOne[2] - 1;
					currBlock->BlockOne[1] = testVar[1];
					currBlock->BlockOne[2] = testVar[2];

					testVar[1] = currBlock->BlockTwo[1] - 1;//  bottom middle to middle left
					testVar[2] = currBlock->BlockTwo[2] + 1;
					currBlock->BlockTwo[1] = testVar[1];
					currBlock->BlockTwo[2] = testVar[2];

					testVar[1] = currBlock->BlockThree[1] - 2;//  bottom right to bottom left
					testVar[2] = currBlock->BlockThree[2];
					currBlock->BlockThree[1] = testVar[1];
					currBlock->BlockThree[2] = testVar[2];

					currBlock->state = state3;
					break;
				case state3:
					testVar[1] = currBlock->BlockOne[1] - 1;//    mid right mid bottom
					testVar[2] = currBlock->BlockOne[2] - 1;
					currBlock->BlockOne[1] = testVar[1];
					currBlock->BlockOne[2] = testVar[2];

					testVar[1] = currBlock->BlockTwo[1] + 1;//   middle left to middle top
					testVar[2] = currBlock->BlockTwo[2] + 1;
					currBlock->BlockTwo[1] = testVar[1];
					currBlock->BlockTwo[2] = testVar[2];

					testVar[1] = currBlock->BlockThree[1];//   bottom left to top left
					testVar[2] = currBlock->BlockThree[2] + 2;
					currBlock->BlockThree[1] = testVar[1];
					currBlock->BlockThree[2] = testVar[2];

					currBlock->state = state4;
					break;
				case state4:
					testVar[1] = currBlock->BlockOne[1] - 1;//   mid bottom to mid left
					testVar[2] = currBlock->BlockOne[2] + 1;
					currBlock->BlockOne[1] = testVar[1];
					currBlock->BlockOne[2] = testVar[2];

					testVar[1] = currBlock->BlockTwo[1] + 1;//    middle top to mid right
					testVar[2] = currBlock->BlockTwo[2] - 1;
					currBlock->BlockTwo[1] = testVar[1];
					currBlock->BlockTwo[2] = testVar[2];

					testVar[1] = currBlock->BlockThree[1] + 2;//   top left to top right
					testVar[2] = currBlock->BlockThree[2];
					currBlock->BlockThree[1] = testVar[1];
					currBlock->BlockThree[2] = testVar[2];

					currBlock->state = state1;
					break;
				default:
					break;
				}
			}
			break;
			case smollPP:{
				switch(currBlock->state){// 4rotations only 3 blocks as center is centered
				case state1:
					testVar[1] = currBlock->BlockOne[1];//  bottom left to top left
					testVar[2] = currBlock->BlockOne[2] + 2;
					currBlock->BlockOne[1] = testVar[1];
					currBlock->BlockOne[2] = testVar[2];

					testVar[1] = currBlock->BlockTwo[1] + 1;// middle left to top middle
					testVar[2] = currBlock->BlockTwo[2] + 1;
					currBlock->BlockTwo[1] = testVar[1];
					currBlock->BlockTwo[2] = testVar[2];

					testVar[1] = currBlock->BlockThree[1] + 2;// top left to top right
					testVar[2] = currBlock->BlockThree[2];
					currBlock->BlockThree[1] = testVar[1];
					currBlock->BlockThree[2] = testVar[2];

					currBlock->state = state2;
					break;
				case state2:
					testVar[1] = currBlock->BlockOne[1] + 2;// top left to top right
					testVar[2] = currBlock->BlockOne[2];
					currBlock->BlockOne[1] = testVar[1];
					currBlock->BlockOne[2] = testVar[2];

					testVar[1] = currBlock->BlockTwo[1] + 1;// middle top to  middle right
					testVar[2] = currBlock->BlockTwo[2] - 1;
					currBlock->BlockTwo[1] = testVar[1];
					currBlock->BlockTwo[2] = testVar[2];

					testVar[1] = currBlock->BlockThree[1];// top right to bottom right
					testVar[2] = currBlock->BlockThree[2] - 2;
					currBlock->BlockThree[1] = testVar[1];
					currBlock->BlockThree[2] = testVar[2];

					currBlock->state = state3;
					break;
				case state3:
					testVar[1] = currBlock->BlockOne[1];//top right to bottom right
					testVar[2] = currBlock->BlockOne[2] - 2;
					currBlock->BlockOne[1] = testVar[1];
					currBlock->BlockOne[2] = testVar[2];

					testVar[1] = currBlock->BlockTwo[1] - 1;// middle right to  middle bottom
					testVar[2] = currBlock->BlockTwo[2] - 1;
					currBlock->BlockTwo[1] = testVar[1];
					currBlock->BlockTwo[2] = testVar[2];

					testVar[1] = currBlock->BlockThree[1] - 2;// bottom right to bottom left
					testVar[2] = currBlock->BlockThree[2];
					currBlock->BlockThree[1] = testVar[1];
					currBlock->BlockThree[2] = testVar[2];

					currBlock->state = state4;
					break;
				case state4:
					testVar[1] = currBlock->BlockOne[1] - 2;// bottom right to bottom left
					testVar[2] = currBlock->BlockOne[2];
					currBlock->BlockOne[1] = testVar[1];
					currBlock->BlockOne[2] = testVar[2];

					testVar[1] = currBlock->BlockTwo[1] - 1;// middle bottom to  middle left
					testVar[2] = currBlock->BlockTwo[2] + 1;
					currBlock->BlockTwo[1] = testVar[1];
					currBlock->BlockTwo[2] = testVar[2];

					testVar[1] = currBlock->BlockThree[1];// bottom left to top left
					testVar[2] = currBlock->BlockThree[2] + 2;
					currBlock->BlockThree[1] = testVar[1];
					currBlock->BlockThree[2] = testVar[2];

					currBlock->state = state1;
					break;
				default:
					break;
				}
			}
		}
	}
}


bool currBlock_verifyRotate(struct currentBlock currBlock){
	int testVar[2];
	switch(currBlock.type){
	case line:{
		switch(currBlock.state){// one block doest move
		case state1:
			testVar[1] = currBlock.BlockOne[1] + 3;
			testVar[2] = currBlock.BlockOne[2] - 3;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockTwo[1] + 2;
			testVar[2] = currBlock.BlockTwo[2] - 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockThree[1] + 1;
			testVar[2] = currBlock.BlockThree[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state2:
			testVar[1] = currBlock.BlockOne[1] - 3;
			testVar[2] = currBlock.BlockOne[2] + 3;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockTwo[1] - 2;
			testVar[2] = currBlock.BlockTwo[2] + 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockThree[1] - 1;
			testVar[2] = currBlock.BlockThree[2] + 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		default:
			break;
		}
	}

	case Square:{
		//no work
		break;
	}
	break;
	case LeftZigZag:{
		switch(currBlock.state){// only two rotations
		case state1:
			testVar[1] = currBlock.BlockOne[1];
			testVar[2] = currBlock.BlockOne[2] - 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockTwo[1] - 2;
			testVar[2] = currBlock.BlockTwo[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state2:
			testVar[1] = currBlock.BlockOne[1];
			testVar[2] = currBlock.BlockOne[2] + 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockTwo[1] + 2;
			testVar[2] = currBlock.BlockTwo[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		default:
			break;
		}
	}
	case RightZigZag:{
		switch(currBlock.state){//only two rotations
		case state1:
			testVar[1] = currBlock.BlockOne[1] - 2;// rightmost most block top to top left
			testVar[2] = currBlock.BlockOne[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockTwo[1];// top middle to bottom middle
			testVar[2] = currBlock.BlockTwo[2] - 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state2:
			testVar[1] = currBlock.BlockOne[1] + 2;// rightmost most block top to top left inverse
			testVar[2] = currBlock.BlockOne[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockTwo[1];// top middle to bottom middle inverse
			testVar[2] = currBlock.BlockTwo[2] + 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		default:
			break;
		}
	}
	case RightL:{
		switch(currBlock.state){// 4 rotations
		case state1:
			testVar[1] = currBlock.BlockOne[1] - 1;//  mid right to mid bottom
			testVar[2] = currBlock.BlockOne[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockTwo[1] + 1;// middle left to top middle
			testVar[2] = currBlock.BlockTwo[2] + 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockThree[1] + 2;// top left to top right
			testVar[2] = currBlock.BlockThree[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state2:
			testVar[1] = currBlock.BlockOne[1] - 1;//  mid bottom to mid left
			testVar[2] = currBlock.BlockOne[2] + 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockTwo[1] + 1;//  top middle to middle right
			testVar[2] = currBlock.BlockTwo[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockThree[1];//  top right to bottom right
			testVar[2] = currBlock.BlockThree[2] - 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state3:
			testVar[1] = currBlock.BlockOne[1] + 1;//  mid left to mid top
			testVar[2] = currBlock.BlockOne[2] + 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockTwo[1] - 1;//  middle right mid bottom
			testVar[2] = currBlock.BlockTwo[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockThree[1] - 2;//  bottom right to bottom left
			testVar[2] = currBlock.BlockThree[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state4:
			testVar[1] = currBlock.BlockOne[1] + 1;//  mid top to mid right
			testVar[2] = currBlock.BlockOne[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockTwo[1] - 1;//  middle right mid bottom
			testVar[2] = currBlock.BlockTwo[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockThree[1] - 2;//  bottom right to bottom left
			testVar[2] = currBlock.BlockThree[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		default:
			break;
		}
	}
	case LeftL:{
		switch(currBlock.state){// 4 rotations
		case state1:
			testVar[1] = currBlock.BlockOne[1] + 1;//  mid left to mid top
			testVar[2] = currBlock.BlockOne[2] + 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockTwo[1] - 1;// middle right to bottom middle
			testVar[2] = currBlock.BlockTwo[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockThree[1];// top right to bottom right
			testVar[2] = currBlock.BlockThree[2] - 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state2:
			testVar[1] = currBlock.BlockOne[1] + 1;//   mid top to mid right
			testVar[2] = currBlock.BlockOne[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockTwo[1] - 1;//  bottom middle to middle left
			testVar[2] = currBlock.BlockTwo[2] + 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockThree[1] - 2;//  bottom right to bottom left
			testVar[2] = currBlock.BlockThree[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state3:
			testVar[1] = currBlock.BlockOne[1] - 1;//    mid right mid bottom
			testVar[2] = currBlock.BlockOne[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockTwo[1] + 1;//   middle left to middle top
			testVar[2] = currBlock.BlockTwo[2] + 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockThree[1];//   bottom left to top left
			testVar[2] = currBlock.BlockThree[2] + 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state4:
			testVar[1] = currBlock.BlockOne[1] - 1;//   mid bottom to mid left
			testVar[2] = currBlock.BlockOne[2] + 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockTwo[1] + 1;//    middle top to mid right
			testVar[2] = currBlock.BlockTwo[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockThree[1] + 2;//   top left to top right
			testVar[2] = currBlock.BlockThree[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		default:
			break;
		}
	}
	case smollPP:{
		switch(currBlock.state){// 4rotations only 3 blocks as center is centered
		case state1:
			testVar[1] = currBlock.BlockOne[1];//  bottom left to top left
			testVar[2] = currBlock.BlockOne[2] + 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockTwo[1] + 1;// middle left to top middle
			testVar[2] = currBlock.BlockTwo[2] + 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockThree[1] + 2;// top left to top right
			testVar[2] = currBlock.BlockThree[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state2:
			testVar[1] = currBlock.BlockOne[1] + 2;// top left to top right
			testVar[2] = currBlock.BlockOne[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockTwo[1] + 1;// middle top to  middle right
			testVar[2] = currBlock.BlockTwo[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockThree[1];// top right to bottom right
			testVar[2] = currBlock.BlockThree[2] - 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state3:
			testVar[1] = currBlock.BlockOne[1];//top right to bottom right
			testVar[2] = currBlock.BlockOne[2] - 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockTwo[1] - 1;// middle right to  middle bottom
			testVar[2] = currBlock.BlockTwo[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockThree[1] - 2;// bottom right to bottom left
			testVar[2] = currBlock.BlockThree[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state4:
			testVar[1] = currBlock.BlockOne[1] - 2;// bottom right to bottom left
			testVar[2] = currBlock.BlockOne[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockTwo[1] - 1;// middle bottom to  middle left
			testVar[2] = currBlock.BlockTwo[2] + 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock.BlockThree[1];// bottom left to top left
			testVar[2] = currBlock.BlockThree[2] + 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
		default:
			break;
		}
	}
	default:
		break;

	}
	return true;
}
