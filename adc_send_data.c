/*
 * adc_send_data.c
 *
 *  Created on: 19 бер. 2018 р.
 *      Author: Mykhailo
 */


#include <driver/adc.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "sdkconfig.h"
#include <stdlib.h>
#include <string.h>
#include "adc_send_data.h"

static char tag_adc1[] = "adc";

char value_channel_0_char[10];
char value_channel_3_char[10];
char value_channel_6_char[10];
char value_channel_7_char[10];
char value_channel_4_char[10];//for check battery

//char value_channel_0_for_send[10];

//char value_channel_0_for_send[10];

float value_channel_4_check_battery;

float get_voltage_from_adc_float(int val)
{
	const float max_value_from_ADC = 4095;
	//const float max_value_from_ADC = 2047;
	const float max_value_in_voltage = 2;//in doc. is 2.2V but we have voltage in 3.0V from this

	return (val*max_value_in_voltage) / max_value_from_ADC;
}


void adc_get_value(void)
{
	ESP_LOGI(tag_adc1, ">> adc1");
	adc1_config_width(ADC_WIDTH_BIT_12);//param width_bit Bit capture width for ADC1
	adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_6);//gives full-scale voltage 2.2V
	adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_6);
	adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_6);
	adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_6);
	adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_6);
	//adc1_config_width(ADC_WIDTH_BIT_12);//param width_bit Bit capture width for ADC1

	while(1) {

		/*
		float value_channel_7 = get_voltage_from_adc_float(adc1_get_raw(ADC1_CHANNEL_7));
		sprintf (value_channel_7_char, "%1.3f",value_channel_7);
		printf("value_channel_7: ");
		printf("%s",value_channel_7_char);
		printf("\n");
*/


		float value_channel_0 = get_voltage_from_adc_float(adc1_get_raw(ADC1_CHANNEL_0));
		float value_channel_3 = get_voltage_from_adc_float(adc1_get_raw(ADC1_CHANNEL_3));
		float value_channel_6 = get_voltage_from_adc_float(adc1_get_raw(ADC1_CHANNEL_6));
		float value_channel_7 = get_voltage_from_adc_float(adc1_get_raw(ADC1_CHANNEL_7));

		value_channel_4_check_battery = get_voltage_from_adc_float(adc1_get_raw(ADC1_CHANNEL_4));// for check voltage of battery


		sprintf (value_channel_0_char, "%1.3f",value_channel_0);
		sprintf (value_channel_3_char, "%1.3f",value_channel_3);
		sprintf (value_channel_6_char, "%1.3f",value_channel_6);
		sprintf (value_channel_7_char, "%1.3f",value_channel_7);
		sprintf (value_channel_4_char, "%1.3f",value_channel_4_check_battery);

		printf("\n");
				printf("value_channel_0: ");
				printf("%s",value_channel_0_char);
				printf("\n");
				printf("value_channel_3: ");
				printf("%s",value_channel_3_char);
				printf("\n");
				printf("value_channel_6: ");
				printf("%s",value_channel_6_char);
				printf("\n");
				printf("value_channel_7: ");
				printf("%s",value_channel_7_char);
				printf("\n");
				printf("Staus baterry: %s",value_channel_4_char);
				printf("\n");

		vTaskDelay(2000/portTICK_PERIOD_MS);
	}
	vTaskDelete(NULL);
}

void adc_see_values(void){

	while(1){

		printf("\n");
		printf("value_channel_0: ");
		printf("%s",value_channel_0_char);
		printf("\n");
		printf("value_channel_3: ");
		printf("%s",value_channel_3_char);
		printf("\n");
		printf("value_channel_6: ");
		printf("%s",value_channel_6_char);
		printf("\n");
		printf("value_channel_7: ");
		printf("%s",value_channel_7_char);
		printf("\n");
		vTaskDelay(2000/portTICK_PERIOD_MS);
	}
}


