/*
 * This file is part of ARGUS Ground Station
 * <https://github.com/nikolaptr/argus>.
 *
 * ARGUS Ground Station is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ARGUS Ground Station is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ARGUS Ground Station. If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2025 Nikola Petrovic
 * Contact: <nikolaptr6@gmail.com>
 */

#include "driver/uart.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

#include "telemetry_bridge.h"

/* telemetry receive UART buffer size */
#define ARGUS_TELEMETRY_RX_BUF_SIZE 512
/* telemetry transmit UART buffer size */
#define ARGUS_TELEMETRY_TX_BUF_SIZE 512

void app_main(void)
{
    /* telemetry UART */
    uart_config_t uart_config = {
        .baud_rate = CONFIG_ARGUS_TELEMETRY_UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    int intr_alloc_flags = 0;

#if CONFIG_UART_ISR_IN_IRAM
    intr_alloc_flags = ESP_INTR_FLAG_IRAM;
#endif

    ESP_ERROR_CHECK(uart_driver_install(
        CONFIG_ARGUS_TELEMETRY_UART_PORT_NUM, ARGUS_TELEMETRY_RX_BUF_SIZE,
        ARGUS_TELEMETRY_TX_BUF_SIZE, 0, NULL, intr_alloc_flags));
    ESP_ERROR_CHECK(
        uart_param_config(CONFIG_ARGUS_TELEMETRY_UART_PORT_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(CONFIG_ARGUS_TELEMETRY_UART_PORT_NUM,
                                 CONFIG_ARGUS_TELEMETRY_UART_TXD,
                                 CONFIG_ARGUS_TELEMETRY_UART_RXD,
                                 UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    /* parse incoming telemetry MAVLink packets */
    xTaskCreate(telemetry_bridge, "telemetry_bridge",
                CONFIG_ARGUS_TELEMETRY_TASK_STACK_SIZE, NULL, 1, NULL);
}
