#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "nrf_gpio.h"
//#include "idelay.h"
#include <stdlib.h>

#define LED_0	30
#define LED_1	25
#define LED_2	28

extern uint32_t SystemMicroSecNopCnt;

int main(void)
{

	// flash LED_0 and LED_1 alternately
  nrf_gpio_cfg_output(LED_0);
  nrf_gpio_cfg_output(LED_1);
  nrf_gpio_cfg_output(LED_2);
  
  while(true)
  {
    nrf_gpio_pin_clear(LED_0);
    nrf_gpio_pin_set(LED_2);
    nrf_delay_us(1000000);
    nrf_gpio_pin_clear(LED_2);
    nrf_gpio_pin_set(LED_0);
    nrf_delay_us(1000000);
  }
}
