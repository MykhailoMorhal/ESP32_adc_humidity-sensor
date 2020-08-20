/*----------------------------------------------------------------------
                                Include
*----------------------------------------------------------------------*/

#include "main.h"

/**
 * @brief Set ESP in deep sleep mode
 * @tparam parms - empty pointer
 */
void task_deep_sleep(void *parms)
{
	while(1){
		deep_sleep_ini();
		if(status_send_loop == 1){
			deep_sleep_start();
		}
	}

	vTaskDelete(NULL);
}

/**
 * @brief Init tcp client
 * @tparam parms - empty pointer
 */
void task_tcp_client_ini(void *parms)
{

	create_tcp_client();

	vTaskDelete(NULL);
}

/**
 * @brief Init adc 
 * @tparam parms - empty pointer
 */
void task_adc_ini(void *parms)
{
	while(1){
		adc_get_value();
	}

	vTaskDelete(NULL);
}

/**
 * @brief Show status ESP battery 
 * @tparam parms - empty pointer
 */
void task_status_battery_ini(void *parms)//min voltage for esp32 is 2.4V
{
	while(1) 																		// show voltage status of battery
	{
		if(value_channel_4_check_battery < MIN_LEVEL_VOLTAGE_BATTERY)
		{ 
			gpio19_show_low_battery();
		}
		else 
		{
			gpio19_show_status_ESP();
		}
	}

	vTaskDelete(NULL);
}

/**
 * @brief Main Loop
 */
void app_main()
{
	flash_memory_ini(); 															// Initialize NVS
	xTaskCreate(&task_deep_sleep, "myTask_1", 2048, 0, 4, 0);						//deep sleep at 20sec


	gpio25_ini_amplifier_lv1_lv2();													// turn on amplifier 1
	gpio33_ini_amplifier_lv3_lv4();													// turn on amplifier 2

	xTaskCreate(&task_status_battery_ini, "myTask_status_battery", 2048, 0, 1, 0);	// status battery

	wifi_init_sta();
	xTaskCreate(&task_adc_ini, "myTask_ADC_int", 2048, 0, 2, 0);					// get value from adc
	xTaskCreate(&task_tcp_client_ini, "myTask_2", 4096, 0, 1, 0);					// send data from esp to server
}
