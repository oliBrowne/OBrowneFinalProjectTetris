/*
 * Game.c
 *
 *  Created on: Dec 3, 2024
 *      Author: Ofhbr
 */

#include "Game.h"

bool board[BoardWidth][BoardHeight] = {};


void board_init(void){
	int i = 0;
	while (i < BoardWidth){

		board[i][0] = Occupied;
		i++;
	}
}
struct currentBlock *currBlock;
void newCurrBlock(){
	currBlock->type = (BlockType)get_rand_num();
	currBlock->state = state1;
	switch(get_rand_num()){
		case line:{
			currBlock->BlockOne[1] = 5;
			currBlock->BlockOne[2] = 4;
			LCD_Draw_Box(110,100,20,LCD_COLOR_CYAN);
			currBlock->BlockTwo[1] = 5;
			currBlock->BlockTwo[2] = 3;
			LCD_Draw_Box(110,80,20,LCD_COLOR_CYAN);
			currBlock->BlockThree[1] = 5;
			currBlock->BlockThree[2] = 2;
			LCD_Draw_Box(110,60,20,LCD_COLOR_CYAN);
			currBlock->BlockFour[1] = 5;
			currBlock->BlockFour[2] = 1;
			LCD_Draw_Box(110,40,20,LCD_COLOR_CYAN);
			grid();
		}
			break;
		case Square:{
			currBlock->BlockOne[1] = 5;
			currBlock->BlockOne[2] = 0;
			LCD_Draw_Box(110,40,20,LCD_COLOR_RED);
			currBlock->BlockTwo[1] = 5;
			currBlock->BlockTwo[2] = 1;
			LCD_Draw_Box(110,60,20,LCD_COLOR_RED);
			currBlock->BlockThree[1] = 4;
			currBlock->BlockThree[2] = 0;
			LCD_Draw_Box(90,40,20,LCD_COLOR_RED);
			currBlock->BlockFour[1] = 4;
			currBlock->BlockFour[2] = 1;
			LCD_Draw_Box(90,60,20,LCD_COLOR_RED);
			grid();
			break;
		}
		case LeftZigZag:{
			currBlock->BlockOne[1] = 5;
			currBlock->BlockOne[2] = 0;
			LCD_Draw_Box(110,40,20,LCD_COLOR_MAGENTA);
			currBlock->BlockTwo[1] = 5;
			currBlock->BlockTwo[2] = 1;
			LCD_Draw_Box(110,60,20,LCD_COLOR_MAGENTA);
			currBlock->BlockThree[1] = 4;
			currBlock->BlockThree[2] = 0;
			LCD_Draw_Box(90,40,20,LCD_COLOR_MAGENTA);
			currBlock->BlockFour[1] = 4;
			currBlock->BlockFour[2] = 1;
			LCD_Draw_Box(90,60,20,LCD_COLOR_MAGENTA);
			grid();
			break;

		}
		case RightZigZag:{
			currBlock->BlockOne[1] = 5;
			currBlock->BlockOne[2] = 0;
			LCD_Draw_Box(110,40,20,LCD_COLOR_YELLOW);
			currBlock->BlockTwo[1] = 5;
			currBlock->BlockTwo[2] = 1;
			LCD_Draw_Box(110,60,20,LCD_COLOR_YELLOW);
			currBlock->BlockThree[1] = 4;
			currBlock->BlockThree[2] = 0;
			LCD_Draw_Box(90,40,20,LCD_COLOR_YELLOW);
			currBlock->BlockFour[1] = 4;
			currBlock->BlockFour[2] = 1;
			LCD_Draw_Box(90,60,20,LCD_COLOR_YELLOW);
			grid();
			break;
		}
		case RightL:{
			currBlock->BlockOne[1] = 5;
			currBlock->BlockOne[2] = 4;
			LCD_Draw_Box(130,80,20,LCD_COLOR_GREEN);
			currBlock->BlockTwo[1] = 5;
			currBlock->BlockTwo[2] = 3;
			LCD_Draw_Box(110,80,20,LCD_COLOR_GREEN);
			currBlock->BlockThree[1] = 5;
			currBlock->BlockThree[2] = 2;
			LCD_Draw_Box(110,60,20,LCD_COLOR_GREEN);
			currBlock->BlockFour[1] = 5;
			currBlock->BlockFour[2] = 1;
			LCD_Draw_Box(110,40,20,LCD_COLOR_GREEN);
			grid();
			break;
		}
		case LeftL:{
			currBlock->BlockOne[1] = 5;
			currBlock->BlockOne[2] = 4;
			LCD_Draw_Box(90,80,20,LCD_COLOR_BLUE);
			currBlock->BlockTwo[1] = 5;
			currBlock->BlockTwo[2] = 3;
			LCD_Draw_Box(110,80,20,LCD_COLOR_BLUE);
			currBlock->BlockThree[1] = 5;
			currBlock->BlockThree[2] = 2;
			LCD_Draw_Box(110,60,20,LCD_COLOR_BLUE);
			currBlock->BlockFour[1] = 5;
			currBlock->BlockFour[2] = 1;
			LCD_Draw_Box(110,40,20,LCD_COLOR_BLUE);
			grid();
			break;
		}
		case smollPP:{
			currBlock->BlockOne[1] = 5;
			currBlock->BlockOne[2] = 0;
			LCD_Draw_Box(110,40,20,LCD_COLOR_RED);
			currBlock->BlockTwo[1] = 5;
			currBlock->BlockTwo[2] = 1;
			LCD_Draw_Box(110,60,20,LCD_COLOR_RED);
			currBlock->BlockThree[1] = 6;
			currBlock->BlockThree[2] = 1;
			LCD_Draw_Box(130,60,20,LCD_COLOR_RED);
			currBlock->BlockFour[1] = 4;
			currBlock->BlockFour[2] = 1;
			LCD_Draw_Box(90,60,20,LCD_COLOR_RED);
			grid();
			break;
		}

	}
}

