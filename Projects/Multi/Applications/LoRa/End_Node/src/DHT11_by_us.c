#include <stdint.h>
#include "tim2.h"
#include "hw_conf.h"
#include "stm32l0xx_hal_gpio.h"
#include "DHT11_by_us.h"



// I decided really randomly to put data signal for our sensor on PC12 (Morpho CN7-3)
// but of course it will be a definition, in order to simplify his changing.
// But no one would change it, because otherwise I will call the police.



#define Phase1				GPIO_MODE_OUTPUT_PP
#define Phase2				GPIO_MODE_INPUT

#define levelHigh			GPIO_PIN_SET
#define levelLow				GPIO_PIN_RESET


static GPIO_InitTypeDef __DHT_GPIO_Init_Structure;


static inline void __setMode(uint16_t mode){
	__DHT_GPIO_Init_Structure.Mode = mode;
	HAL_GPIO_DeInit(DHT11_GPIO, DHT11_GPION);
	HAL_GPIO_Init(DHT11_GPIO,  &__DHT_GPIO_Init_Structure);
}

static inline GPIO_PinState __getValue(){
		return HAL_GPIO_ReadPin(DHT11_GPIO, DHT11_GPION);
}
static inline void __writeValue(GPIO_PinState state){
	HAL_GPIO_WritePin(DHT11_GPIO, DHT11_GPION, state);
}

static inline void _askForData(){
	__writeValue(levelLow);
	//Should be 18000us (but this is working)
	TIM2_Delay(72000);
}

static inline DHT11_Status_t _waitForPreparing(){
	timePoint_t beginTime, nowTime;
	timeUnit_t diff;
	beginTime= TIM2_getTime();
	/*waiting for at most 100us for pulling up*/
	do {
		nowTime= TIM2_getTime();
		diff= TIM2_Diff(nowTime, beginTime);
	}while(( diff < 100) && (__getValue() == levelLow));
	if (diff >= 100)
		return DHT11_Error;
	/*if it keeps up for more than 100us it's not working*/
	beginTime= TIM2_getTime();
	do {
		nowTime= TIM2_getTime();
		diff= TIM2_Diff(nowTime, beginTime);
	}while(( diff < 100) && (__getValue() == levelHigh));
	if (diff >= 100)
		return DHT11_Error;
	return DHT11_Ok;
}

static inline DHT11_Status_t _addBit(uint8_t *string){
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
	timePoint_t beginTime, nowTime;
	timeUnit_t diff;
	/*bit preamble, should be up to 50us*/
	beginTime= TIM2_getTime();
	do {
		nowTime= TIM2_getTime();
		diff= TIM2_Diff(nowTime, beginTime);
	}while(( diff < 100) && (__getValue() == levelLow));
	if (diff >= 100)
		return DHT11_Error;
	/*reading actual time, with a timeout of 120us*/
	beginTime= TIM2_getTime();
	do {
		nowTime= TIM2_getTime();
		diff= TIM2_Diff(nowTime, beginTime);
	}while(( diff < 120) && (__getValue() == levelHigh));
	if (diff >= 120)
		return DHT11_Error;	
	(*string)<<=1;
	/*not sure about this treshold, see https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf */
	/*uptime <40 us => last bit was 0, otherwise it was 1*/
	if(TIM2_Diff(nowTime, beginTime)>40)
		(*string) |= 1;	
	return DHT11_Ok;
#pragma GCC diagnostic pop
}
static void __restore(){
	__setMode(Phase1);
	__writeValue(levelHigh);
	TIM2_Disable();
	__enable_irq();
}
DHT11_Status_t  getTemperatureAndHumidity(uint16_t *temperature, uint16_t *humidity){

	uint8_t RH1, RH2, RH3, RH4;
	uint8_t checksum;
	uint8_t count;
	/*Init*/
	__disable_irq();
	TIM2_Enable();
	/*Send Request*/
	__setMode(Phase1);
	_askForData();
	/*Get Data*/
	__setMode(Phase2);
	if(!_waitForPreparing())
		goto badEnd;
	for(count=0;count<8;count++)
		if(!_addBit(&RH1))
			goto badEnd;
	for(count=0;count<8;count++)
		if(!_addBit(&RH2))
			goto badEnd;
	for(count=0;count<8;count++)
		if(!_addBit(&RH3))
			goto badEnd;
	for(count=0;count<8;count++)
		if(!_addBit(&RH4))
			goto badEnd;
	for(count=0; count<8; count++)
		if(!_addBit(&checksum))
			goto badEnd;
	if (checksum != (uint8_t)(RH1+RH2+RH3+RH4))
		goto badEnd;
	*humidity = RH1<<8;
	*humidity |= RH2;
	*temperature = RH3<<8;
	*temperature |= RH4;
	TIM2_Delay(50);
	__restore();
	return DHT11_Ok;
badEnd:
	__restore();
	return DHT11_Error;
}

void DHT11_Init(){
/* Compile-time check */
if(DHT11_GPIO == GPIOC)
	__HAL_RCC_GPIOC_CLK_ENABLE();
else{
	/*fill with code where needed*/
}
/*Initialize TIM2 with 1us as timeUnit*/
	TIM2_Init(1000);

	__DHT_GPIO_Init_Structure.Pin = DHT11_GPION;
//	A pullup resistor exists in the device
//	Unsafe to keep in input mode with floating wires
	__DHT_GPIO_Init_Structure.Pull = GPIO_NOPULL;
	__DHT_GPIO_Init_Structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	/*as documentation says we should wait at least one second before sending commands*/
	TIM2_Delay(1200000);
}

/*It's 4:25 Am and I'm going to sleep, maybe one day this will be completed...*/
