#include <stdint.h>
#include "stm32l0xx.h"
#include "stm32l0xx_hal_rcc.h"
#include "stm32l0xx_ll_tim.h"
#include "tim2.h"

static inline uint64_t roundDiv(uint64_t op1, uint64_t op2){
	op1 <<= 1;
	op1 /= op2;
	return ( (op1>>1) + (op1 & 1) );	
}


static LL_TIM_InitTypeDef __TIM2_Init_Structure;

/* Public function definitions */
TIM2_Validity TIM2_Init(uint64_t nanoseconds){
	uint32_t sysFreq = HAL_RCC_GetPCLK1Freq();
	uint64_t prescalerValue  = roundDiv(sysFreq * nanoseconds, 1000000000);
	//stm32l0x3's TIM2 should work with just 16 bits
	//rounded division
	if(prescalerValue & ~((uint64_t)0xFFFF))
		return TIM2_invalidHigh;
	if(!prescalerValue)
		return TIM2_invalidLow;
	__TIM2_Init_Structure.Prescaler = prescalerValue & 0xFFFF; 
	__TIM2_Init_Structure.CounterMode = LL_TIM_COUNTERMODE_UP;
	__TIM2_Init_Structure.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
	__TIM2_Init_Structure.Autoreload = 0xFFFF;
	__HAL_RCC_TIM2_CLK_ENABLE();
	if(!LL_TIM_Init(TIM2, &__TIM2_Init_Structure))
		return TIM2_initError;
	return TIM2_Valid;

}

void TIM2_Delay(const timeUnit_t timeUnits)
{
	uint32_t loops, offset, arr =__TIM2_Init_Structure.Autoreload,i;
	uint32_t val=0, val2=0; //very important cast to uint32_t
	loops = timeUnits/arr;
	offset = timeUnits % arr;
	LL_TIM_SetCounter(TIM2, 0);
	LL_TIM_EnableCounter(TIM2);
	for(i=0;i<loops; (val2 >= val) ? 0 : i++){
		val = val2;
		val2 = LL_TIM_GetCounter(TIM2);
	}
	while(offset < LL_TIM_GetCounter(TIM2));	
}

timeUnit_t TIM2_Diff(timePoint_t val1, timePoint_t val2){
	return (timeUnit_t) ((val1 >= val2) ? (val1 - val2) : (val1 + __TIM2_Init_Structure.Autoreload - val2));
}

