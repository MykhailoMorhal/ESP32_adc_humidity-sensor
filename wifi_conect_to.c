/*----------------------------------------------------------------------
                                Include
*----------------------------------------------------------------------*/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"


#include <stdio.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_vfs_fat.h"

#include "wifi_conect_to.h"

/*----------------------------------------------------------------------
                                Defines
*----------------------------------------------------------------------*/
#define DEFAULT_SSID "Alitec_2G"
#define DEFAULT_PWD "$schodydonieba300"

#if CONFIG_WIFI_ALL_CHANNEL_SCAN
#define DEFAULT_SCAN_METHOD WIFI_ALL_CHANNEL_SCAN
#elif CONFIG_WIFI_FAST_SCAN
#define DEFAULT_SCAN_METHOD WIFI_FAST_SCAN
#else
#define DEFAULT_SCAN_METHOD WIFI_FAST_SCAN
#endif /*CONFIG_SCAN_METHOD*/

#if CONFIG_WIFI_CONNECT_AP_BY_SIGNAL
#define DEFAULT_SORT_METHOD WIFI_CONNECT_AP_BY_SIGNAL
#elif CONFIG_WIFI_CONNECT_AP_BY_SECURITY
#define DEFAULT_SORT_METHOD WIFI_CONNECT_AP_BY_SECURITY
#else
#define DEFAULT_SORT_METHOD WIFI_CONNECT_AP_BY_SIGNAL
#endif /*CONFIG_SORT_METHOD*/

#if CONFIG_FAST_SCAN_THRESHOLD
#define DEFAULT_RSSI CONFIG_FAST_SCAN_MINIMUM_SIGNAL
#if CONFIG_EXAMPLE_OPEN
#define DEFAULT_AUTHMODE WIFI_AUTH_OPEN
#elif CONFIG_EXAMPLE_WEP
#define DEFAULT_AUTHMODE WIFI_AUTH_WEP
#elif CONFIG_EXAMPLE_WPA
#define DEFAULT_AUTHMODE WIFI_AUTH_WPA_PSK
#elif CONFIG_EXAMPLE_WPA2
#define DEFAULT_AUTHMODE WIFI_AUTH_WPA2_PSK
#else
#define DEFAULT_AUTHMODE WIFI_AUTH_OPEN
#endif
#else
#define DEFAULT_RSSI -127
#define DEFAULT_AUTHMODE WIFI_AUTH_OPEN
#endif /*CONFIG_FAST_SCAN_THRESHOLD*/

/*----------------------------------------------------------------------
                    		Staric val & Extern val
*----------------------------------------------------------------------*/
static const char *TAG = "scan";
EventGroupHandle_t tcp_event_group;


static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_CONNECTED:
    	printf("STA CONNECT\n");
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
    	ESP_LOGI(TAG, "got ip:%s\n",
		ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        break;
    case SYSTEM_EVENT_AP_STACONNECTED:
    	printf("AP_STACONNECTED\n");
    	ESP_LOGI(TAG, "station:"MACSTR" join,AID=%d\n",
		MAC2STR(event->event_info.sta_connected.mac),
		event->event_info.sta_connected.aid);
    	break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
    	ESP_LOGI(TAG, "station:"MACSTR"leave,AID=%d\n",
		MAC2STR(event->event_info.sta_disconnected.mac),
		event->event_info.sta_disconnected.aid);
    	break;
    default:
        break;
    }
    return ESP_OK;
}

void wifi_init_sta()
{
    tcp_event_group = xEventGroupCreate();

    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL) );


    wifi_init_config_t sta_cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_wifi_init(&sta_cfg));
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = DEFAULT_SSID,
            .password = DEFAULT_PWD
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    ESP_LOGI(TAG, "wifi_init_sta finished.");
    ESP_LOGI(TAG, "connect to ap SSID:%s password:%s \n",
	    DEFAULT_SSID,DEFAULT_PWD);
}

void wifi_init_softap()
{
    tcp_event_group = xEventGroupCreate();

    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));

    wifi_init_config_t ap_cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&ap_cfg));
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = DEFAULT_SSID,
            .ssid_len = 0,
            .max_connection=4,
            .password = DEFAULT_PWD,
            .authmode = WIFI_AUTH_OPEN
        },
    };


    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_softap finished.SSID:%s password:%s \n",
    	    DEFAULT_SSID, DEFAULT_PWD);
}

