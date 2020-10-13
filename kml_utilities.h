/***************************************************************************************/
/*Archivo kml_utilities.h*/
#ifndef KML_UTILITIES__H
#define KML_UTILITIES__H

#include <stdio.h>
#include "types.h"

/*TAGS*/
#define XML_HEADER "?xml version=\"1.0\" encoding=\"UTF-8\"?"
#define KML_HEADER "kml xmkns=\"http://www.opengis.net/kml/2.2\""
#define KML_FOOTER "kml"
#define DOCUMENT_TAG "Document"
#define NAME_TAG "name"
#define DESCRIPTION_TAG "description"
#define STYLE_HEADER_TAG "Style id=\"yellowLineGreenPoly\""
#define LINE_STYLE_TAG "LineStyle"
#define POLY_STYLE_TAG "PolyStyle"
#define STYLE_FOOTER_TAG "Style"
#define COLOR_TAG "color"
#define WITDH_TAG "witdh"
#define PLACEMARK_TAG "Placemark"
#define STYLE_URL_TAG "styleUrl" 
#define LINESTRING_TAG "LineString"
#define EXTRUDE_TAG "extrude"
#define TESSELLATE_TAG "tessellate"
#define ALTITUDE_MODE_TAG "altitudeMode"
#define COORDINATES_TAG "coordinates"
#define FORWARD_SLASH_SYMBOL '/'
#define LESS_THAN_SYMBOL '<'
#define GREATER_THAN_SYMBOL '>'
#define LF '\n'

/*PARAMETROS*/
#define NAME_VALUE "Rutas"
#define NAME_PLACEMARK_VALUE "Relieve absoluto"
#define DESCRIPTION_VALUE "Ejemplos de rutas"
#define DESCRIPTION_PLACEMARK_VALUE "Pared verde transparente con contornos amarillos"
#define STYLE_URL_VALUE "#yellowLineGreenPoly"
#define EXTRUDE_VALUE "1"
#define ALTITUDE_MODE_VALUE "absolute"
#define TESSELLATE_VALUE "1"
#define COLOR_VALUE "ff0000ff"
#define WITDH_VALUE "10"

status_t print_header_tag(char *tag, FILE *fo);
status_t print_footer_tag(char *tag, FILE *fo);
status_t print_line(char* tag,char* parameter,FILE* fo);

#endif
/***************************************************************************************/