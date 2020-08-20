/*----------------------------------------------------------------------
                                Include
*----------------------------------------------------------------------*/

#include <driver/adc.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "sdkconfig.h"
#include <stdlib.h>
#include <string.h>
#include "adc_send_data.h"

/*----------------------------------------------------------------------
                                Defines
*----------------------------------------------------------------------*/
#define LOG_ADC                                 "ADC"

/*----------------------------------------------------------------------
                    		Staric val & Extern val
*----------------------------------------------------------------------*/
char value_channel_0_char[VALUE_CHANNEL_SIZE];
char value_channel_3_char[VALUE_CHANNEL_SIZE];
char value_channel_6_char[VALUE_CHANNEL_SIZE];
char value_channel_7_char[VALUE_CHANNEL_SIZE];
char value_channel_4_char[VALUE_CHANNEL_SIZE];
float value_channel_4_check_battery;

static float get_voltage_from_adc_float(int val)
{
	const float max_value_from_ADC = 4095;
	const float max_value_in_voltage = 2;						//in doc. is 2.2V but we have voltage in 3.0V from this
	return (val*max_value_in_voltage) / max_value_from_ADC;
}


void adc_get_value(void)
{
	ESP_LOGI(LOG_ADC, ">> adc1");
	adc1_config_width(ADC_WIDTH_BIT_12);						//param width_bit Bit capture width for ADC1
	adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_6);	//gives full-scale voltage 2.2V
	adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_6);
	adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_6);
	adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_6);
	adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_6);

	while(1) 
	{
		value_channel_4_check_battery = get_voltage_from_adc_float(adc1_get_raw(ADC1_CHANNEL_4));	// for check voltage of battery

		sprintf (value_channel_0_char, "%1.3f",get_voltage_from_adc_float(adc1_get_raw(ADC1_CHANNEL_0)));
		sprintf (value_channel_3_char, "%1.3f",get_voltage_from_adc_float(adc1_get_raw(ADC1_CHANNEL_3)));
		sprintf (value_channel_6_char, "%1.3f",get_voltage_from_adc_float(adc1_get_raw(ADC1_CHANNEL_6)));
		sprintf (value_channel_7_char, "%1.3f",get_voltage_from_adc_float(adc1_get_raw(ADC1_CHANNEL_7)));
		sprintf (value_channel_4_char, "%1.3f",value_channel_4_check_battery);	
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


