/***************************************************************************************/
/*Archivo ADT_Vector.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADT_Vector.h"
#include "types.h"
#include "kml_utilities.h"

#define INIT_CHOP 5
#define CHOP_SIZE 5

/*La siguiente funcion crea un vector vacío.
	·p es un puntero a un puntero a una estructura de tipo ADT_Vector_t.
PRECONDICIONES: ninguna. 
POSTCONDIONES: El vector aun no esta inicializado. Su inicialización y carga de elementos
debe realizarce con los setters correspondientes. Se debe eliminar el vector con la función
destructura correspondiente cuando no se utilise más.
*/
status_t ADT_Vector_new(ADT_Vector_t **p)
{
	size_t i;

	if(p == NULL)
		return ERROR_NULL_POINTER;
	/*Se crea una estructura de tipo ADT_Vector_t*/
	if((*p = (ADT_Vector_t *)malloc(sizeof(ADT_Vector_t))) == NULL)/* MD para *p*/
		return ERROR_MEMORY;

	if(((*p)->elements = (void **)malloc(INIT_CHOP * sizeof(void *))) == NULL)
	{
		free(*p);
		*p = NULL;
		return ERROR_MEMORY;
	}

	(*p)->alloc_size = INIT_CHOP;
	(*p)->used_size = 0;

	for(i = 0; i < (*p)->alloc_size; i++)
		((*p) -> elements)[i] = NULL;

	return OK;
}

/*La siguiente función elimina un vector con sus elementos.
	·p es un puntero doble al vector a eliminar.
	·destructor es un puntero a una función que elimina los elementos.
PRECONDICIONES: El vector debe estar previamente creado.
POSTCONDICIONES: Ninguna.
*/
status_t ADT_Vector_delete(ADT_Vector_t **p, status_t (*destructor)(void ** ))
{
	size_t i;
	status_t st;

	if( p == NULL || destructor == NULL)
		return ERROR_NULL_POINTER;
	
	for( i = 0; i < (*p)->used_size; i++)
	{
		if((st= (*destructor)((*p)->elements + i)) != OK)
			return st;
		(*p) -> elements[i] = NULL;
	}

	free((*p)->elements);
	free(*p);
	*p = NULL;

	return OK;
}

/*La siguiente función cambia el tamaño de un vector. Si el nuevo tamaño es menor que used_size, se
borran los elementos que no entran en el nuevo vector.
	·v vector al que se quiere cambiar de tamaño.
	·new_size es el nuevo tamaño que tendra el vector.
	·destructor es un puntero a función que sirve para borrar elementos en caso de ser necesario.
PRECONDICIONES: El vector debe haber sido inicializado. 
POSTCONDICIONES: Ninguna.*/
status_t ADT_Vector_new_size(ADT_Vector_t *v, size_t new_size, status_t (*destructor)(void ** ))
{
	void ** aux;
	size_t i;
	status_t st;

	if(v == NULL)
		return ERROR_NULL_POINTER;

	if(new_size < v->used_size)
	{	/*Se eliminan los elementos que no entrarán en el nuevo arreglo*/
		for(i = new_size; i < v->used_size; i++)
			if((st = (*destructor)(v->elements + i)) != OK)
				return st;
		v->used_size = new_size;
	}

	/*Se cambia el tamaño de arreglo de punteros*/
	if((aux = (void **)realloc(v->elements, sizeof(void *) * new_size)) == NULL)
	{
		ADT_Vector_delete(&v, destructor);
		return ERROR_MEMORY;
	}
	v->alloc_size = new_size;
	v->elements = aux;

	return OK;
}

/*La siguiente funcion ordena los elementos de un vector de forma ascendente. Utiliza la función compare.
La función utiliza el metodo de selección.
	·v es un puntero al vector a ordenar.
	·compare es la funcion que compara dos elementos del arreglo.
PRECONDICIONES: El vector debe estar creado. compare debe devolver un numero positivo si el primer elemento es
mayor que el segundo. Negativo en caso contrario. Cero si son iguales.
POSTCONDICIONES: ninguna.
*/
status_t ADT_Vector_sort(ADT_Vector_t *v,int (*compare)(void *, void *))
{
	size_t i;
	size_t min_pos;

	if(v == NULL || compare == NULL)
		return ERROR_NULL_POINTER;
	if(v->used_size < 2)
		return OK;

	for(i = 0; i < v->used_size; i++)
	{
		min_pos = ADT_Vector_get_min_key_pos(v, i, v->used_size, compare);
		ADT_Vector_swap_elements(v, i, min_pos);
	}

	return OK;
}

