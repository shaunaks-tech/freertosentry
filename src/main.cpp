#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "main";

#define LED_GPIO  GPIO_NUM_2   // Onboard LED on most ESP32 dev boards

void main_task(void *pvParameters)
{
    bool led_on = false;
    while (1) {
        led_on = !led_on;
        gpio_set_level(LED_GPIO, led_on ? 1 : 0);
        ESP_LOGI(TAG, "LED %s", led_on ? "on" : "off");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

extern "C" void app_main(void)
{
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    ESP_LOGI(TAG, "Hello from ESP32!");
    xTaskCreate(main_task, "main_task", 4096, NULL, 5, NULL);
}
