/***************************************************************************************/
/*Archivo ADT_GPS_points.h*/
#ifndef ADT_RECORD__H
#define ADT_RECORD__H

#include <stdio.h>
#include <time.h>
#include "types.h"

#define METRE_UNIT_VALUE 'M'
#define SOUTH_DIRECTION 'S'
#define WEST_DIRECTION 'W'
#define YEAR_CORRECTION  1900
#define MONTH_CORRECTION 1
#define DATE_STR_SIZE 15

typedef struct{
	double UTC_time;
	double latitude;
	char lat_direction;
	double longitude;
	char long_direction;
	size_t quality;
	unsigned char used_satellities;
	float hdop;
	double altitude;
	char altitude_unit;
	double separation_of_geoid;
	char sep_of_geoid_unit;
	float age_of_diff_corr;
	int diff_ref_statition_id;
}ADT_GPS_point_t;

status_t ADT_GPS_point_new(ADT_GPS_point_t ** point);
status_t ADT_GPS_point_delete(ADT_GPS_point_t ** point);
status_t ADT_GPS_point_convert_latitude_longitude(ADT_GPS_point_t *point);
status_t ADT_GPS_point_print_as_CSV(const ADT_GPS_point_t * point, char del, FILE *fo);
status_t ADT_GPS_point_print_as_kml(const ADT_GPS_point_t * point, char del, FILE *fo);
status_t ADT_GPS_point_split_record(ADT_GPS_point_t* gga,char delimiter,char* str);
int ADT_GPS_point_compare_by_time(ADT_GPS_point_t * p1, ADT_GPS_point_t *p2);
status_t ADT_GPS_point_get_date_as_AAAAMMDDHHmmSS(ADT_GPS_point_t *point, char *str);

#endif
/***************************************************************************************/