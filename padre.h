#ifndef PADRE_H
#define PADRE_H
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
	argc: cantidad de elementos ingresados por consola
	argv: lista de strings con los elementos ingresados por consola
Salidas: struct con los datos ingresados por consola
Descripción: Funcion creada para registrar los datos ingresados por consola en un struct, funciona a traves de getopt
*/
struct arg *registrarArgumentos(int argc, char **argv);

/*
Entradas: 
	buffer: string con todos los datos de un juego
Salidas: año del juego como entero
Descripción: funcion utilizada para retornar el año de un juego
*/
int obtenerAno(char* buffer);

/*
Entradas:
	anos: lista con los años encontrados en el archivo de juegos
	len: cantidad de años que hay en la variable "anos"
Salidas: lista de enteros con los años ordenados de forma ascendente
Descripción: funcion utilizada para ordenar una lista de enteros de forma ascendente
*/
int* ordenarAnos(int* anos, int len);

/*
Entradas: 
	ano: entero que representa un año
	anos: lista de enteros que contiene los años encontrados
	len: cantidad de elementos que hay en la variable "anos"
Salidas: lista con la variable "ano" ingresada en la lista "anos
Descripción: funcion utilizada para ingresar un entero a una lista de enteros
*/
int* ingresarAno(int ano, int* anos, int *len);

/*
Entradas: 
	nameFile: nombre del archivo a abrir
	len: cantidad de elementos encontrados
Salidas: lista de enteros (años) encontrados en el archivo nameFile
Descripción: función utilizada para buscar los años que hay en el archivo de juegos
*/
int* buscarAnos(char* nameFile, int *len);

/*
Entradas: 
	punteros: lista de punteros(enteros) a fila de texto
	len: cantidad de elementos que hay en la lista "punteros"
	puntero: entero que apunta a una linea de texto
Salidas: lista de enteros con la variable "puntero" agregado
Descripción: funcion utilizada para ingresar la variable "puntero" a la lista "punteros"
*/
int* agregarPuntero(int* punteros, int len, int puntero);

/*
Entradas: 
	nameFile: nombre del archivo a buscar
	Salidas: lista de punteros(enteros) encontrados en el archivo
Descripción: funcion utilizada para buscar todos los punteros que hay en el archivo nameFile
*/
int* buscarPunteros(char* nameFile, int *len);

/*
Entradas: 	
	punteros: lista de punteros que señalan filas de texto
	lenIni: cantidad de elementos que hay en la lista "punteros"
	anos: lista con los años que existe en el archivo de juegos
	lenAnos: cantidad de elementos que hay en la lista "anos"
	fileName: nombre del archivo que se utilizará para ordenar
Salidas: NONE
Descripción: función que lee un archivo y crea uno nuevo ordenado por años
*/
void crarArchivo(int* punteros, int lenIni, int* anos, int lenAnos, char* Filename);

/*
Entradas: 
	anos: lista con los años encontrados en el archivo de juegos 
	lenAnos: cantidad de elementos que hay en la lista "anos"
Salidas: lista de enteros ordenados de forma ascendente
Descripción: función utilizada para ordenar una lista de enteros de forma ascendente
*/
int* buscarLenAnos(int* anos, int lenAnos);

/*
Entradas: 
	nameFile: nombre del archivo de salida donde se escribirá
	h: resultados calculados por un hijo
	ano: año en donde se hicieron los calculos en el hijo
Salidas: NONE
Descripción: función utilizada para escribir los datos calculados por un hijo en el archivo de salida 
*/	
void escribir(char* nameFile, hijo h, int ano);

#include "padre.c"
#endif
