/***************************************************************************************/
/*Archivo errors.c*/
#include <stdio.h>
#include "errors.h"

/*Diccionario de errores*/
char *errors [MAX_ERRORS] = {
	"",
 	ERROR_MSG_NULL_POINTER,
 	ERROR_MSG_PROGRAM_INVOCATION,
 	ERROR_MSG_MEMORY,
 	ERROR_MSG_OPEN_NMEA_FILE,
 	ERROR_MSG_OPEN_OUT_FILE,
 	ERROR_MSG_CLOSE_OUT_FILE,
	ERROR_MSG_UNKNOWN_LAT_DIRECTION,
	ERROR_MSG_UNKNOWN_LONG_DIRECTION,
	ERROR_MSG_UNKNOWN_ALTITUDE_UNIT,
	ERROR_MSG_CORRUPTED_NMEA_FILE
};

/*La siguiente funcion imprime los errores del programa.
	·st es una variable que contiene el enumerativo de error.
PRECONDICIONES: la funcion usa un diccionaro global, debe estar previamente creado.
POSTCONDICIONES: ninguna.
*/
status_t print_error(status_t st)
{
	fprintf(stderr, "%s\n", errors[st]);
	return st;
}
/***************************************************************************************/