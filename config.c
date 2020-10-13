/***************************************************************************************/
/*Archivo config.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "types.h"

/*La siguiente función valida las cadenas de caracteres ingresadas por el usuario
en la linea de comandos. 
	·argc es el numero de argumentos ingresados.
	·argv es un arreglo de cadenas con los token ingresados por el usuario.
	·fmt puntero a una variable de tipo format_t en donde se guardará la opcion de formato
	de salida.
PRECONDICIONES: fmt debe estar previamente creado. argv y argc deben ser los mismos parametros
que los de la función main.
POSTCONDICIONES: ninguna.
*/
status_t validate_arguments(int argc, char **argv, format_t *fmt)
{
	if(argv == NULL || fmt==NULL)
		return ERROR_NULL_POINTER;

	if(argc!=MAX_CMD_ARGS)
		return ERROR_PROGRAM_INVOCATION;

	if(strcmp(argv[CMD_ARG_FORMAT_FLAG_POS], CMD_ARG_FORMAT_FLAG_TOKEN))
		return ERROR_PROGRAM_INVOCATION;

	if(strcmp(argv[CMD_ARG_OUT_FLAG_POS], CMD_ARG_OUT_FLAG_TOKEN))
		return ERROR_PROGRAM_INVOCATION;

	if(!strcmp(argv[CMD_ARG_FORMAT_FLAG_POS + 1], CMD_ARG_FORMAT_CSV_TOKEN))
		*fmt = FMT_CSV;
	else if(!strcmp(argv[CMD_ARG_FORMAT_FLAG_POS + 1], CMD_ARG_FORMAT_KML_TOKEN))
		*fmt = FMT_KML;
	else 
		return ERROR_PROGRAM_INVOCATION;

	return OK;
}
/***************************************************************************************/