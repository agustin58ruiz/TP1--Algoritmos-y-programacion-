/***************************************************************************************/
/*Archivo ADT_Vector.h*/
#ifndef ADT_VECTOR__H
#define ADT_VECTOR__H

#include <stdio.h>
#include "types.h"

typedef struct 
{
	void **elements;/*Arreglo de punteros a elementos*/
	size_t used_size;/*Cantidad de elementos*/
	size_t alloc_size;/*Cantidad de memoria pedida*/

}ADT_Vector_t;


/*PROTOTIPOS*/

status_t ADT_Vector_new(ADT_Vector_t **p);
status_t ADT_Vector_delete(ADT_Vector_t **p, status_t (*destructor)(void ** ));
status_t ADT_Vector_new_size(ADT_Vector_t *v, size_t new_size, status_t (*destructor)(void ** ));
status_t ADT_Vector_sort(ADT_Vector_t *v,int (*compare)(void *, void *));
void ADT_Vector_swap_elements(ADT_Vector_t *v, size_t pos_1, size_t pos_2);
status_t ADT_Vector_export_as_CSV(ADT_Vector_t *vector, FILE * fo, char del, status_t (*printer)(const void *,char, FILE *));
status_t ADT_Vector_export_as_kml(ADT_Vector_t *vector, FILE * fo, char del, status_t (*printer)(const void *,char, FILE *));

/*GETTERS*/

size_t ADT_Vector_get_min_key_pos(ADT_Vector_t *v, size_t init_pos, size_t final_pos, int (*compare)(void *, void *));
void * ADT_Vector_get_element_at(ADT_Vector_t *v, size_t pos);
status_t ADT_Vector_get_used_size(ADT_Vector_t *v, size_t *used_size);

/*SETTERS*/

status_t ADT_Vector_set_element_at(ADT_Vector_t *v, size_t pos, void *data, status_t (*destructor)(void ** ));

#endif
/***************************************************************************************/