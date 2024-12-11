/*
 * Scheduler.c
 *
 *  Created on: Dec 10, 2024
 *      Author: Ofhbr
 */
#include "Scheduler.h"

static uint32_t scheduledEvents;

uint32_t getScheduledEvents(void){
	return scheduledEvents;
}
void addSchedulerEvent(uint32_t fent){
	scheduledEvents |=  fent;
}
void removeSchedulerEvent(uint32_t fent){
	scheduledEvents &= ~ fent;
}
