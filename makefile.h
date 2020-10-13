#Archivo makefile del programa

CFLAGS= -Wall -ansi -pedantic -O2

CC= gcc

all: gpsviewer

gpsviewer: main.o errors.o gps.o ADT_GPS_point.o ADT_Vector.o utilities.o config.o
	$(CC) $(CFLAGS) main.o errors.o gps.o ADT_GPS_point.o ADT_Vector.o utilities.o config.o  -o gpsviewer

main.o: main.c main.h types.h errors.h config.h
	$(CC) $(CFLAGS) -c main.c -o main.o

errors.o: errors.c errors.h types.h
	$(CC) $(CFLAGS) -c errors.c -o errors.o

gps.o: gps.c gps.h ADT_GPS_point.h ADT_Vector.h utilities.h
	$(CC) $(CFLAGS) -c gps.c -o gps.o

utilities.o: utilities.c utilities.h types.h
	$(CC) $(CFLAGS) -c utilities.c -o utilities.o

ADT_Vector.o: ADT_Vector.c ADT_Vector.h types.h
	$(CC) $(CFLAGS) -c ADT_Vector.c -o ADT_Vector.o

ADT_GPS_point.o: ADT_GPS_point.c ADT_GPS_point.h types.h
	$(CC) $(CFLAGS) -c ADT_GPS_point.c -o ADT_GPS_point.o

main.o: main.c main.h types.h errors.h config.h
	$(CC) $(CFLAGS) -c main.c -o main.o

config.o: config.c config.h types.h
	$(CC) $(CFLAGS) -c config.c -o config.o