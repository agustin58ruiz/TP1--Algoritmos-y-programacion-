/***************************************************************************************/
/*Archivo utilities.h*/
#ifndef UTILITIES__H
#define UTILITIES__H

#include <time.h>
#include "types.h"

#define MAX_DELIMITER 2

#define FIRST_POSITION 0
#define SECOND_POSITION 1

#define YEAR_CORRECTION 1900
#define MONTH_CORRECTION 1

#define CHECKSUM_DELIMITER '*'

char* strdupl(const char* s);
status_t read_line(char ** str, bool_t *eof, FILE * file);
unsigned char checksum(const char* str);
char* get_checksum(const char* str,char delimiter);
bool_t checksum_verificator(const char str[],char delimiter);
char* get_string_verificator(const char* string,char delimiter);

#endif
/***************************************************************************************/