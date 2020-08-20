/*----------------------------------------------------------------------
                                Include
*----------------------------------------------------------------------*/

#include "driver/rtc_io.h"
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include "gpio_on_off.h"

void gpio33_ini_amplifier_lv3_lv4(void)
{

	gpio_set_direction(GPIO_NUM_33,GPIO_MODE_OUTPUT);
	gpio_set_level(GPIO_NUM_33,1);
	printf("amplifier_lv3_lv4 ON\n");
}

void gpio25_ini_amplifier_lv1_lv2(void)
{

	gpio_set_direction(GPIO_NUM_25,GPIO_MODE_OUTPUT);
	gpio_set_level(GPIO_NUM_25,1);
	printf("amplifier_lv1_lv2 ON\n");
}

void gpio19_show_status_ESP(void)
{
	gpio_set_direction(GPIO_NUM_19,GPIO_MODE_OUTPUT);
	gpio_set_level(GPIO_NUM_19,1);
}


void gpio19_show_low_battery(void)
{
	gpio_set_direction(GPIO_NUM_19,GPIO_MODE_OUTPUT);
	gpio_set_level(GPIO_NUM_19,0);
	vTaskDelay(1000 / portTICK_RATE_MS);
	gpio_set_level(GPIO_NUM_19,1);
	vTaskDelay(1000 / portTICK_RATE_MS);
	printf("Buttery is LOW\n");
}