/*La siguiente función intercambia la posición de dos elementos.
	·v es el vector al que se va a realizar el intercambio de elementos.
	·pos_1 es la posicion de uno de los elementos.
	.pos_2 es la posicion del segundo elemento a intercambiar.
PRECONDICIONES: v debe estar incializado correctamente. pos_1 y pos_2 deben ser menores que used_size.
POSTCONDICIONES: Ninguna.*/
void ADT_Vector_swap_elements(ADT_Vector_t *v, size_t pos_1, size_t pos_2)
{
	void * temp;

	temp = v->elements[pos_1];
	v->elements[pos_1] = v->elements[pos_2];
	v->elements[pos_2] = temp;  
}

/*La siguiente función agrega un elemento en el vector en una posicion especifica. Si la posicion
esta ocupada, se lo borra y se agrega el nuevo elemento. Si fuera necesario, se agranda el arreglo. 

	·v es el vector donde se desea agregar el nuevo elemento.
	·pos es la posicion donde se desea agregar el elemento.
	·data es un puntero al elemento que se desea agregar.
	·destructor es un puntero a la funcion que libera de la memoria a un elemento del vector.
PRECONDICIONES: El vector debe estar inicializado. Los elementos del vector deben haber sido generados 
con memoria dinámica, la función destructor libera los elementos.
POSTCONDICIONES: Cambia el tamaño del vector si pos > alloc_size. */
status_t ADT_Vector_set_element_at(ADT_Vector_t *v, size_t pos, void *data, status_t (*destructor)(void ** ))
{
	
	status_t st;

	if(v == NULL /*|| agregar otro si es necesario*/)
		return ERROR_NULL_POINTER;

	if(pos < v->used_size)
	{	/*Se elimina el elemento que esta en la posicion pos y se agrega el nuevo elemento*/
		if((st =(*destructor)(v->elements + pos)) != OK)
			return st;
		v->elements[pos] = data;
	}
	else if(pos < v->alloc_size)
	{
		v->elements[pos] = data;
		(v->used_size)++;
	}
	else
	{
		if((st = ADT_Vector_new_size(v, pos + CHOP_SIZE, destructor)) != OK)
			return st;
		v->elements[pos] = data;
	}

	return OK;
}

	/****************************** GETTERS **************************************/

/*La siguiente función devuelve un puntero a un elemento del vector en la posicion pos.
Si no se encuentra, devuelve NULL.
	·v es el vector de donde se desea extraer el elemento.
	·pos es la posición del elemento que se quiere extraer.
PRECONDICIONES: El vector debe estar inicializado.
POSTCONDICIONES: Ninguna.*/
void * ADT_Vector_get_element_at(ADT_Vector_t *v, size_t pos)
{
	if(v ==NULL)
		return NULL;

	if(pos > v->alloc_size)
		return NULL;

	return v->elements[pos];
}

/*La siguiente funcion busca el elemento con la clave menor entre las posiciones init_pos y final_pos.
El criterio de comparación depende de la función compare.
	·v es el vector de donde se obtendra la posición del elemento mayor.
	·init_pos es la posicion desde donde se empienza a buscar el elemento con la clave más grande.
	·final_pos es la posición del último elemento del vector.
	·compare es un puntero a la función comparadora.
PRECONDICIONES: El vector debe estar creado. init_pos debe ser menor que final pos y a su vez final
pos debe ser menor que used_size.
compare debe devolver un numero positivo si el primer elemento es mayor que el segundo. Negativo en 
caso contrario. Cero si son iguales. 
POSTCONDICIONES: ninguna.*/
size_t ADT_Vector_get_min_key_pos(ADT_Vector_t *v, size_t init_pos,size_t final_pos, int (*compare)(void *, void *))
{
	size_t i;
	size_t min_pos;

	min_pos = init_pos;

	for (i = init_pos ; i < (final_pos -1); i ++)
	{
		if((*compare)(v->elements[min_pos],v->elements[i+1]) > 0)
			min_pos = i + 1;
	}

	return min_pos;
}

