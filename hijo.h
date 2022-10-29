#ifndef HIJO_H
#define HIJO_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "struct.h"

/*
Entradas: 
	buffer: string con todos los datos de un juego
Salidas: precio del juego como entero
Descripción: funcion utilizada para retornar el precio de un juego
*/
float obtenerPrecio(char* buffer);

/*
Entradas: 
	buffer: string con todos los datos de un juego
Salidas: nombre del juego como entero
Descripción: funcion utilizada para retornar el nombre de un juego
*/
char* obtenerNombre(char* buffer);

/*
Entradas: 
	buffer: string con todos los datos de un juego
Salidas: entero que señala si es gratis(1) o no(0)
Descripción: funcion utilizada para verificar si un juego es gratis
*/
int obtenerGratis(char* buffer);

/*
Entradas: 
	buffer: string con todos los datos de un juego
Salidas: entero que señala si es está disponible para window(1) o no(0)
Descripción: funcion utilizada para verificar si un juego está disponible para window
*/
float obtenerWin(char* buffer);

/*
Entradas: 
	buffer: string con todos los datos de un juego
Salidas: entero que señala si es está disponible para mac(1) o no(0)
Descripción: funcion utilizada para verificar si un juego está disponible para mac
*/
float obtenerMac(char* buffer);

/*
Entradas: 
	buffer: string con todos los datos de un juego
Salidas: entero que señala si es está disponible para linux(1) o no(0)
Descripción: funcion utilizada para verificar si un juego está disponible para linux
*/
float obtenerLin(char* buffer);

#endif
