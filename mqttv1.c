/* MQTT (over TCP) Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"

//First we need to create the TAG 
static const char *TAG = "MQTT_EXAMPLE"; // To identify the message into the log 

static void log_error_if_nonzero(const char *message, int error_code){

    if(error_code != 0){
        ESP_LOGE(TAG, "Last error %s: 0x%x", message, error_code);
    }
}

/*
 * @brief Event handler registered to receive MQTT events
 *
 *  This function is called by the MQTT client event loop.
 *
 * @param handler_args user data registered to the event.
 * @param base Event base for the handler(always MQTT Base in this example).
 * @param event_id The id for the received event.
 * @param event_data The data for the event, esp_mqtt_event_handle_t.
 */
static void mqtt_event_handler(void *handler_args, esp_event_base_t base ,int32_t event_id, void *event_data ){

 //Check the logs 
 ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%" PRIi32 "" , base , event_id);

 //Init the event Handler , init the client , set the message 
 esp_mqtt_event_handle_t event = event_data;
 //Enter into the second element into the structure 
 esp_mqtt_client_handle_t client = event->client;
 //Message ID
 int msg_id;
 //Flag to indicate when it's connected or not
 bool MqttConnected = false;

 switch((esp_mqtt_event_id_t)event_id){

    //Check if it is connected
    case MQTT_EVENT_CONNECTED:
       ESP_LOGI(TAG,"MQTT EVENT_CONNECTED");
       msg_id = esp_mqtt_client_publish(client,"/topic/qos1","data_3",0,1,0);
       ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
       
       msg_id = esp_mqtt_client_subscribe(client, "/topic/qos0", 0);
       ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

       msg_id = esp_mqtt_client_subscribe(client, "/topic/qos1", 1);
       ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
       
       msg_id = esp_mqtt_client_unsubscribe(client, "/topic/qos1");
       ESP_LOGI(TAG, "sent unsubscribe successful, msg_id=%d", msg_id);
       MqttConnected = true;
       break;  
    //Check if it is disconnected 
    case MQTT_EVENT_DISCONNECTED:
       ESP_LOGI(TAG,"MQTT EVENT_DISCONNECTED");
       break;
    
    //Check if it is susbcribe
    case MQTT_EVENT_SUBSCRIBED:
       ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
       if(MqttConnected == true){
         ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, data_len=%d", event->data_len);
         ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, topic=%p", event->topic);
       }
    case MQTT_EVENT_UNSUBSCRIBED:
       ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
       break;
    case MQTT_EVENT_PUBLISHED:
       ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
       break;
    case MQTT_EVENT_DATA:
       ESP_LOGI(TAG, "MQTT_EVENT_DATA");
       printf("TOPIC=%.*s\r\n", event->topic_len, event->topic); // don't specify the length of the characters
       printf("DATA=%.*s\r\n", event->data_len, event->data);
       break;
    case MQTT_EVENT_ERROR:
       ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
       if(event->error_handle->error_type ==  MQTT_ERROR_TYPE_TCP_TRANSPORT){
            log_error_if_nonzero("reported from esp-tls", event->error_handle->esp_tls_last_esp_err);
            log_error_if_nonzero("reported from tls stack", event->error_handle->esp_tls_stack_err);
            log_error_if_nonzero("captured as transport's socket errno",  event->error_handle->esp_transport_sock_errno);
            ESP_LOGI(TAG, "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));
       }
    break;       

    default:
       ESP_LOGI(TAG, "Other event id:%d", event->event_id);
       break;
  }
}


static void mqtt_app_start(void){

    esp_mqtt_client_config_t mqtt_cfg = {
       .broker.address.uri = CONFIG_BROKER_URL, 
    };

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);

}


void app_main(){

    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %" PRIu32 " bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("mqtt_client", ESP_LOG_VERBOSE);
    esp_log_level_set("MQTT_EXAMPLE", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_BASE", ESP_LOG_VERBOSE);
    esp_log_level_set("esp-tls", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT", ESP_LOG_VERBOSE);
    esp_log_level_set("outbox", ESP_LOG_VERBOSE);

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_ERROR_CHECK(example_connect());

    mqtt_app_start();


}