bool currBlock_verifyDown(void){
	int testVar[2];
	testVar[1] = currBlock->BlockOne[1];
	testVar[2] = currBlock->BlockOne[2] + 1;
	if(((board[testVar[1]][testVar[2]]) != (board[currBlock->BlockTwo[1]][currBlock->BlockTwo[2]])) & ((board[testVar[1]][testVar[2]]) != (board[currBlock->BlockThree[1]][currBlock->BlockThree[2]])) & ((board[testVar[1]][testVar[2]]) != (board[currBlock->BlockFour[1]][currBlock->BlockFour[2]]))){
		if((board[testVar[1]][testVar[2]]) != Free){
			return false;
		}
	}
	testVar[1] = currBlock->BlockTwo[1];
	testVar[2] = currBlock->BlockTwo[2] + 1;
	if(((board[testVar[1]][testVar[2]]) != (board[currBlock->BlockOne[1]][currBlock->BlockOne[2]])) & ((board[testVar[1]][testVar[2]] != board[currBlock->BlockThree[1]][currBlock->BlockThree[2]])) & ((board[testVar[1]][testVar[2]]) != (board[currBlock->BlockFour[1]][currBlock->BlockFour[2]]))){
		if((board[testVar[1]][testVar[2]]) != Free){
			return false;
		}
	}

	testVar[1] = currBlock->BlockThree[1];
	testVar[2] = currBlock->BlockThree[2] + 1;
	if(((board[testVar[1]][testVar[2]]) != (board[currBlock->BlockTwo[1]][currBlock->BlockTwo[2]])) & ((board[testVar[1]][testVar[2]]) != (board[currBlock->BlockOne[1]][currBlock->BlockOne[2]])) & ((board[testVar[1]][testVar[2]]) != (board[currBlock->BlockFour[1]][currBlock->BlockFour[2]]))){
		if((board[testVar[1]][testVar[2]]) != Free){
			return false;
		}
	}
	testVar[1] = currBlock->BlockFour[1];
	testVar[2] = currBlock->BlockFour[2] + 1;
	if(((board[testVar[1]][testVar[2]]) != (board[currBlock->BlockTwo[1]][currBlock->BlockTwo[2]])) & ((board[testVar[1]][testVar[2]]) != (board[currBlock->BlockThree[1]][currBlock->BlockThree[2]])) & ((board[testVar[1]][testVar[2]]) != (board[currBlock->BlockOne[1]][currBlock->BlockOne[2]]))){
		if((board[testVar[1]][testVar[2]]) != Free){
			return false;
		}
	}
	return true;
}
void currBlock_Down(void){
	if(currBlock_verifyDown()){
		int testVar[2];
		testVar[1] = currBlock->BlockOne[1];
		testVar[2] = currBlock->BlockOne[2] + 1;
		currBlock->BlockOne[1] = testVar[1];
		currBlock->BlockOne[2] = testVar[2];

		testVar[1] = currBlock->BlockTwo[1];
		testVar[2] = currBlock->BlockTwo[2] + 1;
		currBlock->BlockTwo[1] = testVar[1];
		currBlock->BlockTwo[2] = testVar[2];

		testVar[1] = currBlock->BlockThree[1];
		testVar[2] = currBlock->BlockThree[2] + 1;
		currBlock->BlockThree[1] = testVar[1];
		currBlock->BlockThree[2] = testVar[2];

		testVar[1] = currBlock->BlockFour[1];
		testVar[2] = currBlock->BlockFour[2] + 1;
		currBlock->BlockFour[1] = testVar[1];
		currBlock->BlockFour[2] = testVar[2];
	}

}
void currBlock_Rotate(void){
	if(currBlock_verifyRotate()){
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


bool currBlock_verifyRotate(void){
	int testVar[2];
	switch(currBlock->type){
	case line:{
		switch(currBlock->state){// one block doest move
		case state1:
			testVar[1] = currBlock->BlockOne[1] + 3;
			testVar[2] = currBlock->BlockOne[2] - 3;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockTwo[1] + 2;
			testVar[2] = currBlock->BlockTwo[2] - 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockThree[1] + 1;
			testVar[2] = currBlock->BlockThree[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state2:
			testVar[1] = currBlock->BlockOne[1] - 3;
			testVar[2] = currBlock->BlockOne[2] + 3;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockTwo[1] - 2;
			testVar[2] = currBlock->BlockTwo[2] + 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockThree[1] - 1;
			testVar[2] = currBlock->BlockThree[2] + 1;
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
		switch(currBlock->state){// only two rotations
		case state1:
			testVar[1] = currBlock->BlockOne[1];
			testVar[2] = currBlock->BlockOne[2] - 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockTwo[1] - 2;
			testVar[2] = currBlock->BlockTwo[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state2:
			testVar[1] = currBlock->BlockOne[1];
			testVar[2] = currBlock->BlockOne[2] + 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockTwo[1] + 2;
			testVar[2] = currBlock->BlockTwo[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
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
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockTwo[1];// top middle to bottom middle
			testVar[2] = currBlock->BlockTwo[2] - 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state2:
			testVar[1] = currBlock->BlockOne[1] + 2;// rightmost most block top to top left inverse
			testVar[2] = currBlock->BlockOne[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockTwo[1];// top middle to bottom middle inverse
			testVar[2] = currBlock->BlockTwo[2] + 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
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
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockTwo[1] + 1;// middle left to top middle
			testVar[2] = currBlock->BlockTwo[2] + 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockThree[1] + 2;// top left to top right
			testVar[2] = currBlock->BlockThree[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state2:
			testVar[1] = currBlock->BlockOne[1] - 1;//  mid bottom to mid left
			testVar[2] = currBlock->BlockOne[2] + 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockTwo[1] + 1;//  top middle to middle right
			testVar[2] = currBlock->BlockTwo[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockThree[1];//  top right to bottom right
			testVar[2] = currBlock->BlockThree[2] - 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state3:
			testVar[1] = currBlock->BlockOne[1] + 1;//  mid left to mid top
			testVar[2] = currBlock->BlockOne[2] + 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockTwo[1] - 1;//  middle right mid bottom
			testVar[2] = currBlock->BlockTwo[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockThree[1] - 2;//  bottom right to bottom left
			testVar[2] = currBlock->BlockThree[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state4:
			testVar[1] = currBlock->BlockOne[1] + 1;//  mid top to mid right
			testVar[2] = currBlock->BlockOne[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockTwo[1] - 1;//  middle right mid bottom
			testVar[2] = currBlock->BlockTwo[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockThree[1] - 2;//  bottom right to bottom left
			testVar[2] = currBlock->BlockThree[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
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
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockTwo[1] - 1;// middle right to bottom middle
			testVar[2] = currBlock->BlockTwo[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockThree[1];// top right to bottom right
			testVar[2] = currBlock->BlockThree[2] - 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state2:
			testVar[1] = currBlock->BlockOne[1] + 1;//   mid top to mid right
			testVar[2] = currBlock->BlockOne[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockTwo[1] - 1;//  bottom middle to middle left
			testVar[2] = currBlock->BlockTwo[2] + 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockThree[1] - 2;//  bottom right to bottom left
			testVar[2] = currBlock->BlockThree[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state3:
			testVar[1] = currBlock->BlockOne[1] - 1;//    mid right mid bottom
			testVar[2] = currBlock->BlockOne[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockTwo[1] + 1;//   middle left to middle top
			testVar[2] = currBlock->BlockTwo[2] + 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockThree[1];//   bottom left to top left
			testVar[2] = currBlock->BlockThree[2] + 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state4:
			testVar[1] = currBlock->BlockOne[1] - 1;//   mid bottom to mid left
			testVar[2] = currBlock->BlockOne[2] + 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockTwo[1] + 1;//    middle top to mid right
			testVar[2] = currBlock->BlockTwo[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockThree[1] + 2;//   top left to top right
			testVar[2] = currBlock->BlockThree[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		default:
			break;
		}
	}
	case smollPP:{
		switch(currBlock->state){// 4rotations only 3 blocks as center is centered
		case state1:
			testVar[1] = currBlock->BlockOne[1];//  bottom left to top left
			testVar[2] = currBlock->BlockOne[2] + 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockTwo[1] + 1;// middle left to top middle
			testVar[2] = currBlock->BlockTwo[2] + 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockThree[1] + 2;// top left to top right
			testVar[2] = currBlock->BlockThree[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state2:
			testVar[1] = currBlock->BlockOne[1] + 2;// top left to top right
			testVar[2] = currBlock->BlockOne[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockTwo[1] + 1;// middle top to  middle right
			testVar[2] = currBlock->BlockTwo[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockThree[1];// top right to bottom right
			testVar[2] = currBlock->BlockThree[2] - 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state3:
			testVar[1] = currBlock->BlockOne[1];//top right to bottom right
			testVar[2] = currBlock->BlockOne[2] - 2;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockTwo[1] - 1;// middle right to  middle bottom
			testVar[2] = currBlock->BlockTwo[2] - 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockThree[1] - 2;// bottom right to bottom left
			testVar[2] = currBlock->BlockThree[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			break;
		case state4:
			testVar[1] = currBlock->BlockOne[1] - 2;// bottom right to bottom left
			testVar[2] = currBlock->BlockOne[2];
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockTwo[1] - 1;// middle bottom to  middle left
			testVar[2] = currBlock->BlockTwo[2] + 1;
			if(board[testVar[1]][testVar[2]] != Free){
				return false;
			}
			testVar[1] = currBlock->BlockThree[1];// bottom left to top left
			testVar[2] = currBlock->BlockThree[2] + 2;
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
