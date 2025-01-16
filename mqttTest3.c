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

//For the i2c
#include "driver/i2c.h"
//Define the pins of the i2c
#define I2C_NUM I2C_NUM_0
#define I2C_SCL GPIO_NUM_19
#define I2C_SDA GPIO_NUM_23
#define MPU_ADDR 0x68

float tempInC =0.0;

//init the i2c 
static esp_err_t i2c_master_init(void){

   int i2c_master_port = I2C_NUM;

   //configure the parameters for struct of the i2c 
   i2c_config_t conf = {
      .mode = I2C_MODE_MASTER,
      .sda_io_num = I2C_SDA,
      .scl_io_num = I2C_SCL,
      .sda_pullup_en = GPIO_PULLUP_ENABLE,
      .scl_pullup_en = GPIO_PULLUP_ENABLE,
      .master.clk_speed = 400000,
   };

   //pass the parameter to this function config i2c
   i2c_param_config(i2c_master_port,&conf);
   //install the driver
   return i2c_driver_install(i2c_master_port, conf.mode, 0,0,0);
}

//Read data from register 
esp_err_t mpuReadfromReg(uint8_t Reg, uint8_t *ReadBuffer , size_t len){
   return (i2c_master_write_read_device(I2C_NUM, MPU_ADDR, &Reg, 1, ReadBuffer, len, 2000));
}

//write a single data byte 
esp_err_t mpuWriteReg(uint8_t Reg , uint8_t data){
   
   uint8_t writeBuf[2];
   writeBuf[0] = Reg;
   writeBuf[1] = data;

   return (i2c_master_write_to_device(I2C_NUM, MPU_ADDR, writeBuf, 2, 1000));

}

//First we need to create the TAG 
static const char *TAG = "MQTT_EXAMPLE"; // To identify the message into the log 
static const char *TAG_i2c = "I2C_EXAMPLE"; // To identify the message into the log 

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
 
 char payload[100];

 switch((esp_mqtt_event_id_t)event_id){

    //Check if it is connected
    case MQTT_EVENT_CONNECTED:
       ESP_LOGI(TAG,"MQTT EVENT_CONNECTED");
       snprintf(payload,sizeof(payload),"{\"Temp} :  %.2f}",tempInC);
       msg_id = esp_mqtt_client_publish(client,"/topic/qos0",payload,0,1,0);
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

    //mpu6050 
    uint8_t data[10];
    uint8_t dataTemperature[10];
    ESP_ERROR_CHECK(i2c_master_init());
    ESP_LOGI(TAG_i2c, "I2C initialized successfully");

    mpuReadfromReg(0x75,data,1);
    ESP_LOGI(TAG_i2c, "%X", data[0]);

    mpuWriteReg(0x6B,0);
    mpuWriteReg(0x19, 7); // sample rate 1KHz
    mpuWriteReg(0x1C, 0);  // ACC FS Range ±2g  
   
   //Read the data from the mpu6050 sensor 
   //mqtt
    mqtt_app_start();

   
   while(1){
      mpuReadfromReg(0x3B,data,6); // read 6 bytes FOR THE ACCELEROMETER
      mpuReadfromReg(0x41,dataTemperature,2); // read 2 bytes for the temperature

      int16_t RAWX = (data[0]<<8)|data[1]; // to combine the 2 bytes into a register of 16 bites
      int16_t RAWY = (data[2]<<8)|data[3];     
      int16_t RAWZ = (data[4]<<8)|data[5];

      int16_t TEMP_OUT = (dataTemperature[0]<<8)|(dataTemperature[1]); // the array takes bites
      
      //Divide the sensibility , also the sensibility are in the datasheet
      float xg = (float)RAWX/16384;
      float yg = (float)RAWY/16384;
      float zg = (float)RAWZ/16384;

      //Temperature in degrees
      tempInC = (((TEMP_OUT)/(340))+36.53);

      ESP_LOGI(TAG_i2c, "\nx=%.2f\ty=%.2f\tz=%.2f", xg, yg, zg);
      ESP_LOGI(TAG_i2c, "\nTemperature Value = %.2f", tempInC);
      sleep(1);
    }   
   
}

