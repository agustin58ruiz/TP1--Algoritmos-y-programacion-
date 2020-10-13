/***************************************************************************************/
/*Archivo main.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "config.h"
#include "types.h"
#include "utilities.h"
#include "gps.h"

int main (int argc, char *argv[])
{
	FILE *file_in;/*De este "archivo" se leerán los mensajes GPS en formato NMEA*/
	FILE *file_out;/*En este "archivo" se guardará el archivo ya convertido a CSV o kml y ordenado por fechas*/
	status_t st;
	format_t fmt;

	if ((st = validate_arguments(argc, argv, &fmt)) != OK) { 
		print_error(st);
		return st;
	}

	if ((file_in = fopen(argv[CMD_ARG_IN_FILE_POS], "rt")) == NULL) {
		st = ERROR_OPEN_NMEA_FILE;
		print_error(st);
		return st;
	}

	if ((file_out = fopen(argv[CMD_ARG_OUT_FLAG_POS+1], "wt")) == NULL) {
		st = ERROR_OPEN_OUT_FILE;
		fclose(file_in);
		print_error(st);
		return st;
	}

	if ((st = process_export(file_in,file_out,fmt)) != OK) {
		fclose(file_in);
		fclose(file_out);
		remove(argv[CMD_ARG_OUT_FLAG_POS+1]);
		print_error(st);
		return st;
	}

	fclose(file_in);
	if (fclose(file_out) == EOF) {
		st = ERROR_CLOSE_OUT_FILE;
		print_error(st);
		return st;
	}

	return OK;
}
/***************************************************************************************/
