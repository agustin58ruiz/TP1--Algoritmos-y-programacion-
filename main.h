#ifndef MAIN__H
#define MAIN__H

#include <stdio.h>
#include "types.h"
#include "errors.h"

#define MAX_CMD_ARGS 6
#define CMD_ARG_FORMAT_FLAG_POS 1
#define CMD_ARG_FORMAT_FLAG_TOKEN "-fmt"
#define CMD_ARG_FORMAT_CSV_TOKEN "csv"
#define CMD_ARG_FORMAT_KML_TOKEN "kml"
#define CMD_ARG_OUT_FLAG_POS 3
#define CMD_ARG_OUT_FLAG_TOKEN "-out"
#define CMD_ARG_GPS_FILE_POS 5 


status_t validate_arguments(int argc, char **argv, format_t *fmt);

#endif