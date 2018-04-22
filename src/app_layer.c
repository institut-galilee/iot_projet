/*
 * IoT-Labs-2018
 * Copyright (C) 2018 Massinissa Hamidi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "app_layer.h"
#include "trans_layer.h"

#define REQUEST_SIZE_MAX    200

char hostname[] = "hostname";
char resource[] = "/resource";

// TODO probably introducing an encryption layer on top of the application
// protocol (application layer encryption). This has not to be confused with
// transport layer encryption like tls which lie on top of the transport
// layer.

int8_t app_layer_start(enum app_protocols app_proto);
int8_t send_a_reading(const char *formatted_reading);
int8_t http_send(const char *formatted_reading);
int8_t coap_send(const char *formatted_reading);
int8_t mqtt_send(const char *formatted_reading);

int8_t
application_layer_start(enum app_protocols app_proto)
{
    int8_t rc;

    switch (app_proto) {
        case HTTP:
            rc = ENOSYS;  //http_send(???));
            break;
        case CoAP:
            rc = ENOSYS;  //coap_send(???);
            break;
        case MQTT:
            rc = ENOSYS;  //mqtt_send(???);
            break;
        default:
            rc = ENOSYS;     // ????????? HTTP ???????????
            break;
    }

    return rc;
}

int8_t
send_a_reading(const char *formatted_reading)
{
    int8_t rc;

    // TODO switch between available protocols

    rc = http_send(formatted_reading);
    if (rc < 0) {
        printf("[IoT-Labs] Error while sending a reading over http\n");
        return rc;
    }

    return rc;
}

int8_t
http_send(const char *formatted_reading)
{
    int8_t rc;
    char *sendline;

    sendline = (char*)malloc(REQUEST_SIZE_MAX*sizeof(char));
    if (sendline == NULL) {
        printf("[IoT-Labs] Error while allocating memory for http request\n");
        return errno;
    }

    /* wrap formatted_reading with an HTTP request, ... */
    //rc = ENOSYS; // La mettre dans une requete http .. Mais comment ?
    //char* test = "{\"timestep\": 8,\"value\": 8}";
    //printf("TAAAAAAIIIIIILLLLLLLLLLLLLLLLEEEEE ------------------------------------- %d", strlen(formatted_reading));
    snprintf(sendline, REQUEST_SIZE_MAX*sizeof(char), "POST /temperature HTTP/1.1\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n%s", strlen(formatted_reading) ,formatted_reading);
//  snprintf(sendline, REQUEST_SIZE_MAX*sizeof(char), "POST /temperature HTTP/1.1\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n%s", strlen(test) ,test);
  //  sendline ="POST /temperature HTTP/1.1\r\nContent-Type: application/json\r\nContent-Length: 26\r\n\r\n{\"timestep\": 8,\"value\": 8}";

    printf("[[ HTTP_SEND ]] sendline -> %s\n", sendline);

    /* ... then send it via transport layer */
    rc = trans_send(sendline); //sendline car 'a constant reference to data to be sent'    // fait

    return rc;
}


int8_t
coap_send(const char *formatted_reading)
{
    // failwith "Students, this is your job!"
    int8_t rc;
    rc = ENOSYS;

    return rc;
}

int8_t
mqtt_send(const char *formatted_reading)
{
    // failwith "Students, this is your job!"
    int8_t rc;
    rc = ENOSYS;

    return rc;
}
