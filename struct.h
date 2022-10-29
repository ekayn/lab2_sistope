#ifndef STRUCT_H
#define STRUCT_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
Descripción: struct utilizado para escribir y leer los valores calculados por los hijos
mayor: valor del juego mas caro
nombreMayor[50]: nombre del juego mas caro
menor: valor del juego mas barato
nombreMenor[50]: nombre del juego mas barato
promedio: promedio de los juegos analizados
win: porcentaje de juegos disponibles para windows
mac: porcentaje de juegos disponibles para mac
lin: porcentaje de juegos disponibles para linux
lenGratis: cantidad de juegos que son gratis
gratis: lista de nombres de los juegos que son gratis
*/
typedef struct hijo{
    float mayor;
    char nombreMayor[50];
    float menor;
    char nombreMenor[50];
    float promedio;
    float win;
    float mac;
    float lin;
    int lenGratis;
    char gratis[200][50];
} hijo;

/*
Descripción: struct utilizado para representar la escritura del padre y lectura del hijo
inicio: valor que toma el puntero a la primera fila de texto en el archivo a leer en el hijo
fin: valor que toma el puntero a la ultima fila de texto en el archivo a leer en el hijo
precio: precio mínimo que debe tener un juego
cantidad: cantidad de juegos por año
ciclos: cantidad de años que existen
*/
typedef struct entrada{
    int inicio;
    int fin;
    float precio;
    int cantidad;
    int ciclos;
}entrada;

/*
Descripción: struct utilizado para ingresar los datos por consola
inputFile: nombre del archivo con los juegos
outputFile: nombre del archivo a crear
ano: año desde donde se deben registrar los juegos
precio: precio minimo que deben tener los juegos a analizar
flag: bandera utilizada para imprimir en pantalla
*/
typedef struct arg{
    char inputFile[1000];
    char outputFile[1000];
    int ano;
    float precio;
    int flag;
}arg;

#endif
