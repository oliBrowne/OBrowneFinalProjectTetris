/*
 * RNG_Driver.c
 *
 *  Created on: Dec 11, 2024
 *      Author: Ofhbr
 */
#include "RNG_Driver.h"
static RNG_HandleTypeDef hRNG;

void RNG_init(void){

	hRNG.Instance = RNG;
	if(HAL_RNG_Init(&hRNG) != HAL_OK){
			while(1){
			}
		}
}
uint32_t get_rand_num(void){
	RNG_init();
	if(HAL_RNG_Init(&hRNG)!= HAL_OK){
			while(1){
			}
		}
	uint32_t num = 0;
	HAL_RNG_GenerateRandomNumber(&hRNG,&num);
	num = num % 7;
	return num;

}

