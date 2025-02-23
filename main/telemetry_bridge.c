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

#include "telemetry_bridge.h"
#include "driver/uart.h"
#include "esp_log.h"

/* telemetry MAVLink channel - used for message parsing and message packing */
#define ARGUS_TELEMETRY_MAV_CH MAVLINK_COMM_0

void telemetry_bridge(void *arg)
{
    mavlink_message_t mav_msg;               // MAVLink message.
    uint8_t mav_buf[MAVLINK_MAX_PACKET_LEN]; // MAVLink serialization buffer.
    uint8_t uart_rx[32];                     // UART receive buffer.

    for (;;) {
        /* read data from UART */
        int len = uart_read_bytes(CONFIG_ARGUS_TELEMETRY_UART_PORT_NUM, uart_rx,
                                  sizeof(uart_rx), 10 / portTICK_PERIOD_MS);

        /* error occurred during read */
        if (len < 0)
            continue;

        /* parse read data */
        for (int i = 0; i < len; i++) {
            uint8_t status = 0;
            status = mavlink_parse_char(ARGUS_TELEMETRY_MAV_CH, uart_rx[i],
                                        &mav_msg, NULL);

            /* no message could be decoded or bad CRC */
            if (status != 1)
                continue;

            /* pass message to GCS */
            uint16_t size = mavlink_msg_to_send_buffer(mav_buf, &mav_msg);

            uart_write_bytes(CONFIG_ARGUS_GCS_UART_PORT_NUM, mav_buf, size);
        }
    }
}
