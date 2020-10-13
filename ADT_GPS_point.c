/***************************************************************************************/
/*Archivo ADT_GPS_points.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "ADT_GPS_point.h"

/*La siguiente función crea un ADT_GPS_point_t con memoria dinámica.
Luego de su uso, hay que eliminar la variable usando ADT_GPS_point_delete.*/
status_t ADT_GPS_point_new(ADT_GPS_point_t ** point)
{
	if (point == NULL)
		return ERROR_NULL_POINTER;

	if((*point = (ADT_GPS_point_t *)malloc(sizeof(ADT_GPS_point_t))) == NULL)
		return ERROR_MEMORY;

	return OK;
}

/*La siguiente función elimina una variable de tipo ADT_GPS_point_t.*/
status_t ADT_GPS_point_delete(ADT_GPS_point_t ** point)
{
	if (point == NULL)
		return ERROR_NULL_POINTER;

	free(*point);
	*point = NULL;

	return OK;
}

/*La siguiente función combierte la latitud y longitud, que estan en formato hhmmss.sss, a 
formato decimal.*/
status_t ADT_GPS_point_convert_latitude_longitude(ADT_GPS_point_t *point){

	int aux_degrees;
	double aux_minutes;

	if(point==NULL)
		return ERROR_NULL_POINTER;

	aux_degrees=(point->latitude)/100;
	aux_minutes=(point->latitude)-(float)aux_degrees*100;
	point->latitude=aux_minutes/60+(float)(aux_degrees);
	if(point->lat_direction==SOUTH_DIRECTION)
		point->latitude*=-1;

	aux_degrees=0;
	aux_minutes=0;

	aux_degrees=(point->longitude)/100;
	aux_minutes=(point->longitude)-(float)aux_degrees*100;
	point->longitude=aux_minutes/60+(float)(aux_degrees);
	if(point->long_direction==WEST_DIRECTION)
		point->longitude*=-1;

	return OK;
}

/*La siguiente funcion recibe una línea gpgga y la guarda en una variable ADT_GPS_point_t*/
status_t ADT_GPS_point_split_record(ADT_GPS_point_t* gga,char delimiter,char* str){

	/*$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000*5E*/
	char* ptr;

	if(str==NULL || gga==NULL)
		return ERROR_NULL_POINTER;

	str=strchr(str,delimiter);
	str++;
	gga->UTC_time=strtod(str,&ptr);/*horario*/
	ptr++;
	gga->latitude=strtod(ptr,&str);/*latitud*/
	str++;
	gga->lat_direction=*str;/*indicador N/S*/
	str++;str++;
	gga->longitude=strtod(str,&ptr);/*longitud*/
	ptr++;
	gga->long_direction=*ptr;/*indicador E/O*/
	ptr++;ptr++;
	gga->quality=strtod(ptr,&str);/*calidad*/
	str++;
	gga->used_satellities=strtod(str,&ptr);/*satelites utilizados*/
	ptr++;
	gga->hdop=strtod(ptr,&str);/*hdop*/
	str++;
	gga->altitude=strtod(str,&ptr);/*altitud*/

	return OK;
}

/*La siguiente función compara dos registor ADT_GPS_point_t. Devuelve 0, si son iguales,
positivo si p1 está despues que p2 y negativo si p2 está despues de p1*/
int ADT_GPS_point_compare_by_time(ADT_GPS_point_t * p1, ADT_GPS_point_t *p2)
{
	return (int)((p1->UTC_time - p2->UTC_time)*1000);
}

/*La siguiente función imprime un registro ADT_GPS_point_t en formato CSV.*/
status_t ADT_GPS_point_print_as_CSV(const ADT_GPS_point_t * point, char del, FILE *fo)
{

	char date[DATE_STR_SIZE];

	if(point == NULL || fo == NULL)
		return ERROR_NULL_POINTER;

	ADT_GPS_point_get_date_as_AAAAMMDDHHmmSS(point, date);

	fprintf(fo, "%s%c%f%c%f%c%f",date, del, point->latitude,del, point->longitude,del, point->altitude);

	return OK;
}
/*La siguiente función imprime un registro ADT_GPS_point_t en formato kml.*/
status_t ADT_GPS_point_print_as_kml(const ADT_GPS_point_t * point, char del, FILE *fo)
{
	if(point == NULL || fo == NULL)
		return ERROR_NULL_POINTER;
	fprintf(fo, "%f%c%f%c%f", point-> longitude, del, point->latitude, del, point->altitude);
	return OK;
}

/*La siguiente función recibe un registro ADT_GPS_point_t y guarda en la cadena str
la fecha en que se usa el programa, con la hora en que viene en el registro*/
status_t ADT_GPS_point_get_date_as_AAAAMMDDHHmmSS(ADT_GPS_point_t *point, char *str)
{
	struct tm* p;
	time_t t;
	int hours;
	int minuts;
	int seconds;
	size_t aux;

	if(point == NULL)
		return ERROR_NULL_POINTER;

	time(&t);
	p=localtime(&t);

	aux = (point->UTC_time);
	hours = aux / 10000;

	aux = aux - hours * 10000; 
	minuts = aux / 100;

	aux = aux - minuts * 100;
	seconds = aux;

	sprintf(str,"%4i%02i%02i%02i%02i%02i",p->tm_year+YEAR_CORRECTION, p->tm_mon+MONTH_CORRECTION, p->tm_mday, hours, minuts,seconds);
	return OK;
}
/***************************************************************************************/