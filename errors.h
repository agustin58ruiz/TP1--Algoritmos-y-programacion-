/***************************************************************************************/
/*Archivo errors.h*/
#ifndef ERRORS__H
#define ERRORS__H

#include <stdio.h>
#include "types.h"

#define MAX_ERRORS 11

#define ERROR_MSG_NULL_POINTER "PUNTERO NULO"
#define ERROR_MSG_PROGRAM_INVOCATION "ARGUMENTOS INCORRECTOS"
#define ERROR_MSG_MEMORY "MEMORIA INSUFICIENTE"
#define ERROR_MSG_OPEN_NMEA_FILE "ERROR AL ABRIR EL ARCHIVO NMEA"
#define ERROR_MSG_OPEN_OUT_FILE "ERROR AL ABRIR EL ARCHIVO DE SALIDA"
#define ERROR_MSG_CLOSE_OUT_FILE "ERROR AL CERRAR EL ARCHIVO DE SALIDA"
#define	ERROR_MSG_UNKNOWN_LAT_DIRECTION "DIRECCION DE LATITTUD DESCONOCIDA"
#define	ERROR_MSG_UNKNOWN_LONG_DIRECTION "DIRECCION DE LONGITUD DESCONOCIDA"
#define	ERROR_MSG_UNKNOWN_ALTITUDE_UNIT "UNIDAD DE LONGITUD DESCONOCIDA"
#define	ERROR_MSG_CORRUPTED_NMEA_FILE "EL ARCHIVO NMEA ESTA CORRUPTO"

status_t print_error(status_t st);

#endif 
/***************************************************************************************/