#ifndef MAIN_SCAN_H_
#define MAIN_SCAN_H_

/*----------------------------------------------------------------------
                                Include
*----------------------------------------------------------------------*/
#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <nvs_flash.h>
#include <freertos/task.h>
#include <driver/gpio.h>

#include "wifi_conect_to.h"
#include "socket_set_get.h"
#include "adc_send_data.h"
#include "deep_sleep.h"
#include "NVS.h"
#include "gpio_on_off.h"

/*----------------------------------------------------------------------
                                Defines
*----------------------------------------------------------------------*/
#define     MIN_LEVEL_VOLTAGE_BATTERY           1.6f

/*----------------------------------------------------------------------
                    Staric val & Extern val & function
*----------------------------------------------------------------------*/
extern float value_channel_4_check_battery;				/* adc gpio32 */
extern _Bool status_send_loop; 							/* on/off deep sleep */

#endif /* MAIN_SCAN_H_ */
