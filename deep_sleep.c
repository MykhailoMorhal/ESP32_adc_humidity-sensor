/*----------------------------------------------------------------------
                                Include
*----------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "esp_log.h"
#include "esp32/ulp.h"
#include "driver/touch_pad.h"
#include "driver/adc.h"
#include "driver/rtc_io.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/sens_reg.h"
#include "soc/rtc.h"
#include "deep_sleep.h"

/*----------------------------------------------------------------------
                    		Staric val & Extern val
*----------------------------------------------------------------------*/
static RTC_DATA_ATTR struct timeval sleep_enter_time;


void deep_sleep_ini(void)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    int sleep_time_ms = (now.tv_sec - sleep_enter_time.tv_sec) * 1000 + (now.tv_usec - sleep_enter_time.tv_usec) / 1000;

    switch (esp_sleep_get_wakeup_cause()) {
        case ESP_SLEEP_WAKEUP_TIMER: {
            printf("Wake up from timer. Time spent in deep sleep: %dms\n", sleep_time_ms);
            break;
        }

        case ESP_SLEEP_WAKEUP_UNDEFINED:
        default:
            printf("Not a deep sleep reset\n");
    }


    vTaskDelay(1000 / portTICK_PERIOD_MS);

    const int wakeup_time_sec = 20;// how long deep sleep must be
    printf("Enabling timer wakeup, %ds\n", wakeup_time_sec);
    esp_sleep_enable_timer_wakeup(wakeup_time_sec * 1000000);
    gettimeofday(&sleep_enter_time, NULL);

}

void deep_sleep_start(void)
{
	vTaskDelay(3000 / portTICK_PERIOD_MS);
	printf("Entering deep sleep\n");
	esp_deep_sleep_start();
}


