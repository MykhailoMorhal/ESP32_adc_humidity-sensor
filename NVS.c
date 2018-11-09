#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "nvs_flash.h"
#include "NVS.h"

void flash_memory_ini(void)
{
	 esp_err_t ret = nvs_flash_init();// записуЇ дан≥ з банку пам€т≥ esp,€кщо нема в≥льного м≥сц€ то йде
	    if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
	        ESP_ERROR_CHECK(nvs_flash_erase());
	        ret = nvs_flash_init();
	    }
	    ESP_ERROR_CHECK( ret );
}




