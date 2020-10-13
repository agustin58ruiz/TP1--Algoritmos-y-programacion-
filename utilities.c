/***************************************************************************************/
/*Archivo utilities.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utilities.h"
#include "types.h"

#define INIT_CHOP 100
#define CHOP_SIZE 20

char* strdupl(const char* s){

	char* t;
	size_t i;

	if(s==NULL)
		return NULL;

	if((t=(char*)malloc(sizeof(char)*(strlen(s)+1)))==NULL)
		return NULL;

	for(i=0;(t[i]=s[i]);i++);

	return t;
}

status_t read_line(char ** str, bool_t *eof, FILE * file)
{
	size_t alloc_size;
	char c;
	char *aux;
	size_t used_size;

	if (str == NULL || eof == NULL || file == NULL)
		return ERROR_NULL_POINTER;

	if((*str = (char *)malloc(INIT_CHOP * sizeof(char))) == NULL)
		return ERROR_MEMORY;

	alloc_size = INIT_CHOP;

	used_size = 0;
	while ((c = fgetc(file)) != '\n' && c != EOF)
	{
		/*El - 1 sirve para guardar el '\0'*/
		if(used_size == alloc_size - 1)
		{
			if((aux = (char *)realloc(*str, (alloc_size + CHOP_SIZE) * sizeof(char))) == NULL)
			{
				free(str);
				return ERROR_MEMORY;
			}
			*str = aux;
			alloc_size += CHOP_SIZE;
		}
		if(c == '\r')/*se ignora el retorno de carro*/
			continue;
		(*str)[ used_size++ ] = c;
	}
	(*str)[ used_size ] = '\0';

	*eof = ( c == EOF )? TRUE : FALSE;

	return OK;
}
/*Ejemplo de registro:
$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000*5E

Lo que debe recibir:
GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000

Devuelve una cadena que representa el numero de verificacion en decimal
*/
unsigned char checksum(const char* str){

	unsigned char sum=0;

	while(*str)
		sum^=*str++;

	return sum;
}

/*Recibe el registro completo y devuelve el numero de verificacion*/
char* get_checksum(const char* str,char delimiter){

	char* ptr;

	if(str==NULL)
		return NULL;

	ptr=strchr(str,delimiter);

	if(ptr==NULL)
		return NULL;

	ptr++;
	return ptr;
}

/*Recibe la cadena y el * y devuelve la cadena sin el $ y hasta el * sin incluir*/

char* get_string_verificator(const char* string,char delimiter){

	char* str;
	char* ptr;

	if(string==NULL)
		return NULL;

	if((str=strdupl(string + 1))==NULL)
		return NULL;

	ptr=strchr(str,delimiter);

	if(ptr == NULL)
	{
		free(str);
		return NULL;
	}

	*ptr='\0';

	return str;
}

/*Recibe la cadena completa y analiza si el numero de verificacion coincide con el checksum*/
bool_t checksum_verificator(const char str[],char delimiter){

	unsigned char sum;
	char *str_to_verificate;
	char *check;
	long s;

	if((str_to_verificate = get_string_verificator(str,CHECKSUM_DELIMITER)) == NULL)
		return FALSE;

	sum=checksum(str_to_verificate);

	free(str_to_verificate);

	if((check = get_checksum(str,delimiter)) == NULL)
		return FALSE;

	s=strtol(check,NULL,16);

	return (sum==s)?TRUE:FALSE;
}
/***************************************************************************************/