/* UART asynchronous example, that uses separate RX and TX tasks

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"
#include "driver/gpio.h"

static const int RX_BUF_SIZE = 128;

#define UART_NUM UART_NUM_2
#define TXD_PIN (GPIO_NUM_17)
#define RXD_PIN (GPIO_NUM_16)

void init(void)
{
    const uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    // We won't use a buffer for sending data.
    uart_driver_install(UART_NUM, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

static void tx_task(void *arg){
	int num=0;
	uint8_t *data = (uint8_t*) malloc(30); //30 bytes 
	while(1){
		int len = sprintf((char *)data, "Hello World %d\n", num++);
		uart_write_bytes(UART_NUM, data, len);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	free(data);
}

static void rx_task(void *arg){
	
	static const char *RX_TASK_TAG = "RX_TASK";
	esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
	uint8_t *data = (uint8_t*) malloc(RX_BUF_SIZE+1);
	
	while(1){
		const int rxBytes = uart_read_bytes(UART_NUM, data, RX_BUF_SIZE, 200 / portTICK_PERIOD_MS);
		if(rxBytes > 0){
			data[rxBytes]=0; //setting all in Cero in the data
			ESP_LOGI(RX_TASK_TAG, "Read %d bytes: '%s'", rxBytes, data);
		}
		
	}
	
	free(data);
}


void app_main(void)
{
    init();
    xTaskCreate(rx_task, "uart_rx_task", 1024 * 2, NULL, configMAX_PRIORITIES - 1, NULL);
    xTaskCreate(tx_task, "uart_tx_task", 1024 * 2, NULL, configMAX_PRIORITIES - 2, NULL);
}




