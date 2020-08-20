#ifndef MAIN_ADC_SEND_DATA_H_
#define MAIN_ADC_SEND_DATA_H_

/*----------------------------------------------------------------------
                                Include
*----------------------------------------------------------------------*/
#include "socket_set_get.h"
#include <driver/adc.h>

#define VALUE_CHANNEL_SIZE                      10u
/*----------------------------------------------------------------------
                                Functions
*----------------------------------------------------------------------*/

/**
 * @brief Get signal from ADC
 */
void adc_get_value(void);

/**
 * @brief Print signal value from ADC
 */
void adc_see_values(void);

#endif /* MAIN_ADC_SEND_DATA_H_ */
