/***************************************************************************************/
/*Archivo gps.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "gps.h"
#include "errors.h"
#include "ADT_GPS_point.h"
#include "ADT_Vector.h"
#include "utilities.h"

/*Variables globales para exportar*/
status_t (*print_vector[MAX_FORMAT_OPTION])(ADT_Vector_t *, FILE *, char, status_t (*)(const void *,char, FILE *)) ={
	ADT_Vector_export_as_CSV,
	ADT_Vector_export_as_kml
};

status_t (*print_a_point[MAX_FORMAT_OPTION])(const void *,char, FILE *) = {
	ADT_GPS_point_print_as_CSV,
	ADT_GPS_point_print_as_kml
};

char delimiter[MAX_FORMAT_OPTION] = {
	CSV_DELIMITER,
	KML_DELIMITER
};

/*La siguiente función verifica que la línea sea gpgga. str debe estar creada.*/
bool_t is_gpgga(char *str)
{

	if(str == NULL)
		return FALSE;

	return (!strncmp(str, PROTOCOL_GPGGA_HEADER, PROTOCOL_GPGGA_LENGTH))? TRUE : FALSE;
}

/*La siguiente función revisa si los campos de la linea GPGGA esten vacíos.
PRECONDICIÓN: La linea str debe ser gpgga, si no, no tiene sentido. Primero debe
verificarse que str sea gpgga.*/
bool_t is_empty(char *str)
{

	if(str == NULL)
		return FALSE;

	return (strlen(str) < GPGGA_EMPTY_LENGH) ? TRUE : FALSE;
}

/*La siguiente función lee los registros de un archivo */
status_t process_export(FILE* fi,FILE* fo,format_t fmt){
	
	ADT_Vector_t *gps_points;
	status_t st;

	if(fi==NULL || fo==NULL)
		return ERROR_NULL_POINTER;

	/*se crea el vector donde se van a guardar los puntos gps*/
	if((st = ADT_Vector_new(&gps_points)) != OK)
		return st;

	/*Se cargan los registros provenientes del archivo nmea al vector*/
	if((st = load_gps_points(gps_points,fi))!=OK)
		return st;

	if((st = ADT_Vector_sort(gps_points, ADT_GPS_point_compare_by_time))!= OK)
	{
		ADT_Vector_delete(&gps_points, ADT_GPS_point_delete);
		return st;
	}


	if((st = (*print_vector[fmt])(gps_points, fo, delimiter[fmt],*print_a_point[fmt])) != OK)
	{
		ADT_Vector_delete(&gps_points, ADT_GPS_point_delete);
		return st;
	}

	ADT_Vector_delete(&gps_points, ADT_GPS_point_delete);

	return OK;
}


/*La siguiente función carga un arreglo de vector
El vector points debe estar previamente creado, fi debe estar previamente abierto*/
status_t load_gps_points(ADT_Vector_t *points, FILE * fi)
{
	size_t i;
	status_t st;
	bool_t eof;
	ADT_GPS_point_t *point;

	if(points == NULL || fi==NULL)
		return ERROR_NULL_POINTER;

	if((st = ADT_GPS_point_new(&point)) != OK)
		return st;

	if((st =load_a_gps_point(point,&eof ,fi)) != OK)
	{
		ADT_GPS_point_delete(&point);
		return st;
	}

	for(i = 0; eof == FALSE; i++)
	{	
		if((st = ADT_Vector_set_element_at(points, i, point, ADT_GPS_point_delete)) != OK)/*Se agrego un elemento al vector*/
		{
			ADT_GPS_point_delete(&point);
			return st;
		}
		if((st = ADT_GPS_point_new(&point)) != OK) /* Se crea otro punto*/
			return st;
		if((st =load_a_gps_point(point,&eof ,fi)) != OK)/* se carga otro punto del archivo nmea*/
		{
			ADT_GPS_point_delete(&point);
			return st;
		}

	}

	return OK;
}

/*La siguiente función lee un archivo NMEA y busca un registro de tipo GPGGA. Cuando lo encuentra
lo carga a una estrctura de tipo ADT_GPS_point_t. 
point debe estar previamente creado. fi debe estar previamente abierto*/
status_t load_a_gps_point(ADT_GPS_point_t *point,bool_t *eof ,FILE *fi)
{

	char *line;
	status_t st;

	if (point == NULL || eof == NULL || fi == NULL)
		return ERROR_NULL_POINTER;

	if((st=read_line(&line,eof,fi))!=OK)
		return st;
	
	if(*eof == TRUE)
	{	
		free(line);	
		return OK;
	}

	if(checksum_verificator(line,CHECKSUM_DELIMITER) == FALSE)
	{
		free(line);
		return ERROR_CORRUPTED_NMEA_FILE;
	}

	while(*eof == FALSE && (is_gpgga(line) == FALSE || is_empty(line) == TRUE))
	{
		free(line);
		if((st=read_line(&line,eof,fi))!=OK)
			return st;

		if(*eof == TRUE)
		{	
			free(line);	
			return OK;
		}

		if(checksum_verificator(line,CHECKSUM_DELIMITER) == FALSE)
		{
			free(line);
			return ERROR_CORRUPTED_NMEA_FILE;
		}	
	}

	ADT_GPS_point_split_record(point,GPGGA_DELIMITER,line);
	ADT_GPS_point_convert_latitude_longitude(point);

	return OK;
}
/***************************************************************************************/