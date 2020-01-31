#include <stdint.h>

#define DHT11_GPIO		GPIOC
#define DHT11_GPION		GPIO_PIN_12


typedef enum{
	DHT11_Error = 0,
	DHT11_Ok
} DHT11_Status_t;

void DHT11_Init();
/*DHT11 doesn't have decimal values, but our code still uses 16 bits, because probably it's compatible with DHT22*/
DHT11_Status_t getTemperatureAndHumidity(uint16_t *temperature, uint16_t *humidity);
