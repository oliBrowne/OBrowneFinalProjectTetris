/*
 * RNG_Driver.h
 *
 *  Created on: Dec 11, 2024
 *      Author: Ofhbr
 */

#ifndef SRC_RNG_DRIVER_H_
#define SRC_RNG_DRIVER_H_

#include "stm32f4xx_hal.h"
void RNG_init(void);
uint32_t get_rand_num(void);

#endif /* SRC_RNG_DRIVER_H_ */
