#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>
#include "stm32l0xx_ll_tim.h"

/* timeValue_t represents nanoseconds
 * timePoint_t can be used for checkpoints*/
typedef uint64_t timeUnit_t;
typedef uint16_t timePoint_t;

typedef enum{
	TIM2_Valid = 0, /*!!*/
	TIM2_invalidHigh,
	TIM2_invalidLow,
	TIM2_initError
} TIM2_Validity;



#define TIM2_Deinit()		do{LL_TIM_DeInit(TIM2);__HAL_RCC_TIM2_CLK_DISABLE();}while(0)
#define TIM2_Enable()		LL_TIM_EnableCounter(TIM2)
#define TIM2_Disable()	LL_TIM_DisableCounter(TIM2)


/* Public function declarations */

/*ATTENTION:
 * returns 0 if ok
 * does not enable
 */
 
 
 /*
 * @param nanoseconds : number of nanoseconds of precision
 * found that System Clock is 32Mhz, so 31<nanoseconds<=2'047'968 (about 2ms)
 * max measurable diff: 2ms (max timeUnit) * 65535 ~ 130s;
 */

TIM2_Validity TIM2_Init(uint64_t nanoseconds);

/*Use of Delay invalids previous timePoints with respect to new ones*/
void TIM2_Delay(const timeUnit_t timeUnits);

static inline timePoint_t TIM2_getTime(void){
	return (timePoint_t)LL_TIM_GetCounter(TIM2);
}

//It's not possible to have a diff >= AutoReload  (max = 65535 time units!)

timeUnit_t TIM2_Diff(timePoint_t end, timePoint_t start);
#endif
