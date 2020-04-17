/**
Libre Wireless Technologies
 **/

#ifndef _DATE_TIME_H
#define _DATE_TIME_H

//Dependencies
#include <time.h>
#include "stdint.h"
#include "os_port.h"


/**
 * @brief Date and time representation
 **/

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t dayOfWeek;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint16_t milliseconds;
} DateTime;


//Date and time management
const char_t *formatSystemTime(systime_t time, char_t *str);
const char_t *formatDate(const DateTime *date, char_t *str);

void getCurrentDate(DateTime *date);
time_t getCurrentUnixTime(void);

void convertUnixTimeToDate(time_t t, DateTime *date);
time_t convertDateToUnixTime(const DateTime *date);

uint8_t computeDayOfWeek(uint16_t y, uint8_t m, uint8_t d);

#endif