/*La siguiente función exporta un ADT_Vector_t a un archivo CSV.
	·vector es el vector que contiene los registros a imprimir.
	·del es el delimitador del CSV.
	·printer es la funcion que imprime los elementos del vector.
*/
status_t ADT_Vector_export_as_CSV(ADT_Vector_t *vector, FILE * fo, char del, status_t (*printer)(const void *,char, FILE *))
{
	size_t i;
	status_t st;

	if(vector == NULL || fo == NULL || printer == NULL)
		return ERROR_NULL_POINTER;

	for (i = 0; i < vector->used_size; i++)
	{
		if((st = (*printer)(vector->elements[i], del, fo) )!= OK)
			return st;

		fputc('\n', fo);
	}
	return OK;
}

/*La siguiente función exporta un ADT_Vector_t a un archivo kml.
	·vector es el vector que contiene los registros a imprimir.
	·del es el delimitador del kml.
	·printer es la funcion que imprime los elementos del vector.
*/
status_t ADT_Vector_export_as_kml(ADT_Vector_t *vector, FILE * fo, char del, status_t (*printer)(const void *,char, FILE *))
{
	size_t i;
	status_t st;

	if(vector == NULL || fo == NULL || printer == NULL)
		return ERROR_NULL_POINTER;

	print_header_tag(XML_HEADER, fo);
	fputc(LF, fo);
	print_header_tag(KML_HEADER, fo);
	fputc(LF, fo);
	print_header_tag(DOCUMENT_TAG, fo);
	fputc(LF, fo);
	print_line(NAME_TAG,NAME_VALUE,fo);
	print_line(DESCRIPTION_TAG,DESCRIPTION_VALUE,fo);
	print_header_tag(STYLE_HEADER_TAG, fo);
	fputc(LF, fo);
	print_header_tag(LINE_STYLE_TAG, fo);
	fputc(LF, fo);
	print_line(COLOR_TAG,COLOR_VALUE,fo);
	print_line(WITDH_TAG,WITDH_VALUE,fo);
	print_footer_tag(LINE_STYLE_TAG, fo);
	fputc(LF, fo);
	print_header_tag(POLY_STYLE_TAG, fo);
	fputc(LF, fo);
	print_line(COLOR_TAG,COLOR_VALUE,fo);
	print_footer_tag(POLY_STYLE_TAG, fo);
	fputc(LF, fo);
	print_footer_tag(STYLE_FOOTER_TAG, fo);
	fputc(LF, fo);
	print_header_tag(PLACEMARK_TAG, fo);
	fputc(LF, fo);
	print_line(NAME_VALUE,NAME_PLACEMARK_VALUE,fo);
	print_line(DESCRIPTION_TAG,DESCRIPTION_PLACEMARK_VALUE,fo);
	print_line(STYLE_URL_TAG,STYLE_URL_VALUE,fo);
	print_header_tag(LINESTRING_TAG, fo);
	fputc(LF, fo);
	print_line(EXTRUDE_TAG,EXTRUDE_VALUE,fo);
	print_line(TESSELLATE_TAG,TESSELLATE_VALUE,fo);
	print_line(ALTITUDE_MODE_TAG,ALTITUDE_MODE_VALUE,fo);
	print_header_tag(COORDINATES_TAG, fo);

	for (i = 0; i < vector->used_size; i++)
	{
		if((st = (*printer)(vector->elements[i], del, fo) )!= OK)
			return st;

		fputc(LF, fo);
	}	
	print_footer_tag(COORDINATES_TAG, fo);
	fputc(LF, fo);
	print_footer_tag(LINESTRING_TAG, fo);
	fputc(LF, fo);
	print_footer_tag(PLACEMARK_TAG, fo);
	fputc(LF, fo);	
	print_footer_tag(DOCUMENT_TAG, fo);
	fputc(LF, fo);
	print_footer_tag(KML_FOOTER, fo);

	return OK;
}
/***************************************************************************************/