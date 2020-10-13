/***************************************************************************************/
/*Archivo types.h*/
#ifndef TYPES__H
#define TYPES__H

#include <stdio.h>

typedef enum 
{
	FALSE,
	TRUE
}bool_t;

typedef enum
{
	FMT_CSV,
	FMT_KML

}format_t;

typedef enum 
{
	OK, 
	ERROR_NULL_POINTER,
	ERROR_PROGRAM_INVOCATION,
	ERROR_MEMORY,
	ERROR_OPEN_NMEA_FILE,
	ERROR_OPEN_OUT_FILE,
	ERROR_CLOSE_OUT_FILE,
	ERROR_UNKNOWN_LAT_DIRECTION,
	ERROR_UNKNOWN_LONG_DIRECTION,
	ERROR_UNKNOWN_ALTITUDE_UNIT,
	ERROR_CORRUPTED_NMEA_FILE

}status_t;

#endif
/***************************************************************************************/