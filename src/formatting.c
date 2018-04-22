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


#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include <string.h>

#include "formatting.h"




cJSON *
json_of_reading(const struct a_reading *reading)
{
    int8_t rc = 0;
    cJSON *timestamp;
    cJSON *bme280_reading;
    cJSON *temperature;
    cJSON *pressure;
    cJSON *humidity;
    cJSON * json;

    printf("[json_of_reading] ##########################\n");
    //print_a_reading(reading);

    // create root node
    json = cJSON_CreateObject();

    timestamp = cJSON_CreateNumber(reading->timestamp);
//Fait
    cJSON_AddNumberToObject(json, "timestamp", reading->timestamp);

    bme280_reading = cJSON_CreateObject();

    temperature = cJSON_CreateNumber(reading->data.temperature);
    if (!temperature) {
        printf("\n");
        goto end;
    }

    pressure = cJSON_CreateNumber(reading->data.pressure);
    if (!pressure) {
        printf("\n");
        goto end;
    }

    humidity = cJSON_CreateNumber(reading->data.humidity);
    if (!humidity) {
        printf("\n");
        goto end;
    }

    // TODO failwith "Students, this is your job!"
//fait
    cJSON_AddNumberToObject(bme280_reading, "temperature", reading->data.temperature);
    cJSON_AddNumberToObject(bme280_reading, "pressure", reading->data.pressure);
    cJSON_AddNumberToObject(bme280_reading, "humidity", reading->data.humidity);

    cJSON_AddItemToObject(json, "reading", bme280_reading); // fait

    // debug
    printf("Test n°1 : \n\n%s\n\n", cJSON_Print(json));

    return json;

end:
    cJSON_Delete(json);
    return NULL;
}

/* Assemble multiple readings in a unique json object */
int8_t
json_of_readings(cJSON *json, const struct a_reading **readings)
{
    int8_t rc;
    rc = ENOSYS;
    return rc;
}


int8_t
string_of_json(char *buff, cJSON *json)
{
    int8_t rc;

    char * var = cJSON_Print(json);
    memcpy(buff, var, strlen(var)+1);

    if (buff == NULL){
      buff = (char*)malloc(200*sizeof(char));
      buff = "{'error': 'no json could be formatted'}";

      rc = -1;
    }

    rc = 1;
    return rc;
}

int8_t
reading_formatting(char *representation, const struct a_reading *reading)
{
  int8_t rc=1;
  cJSON *json;

    // make a json object from dequeued reading
    json = json_of_reading(reading);

    printf("Test n°2 : \n\n%s\n\n", cJSON_Print(json));

    // get string representation of json object
    rc = string_of_json(representation, json);

    printf("Test n°3 : \n\n%s\n\n", representation);

    if (rc < 0) {
        printf("[IoT-Labs] Error while getting string repr. from json\n");
        return rc;
    }

    return rc;
}
