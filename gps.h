/***************************************************************************************/
/*Archivo gps.h*/
#ifndef GPS__H
#define GPS__H

#include <stdio.h>
#include "ADT_Vector.h"
#include "ADT_GPS_point.h"
#include "types.h"

#define PROTOCOL_GPGGA_HEADER "$GPGGA"
#define PROTOCOL_GPGGA_LENGTH 6
#define GPGGA_DELIMITER ','
#define GPGGA_EMPTY_LENGH 33

#define CSV_DELIMITER '|'
#define KML_DELIMITER ','

#define MAX_FORMAT_OPTION 2

#define MAX_DELIMITER 2
#define DELIMITER_POSITION 0
#define END_POSITION 1
#define CMP_CHARACTERS 1

bool_t is_gpgga(char *str);
bool_t is_empty(char *str);
status_t process_export(FILE* fi,FILE* fo,format_t fmt);
status_t load_gps_points(ADT_Vector_t *points, FILE * fi);
status_t load_a_gps_point(ADT_GPS_point_t *point,bool_t *eof ,FILE *fi);

#endif
/***************************************************************************************/