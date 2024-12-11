/*
 * Timer.c
 *
 *  Created on: Dec 10, 2024
 *      Author: Ofhbr
 */


/*
 * Timer_Driver.c
 *
 *  Created on: Oct 17, 2024
 *      Author: Ofhbr
 */


#include "TIMER.H"
TIM_HandleTypeDef timer = {0};


void timerInit(){
	//Clock Division
	//frequency 6.25 * 1000000; tim 2
	timer.Instance = TIM2;
	timer.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	timer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	timer.Init.Prescaler = 65331;
	timer.Init.CounterMode = TIM_COUNTERMODE_UP;
	timer.Init.Period = 286;
	HAL_TIM_Base_Init(&timer);
	__HAL_TIM_URS_ENABLE(&timer);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}
void tim2Start(){
	__HAL_TIM_ENABLE_IT( &timer,TIM_IT_UPDATE);
	HAL_TIM_Base_Start_IT(&timer);
	__HAL_TIM_CLEAR_IT(&timer,TIM_IT_UPDATE);
}
void tim2Stop(){
	__HAL_TIM_ENABLE_IT( &timer,TIM_IT_UPDATE);
	HAL_TIM_Base_Stop_IT(&timer);
	__HAL_TIM_CLEAR_IT(&timer,TIM_IT_UPDATE);
}
void TIM2_IRQHandler(){
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	__HAL_TIM_CLEAR_IT(&timer,TIM_IT_UPDATE);
	// move down code
	addSchedulerEvent(BlockDown);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}
//void timerCLK(GPTIMR_RegDef_t *portptr, uint8_t clkENR){
//	if (clkENR) {
//	        // Enable the clock for the specified timer
//	        if (portptr == (GPTIMR_RegDef_t *)TIM2_BASE_ADDR) {
//	            TimeCLK_Enable(TIM2_OFFSET);
//	        }else if (portptr == (GPTIMR_RegDef_t *)TIM5_BASE_ADDR) {
//	            TimeCLK_Enable(TIM5_OFFSET);
//	        }
//	    } else {
//	        // Disable the clock for the specified timer
//	        if (portptr == (GPTIMR_RegDef_t *)TIM2_BASE_ADDR) {
//	            TimeCLK_Disable(TIM2_OFFSET);
//	        }else if (portptr == (GPTIMR_RegDef_t *)TIM5_BASE_ADDR) {
//	            TimeCLK_Disable(TIM5_OFFSET);
//	        }
//	    }
//}
//void timerStrStp(GPTIMR_RegDef_t *portptr, uint8_t timerMode){
//	//timerMode = 0 - disable
//	//timerMode = 1 - enable
//	//timerMode = 2 - reset
//	if (timerMode == enabler) {
//		        // Enable
//			portptr->TIMx_CR1 |= (enabler << CEN_offset );
//		    }
//	else if(timerMode == disabler){
//		        // Disable
//		    portptr->TIMx_CR1 &= ~(enabler << CEN_offset);
//		    }
//				//Reset
//	else{
//		    	portptr->TIMx_CNT = reseter;//reset the CNT register
//		    }
//
//}
//uint32_t timerReturn(GPTIMR_RegDef_t *portptr){
//	 return portptr->TIMx_CNT;//returns CNT
//}
//void timerIntrENR(GPTIMR_RegDef_t *portptr, uint8_t intrENR){
//	if (intrENR) {
//	        // Enable
//	        portptr->TIMx_DIER |= (1 << 0);
//	        NVIC_EnableDisable_Timer(portptr,intrENR);
//	    } else {
//	        // Disable
//	        portptr->TIMx_DIER &= ~(1 << 0);
//	        NVIC_EnableDisable_Timer(portptr,intrENR);
//	    }
//
//}
//uint32_t timerARV(GPTIMR_RegDef_t *portptr){
//	return portptr->TIMx_ARR;//returns ARR
//}
//void timer_Clear_Pending_TIM2(){
//	TIM2->TIMx_SR &= ~(1 << UpdateInterruptFlag);
//}
//void timer_Clear_Pending_TIM5(){
//	TIM5->TIMx_SR &= ~(1 << UpdateInterruptFlag);
//}
//void NVIC_EnableDisable_Timer(GPTIMR_RegDef_t *portptr, bool EnableDisable){
//	if(EnableDisable){
//			if(portptr == TIM2){
//				IRQ_Enable(TIM2_IRQ);
//			}
//			if(portptr == TIM5){
//				IRQ_Enable(TIM5_IRQ);
//			}
//		}
//		else{
//			if(portptr == TIM2){
//				IRQ_Disable(TIM2_IRQ);
//			}
//			if(portptr == TIM5){
//				IRQ_Disable(TIM5_IRQ);
//			}
//		}
//}
