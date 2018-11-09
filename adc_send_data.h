/*
 * adc_send_data.h
 *
 *  Created on: 13 квіт. 2018 р.
 *      Author: Mykhailo
 */

#ifndef MAIN_ADC_SEND_DATA_H_
#define MAIN_ADC_SEND_DATA_H_
#include "socket_set_get.h"
#include <driver/adc.h>

float get_voltage_from_adc_float(int val);
void adc_get_value(void);
void adc_see_values(void);


#endif /* MAIN_ADC_SEND_DATA_H_ */
