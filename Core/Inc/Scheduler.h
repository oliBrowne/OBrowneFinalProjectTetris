/*
 * Scheduler.h
 *
 *  Created on: Dec 10, 2024
 *      Author: Ofhbr
 */
#include <stdint.h>

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#define BlockDown (1 << 0)
#define BlockRotate 	(1 << 1)
#define EndScreen 	(1 << 2)
#define StartScreen (1 << 3)
#define GameScreen (1 << 4)

uint32_t getScheduledEvents(void);
void addSchedulerEvent(uint32_t fent );
void removeSchedulerEvent(uint32_t fent );

#endif
