/***************************************************************************************/
/*Archivo kml_utilities.c*/
#include <stdio.h>
#include "kml_utilities.h"

status_t print_header_tag(char *tag, FILE *fo)
{
	if(tag == NULL || fo == NULL)
		return ERROR_NULL_POINTER;

	fprintf(fo, "%c%s%c", LESS_THAN_SYMBOL,tag, GREATER_THAN_SYMBOL);

	return OK;
}

status_t print_footer_tag(char *tag, FILE *fo)
{

	if(tag == NULL || fo == NULL)
		return ERROR_NULL_POINTER;

	fprintf(fo, "%c%c%s%c", LESS_THAN_SYMBOL, FORWARD_SLASH_SYMBOL, tag, GREATER_THAN_SYMBOL);

	return OK;
}

status_t print_line(char* tag,char* parameter,FILE* fo)
{

	if(tag==NULL || parameter==NULL || fo==NULL)
		return ERROR_NULL_POINTER;

	fprintf(fo, "%c%s%c%s%c%c%s%c\n" , LESS_THAN_SYMBOL,tag,GREATER_THAN_SYMBOL,parameter,LESS_THAN_SYMBOL,FORWARD_SLASH_SYMBOL,tag,GREATER_THAN_SYMBOL);

	return OK;

}
/***************************************************************************************/