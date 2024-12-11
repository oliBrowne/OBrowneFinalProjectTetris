/*
 * Timer_Driver.h
 *
 *  Created on: Oct 10, 2024
 *      Author: Ofhbr
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stm32f4xx_hal.h"
#include "Scheduler.h"
#include <stdbool.h>
#define GPTimer_MasterMode_offset 4
#define GPTimer_MasterMode_clear 7
typedef enum GPTimer_MasterMode {
	MM_Reset = 0,
	MM_Enable,
	MM_Update,
	MM_ComparePulse,
	MM_Compare1,
	MM_Compare2,
	MM_Compare3,
	MM_Compare4,
}GPTimer_MasterMode;

//clock division (TIMx_CR1)
#define GPTimer_ClockDivision_offset 8
#define GPTimer_ClockDivision_clear 3
typedef enum GPTimer_ClockDivision {
	CD_tCK_INT = 0,
	CD_tCK_INT2,
	CD_tCK_INT3,
	CD_RESERVED,
}GPTimer_ClockDivision;

#define GPTimer_CenterAlignedMode_offset 5
#define GPTimer_CenterAlignedMode_clear 3
typedef enum GPTimer_CenterAlignedMode {
	CMS_EdgeAlignedMode = 0,
	CMS_CenterAlignedMode1,
	CMS_CenterAlignedMode2,
	CMS_CenterAlignedMode3,
}GPTimer_CenterAlignedMode;

#define GPTimer_AutoReloadPreloadEnable_offset 7
#define GPTimer_AutoReloadPreloadEnable_clear 1
typedef enum GPTimer_AutoReloadPreloadEnable{
	ARPE_NonBuffered = 0,
	ARPE_Buffered,
}GPTimer_AutoReloadPreloadEnable;

#define GPTimer_Direction_offset 4
#define GPTimer_Direction_clear 1
typedef enum GPTimer_Direction{
	DIR_UpCount = 0,
	DIR_DownCount = 1,
}GPTimer_Direction;

//Update interrupt enable (TIMx_DIER)
#define GPTimer_UpdateInterruptEnable_offset 0
#define GPTimer_UpdateInterruptEnable_clear 1
typedef enum GPTimer_UpdateInterruptEnable{
	UIE_Disable = 0,
	UIE_Enable,
}GPTimer_UpdateInterruptEnable;

#define GPTimer_UpdateDisable_offset 1
#define GPTimer_UpdateDisable_clear 1
typedef enum GPTimer_UpdateDisable{
	UDIS_Enable = 0,
	UDIS_Disable,
}GPTimer_UpdateDisable;

#define GPTimer_OnePulseMode_offset 0
#define GPTimer_OnePulseMode_clear 1
typedef enum GPTimer_OnePulseMode{
	OPM_Disable = 0,
	OPM_Enable,
}GPTimer_OnePulseMode;

typedef struct {
	 uint32_t  Autoreload;
	 GPTimer_MasterMode  MasterMode;
	 GPTimer_ClockDivision ClockDivision;
	 uint32_t  Prescaler;
	 GPTimer_CenterAlignedMode CenterAlignedMode;
	 GPTimer_AutoReloadPreloadEnable  AutoReloadPreloadEnable;
	 GPTimer_Direction  Direction;
	 GPTimer_UpdateInterruptEnable   UpdateInterruptEnable;
	 GPTimer_UpdateDisable   UpdateDisable;
	 GPTimer_OnePulseMode  OnePulseMode;

}GPTimer_Config_t;


void timerInit(void);
void tim2Start(void);
void tim2Stop(void);
void TIM2_IRQHandler(void);

//void timerCLK(GPTIMR_RegDef_t *portptr, uint8_t clkENR);
//#define enabler 1
//#define disabler 0
//#define CEN_offset 0
//#define reseter 0
//void timerStrStp(GPTIMR_RegDef_t *portptr, uint8_t timerMode);
//uint32_t timerReturn(GPTIMR_RegDef_t *portptr);
//void timerIntrENR(GPTIMR_RegDef_t *portptr, uint8_t intrENR);
//uint32_t timerARV(GPTIMR_RegDef_t *portptr);
//void timer_Clear_Pending_TIM2(void);
//void timer_Clear_Pending_TIM5(void);
//void NVIC_EnableDisable_Timer(GPTIMR_RegDef_t *portptr, bool EnableDisable);
#endif
