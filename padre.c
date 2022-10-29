#include "padre.h"

/*
Entradas: 
	argc: cantidad de elementos ingresados por consola
	argv: lista de strings con los elementos ingresados por consola
Salidas: struct con los datos ingresados por consola
Descripción: Funcion creada para registrar los datos ingresados por consola en un struct, funciona a traves de getopt
*/
struct arg *registrarArgumentos(int argc, char **argv){
    int currentFlag = 0;
    arg *argumentos = (arg*)calloc(1, sizeof(arg));
    while((currentFlag = getopt(argc, argv, "i:o:d:p:b")) != -1){
        switch(currentFlag){
        case 'i':
            strcpy(argumentos->inputFile, optarg);
            break;
        case 'o':
            strcpy(argumentos->outputFile, optarg);
            break;
        case 'd':
            argumentos->ano = atoi(optarg);
            break;
        case 'p':
            argumentos->precio = atof(optarg);
            break;
        case 'b':
            argumentos->flag = 1;
            break;
        default:
            return NULL;
        }
    }
    return argumentos;
}

/*
Entradas: 
	buffer: string con todos los datos de un juego
Salidas: año del juego como entero
Descripción: funcion utilizada para retornar el año de un juego
*/
int obtenerAno(char* buffer){
    int nComas = 0;
    int i=0;
    char numerico[5];
    while(nComas < 5){
        if(buffer[i]==','){
            nComas++;
        }
        i++;
    }
    numerico[0] = buffer[i];
    numerico[1] = buffer[i+1];
    numerico[2] = buffer[i+2];
    numerico[3] = buffer[i+3];
    numerico[4] = '\0';
    return atoi(numerico);
}

/*
Entradas:
	anos: lista con los años encontrados en el archivo de juegos
	len: cantidad de años que hay en la variable "anos"
Salidas: lista de enteros con los años ordenados de forma ascendente
Descripción: funcion utilizada para ordenar una lista de enteros de forma ascendente
*/
int* ordenarAnos(int* anos, int len){
    int* nuevaLista = (int*)malloc(sizeof(int)*len);
    for(int i=0; i<len; i++){
        nuevaLista[i] = anos[i];
    }
    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            if(nuevaLista[i]<nuevaLista[j]){
                int aux = nuevaLista[i];
                nuevaLista[i] = nuevaLista[j];
                nuevaLista[j] = aux;
            }
        }
    }
    free(anos);
    return nuevaLista;
}

/*
Entradas: 
	ano: entero que representa un año
	anos: lista de enteros que contiene los años encontrados
	len: cantidad de elementos que hay en la variable "anos"
Salidas: lista con la variable "ano" ingresada en la lista "anos
Descripción: funcion utilizada para ingresar un entero a una lista de enteros
*/
int* ingresarAno(int ano, int* anos, int *len){
    for (int i=0; i<*len; i++){
        if (anos[i] == ano){
            return anos;
        }
    }
    int* nuevoAnos = (int*)malloc(sizeof(int)*(*len+1));
    for (int i=0; i<*len; i++){
        nuevoAnos[i] = anos[i];
    }
    nuevoAnos[*len] = ano;
    free(anos);
    *len = *len +1;
    return nuevoAnos;
}

/*
Entradas: 
	nameFile: nombre del archivo a abrir
	len: cantidad de elementos encontrados
Salidas: lista de enteros (años) encontrados en el archivo nameFile
Descripción: función utilizada para buscar los años que hay en el archivo de juegos
*/
int* buscarAnos(char* nameFile, int *len){
    FILE* file = fopen(nameFile, "r");
    if(file == NULL){
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }
    int* anos = (int*)malloc(sizeof(int)**len);
    char buffer[200];
    while(fgets(buffer, 200, file) != NULL){
        int ano = obtenerAno(buffer);
        anos = ingresarAno(ano, anos, &*len);
    }
    fclose(file);
    anos = ordenarAnos(anos, *len);
    return anos;
}

/*
Entradas: 
	punteros: lista de punteros(enteros) a fila de texto
	len: cantidad de elementos que hay en la lista "punteros"
	puntero: entero que apunta a una linea de texto
Salidas: lista de enteros con la variable "puntero" agregado
Descripción: funcion utilizada para ingresar la variable "puntero" a la lista "punteros"
*/
int* agregarPuntero(int* punteros, int len, int puntero){
    int* nuevaLista = (int*)malloc(sizeof(int)*(len+1));
    for(int i=0; i<len; i++){
        nuevaLista[i] = punteros[i];
    }
    nuevaLista[len] = puntero;
    free(punteros);
    return nuevaLista;
}

/*
Entradas: 
	nameFile: nombre del archivo a buscar
	Salidas: lista de punteros(enteros) encontrados en el archivo
Descripción: funcion utilizada para buscar todos los punteros que hay en el archivo nameFile
*/
int* buscarPunteros(char* nameFile, int *len){
    FILE* file = fopen(nameFile, "r");
    if(file == NULL){
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }
    int* retornar = (int*)malloc(sizeof(int)*1);
    retornar[0] = 0;
    *len = *len+1;
    char buffer[200];
    int i=0;
    while(fgets(buffer, 200, file) != NULL){
		retornar = agregarPuntero(retornar, *len, ftell(file));
		*len = *len+1;
        i++;
    }
    fclose(file);
    *len = *len -1;
    return retornar;
}

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
void crarArchivo(int* punteros, int lenIni, int* anos, int lenAnos, char* Filename){
	int* newPunteros = (int*)malloc(sizeof(int)*lenIni);
	
    FILE* file = fopen(Filename, "r");
    if(file == NULL){
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }

    FILE* file2 = fopen("intermedio.txt", "w");
    if(file2 == NULL){
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }
    char buffer[200];
    for (int i=0; i<lenAnos; i++){
        for (int j=0; j<lenIni; j++){
            fseek(file, punteros[j], SEEK_SET);
            if (fgets(buffer, 200, file) != NULL){
				if (obtenerAno(buffer) == anos[i]){
					fprintf(file2, "%s", buffer);
				}
            }
        }
    }  
    
    fclose(file);
    fclose(file2);
}

/*
Entradas: 
	anos: lista con los años encontrados en el archivo de juegos 
	lenAnos: cantidad de elementos que hay en la lista "anos"
Salidas: lista de enteros ordenados de forma ascendente
Descripción: función utilizada para ordenar una lista de enteros de forma ascendente
*/
int* buscarLenAnos(int* anos, int lenAnos){
    FILE* file = fopen("intermedio.txt", "r");
    if(file == NULL){
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }
    int* retornar = (int*)malloc(sizeof(int)*(lenAnos));
    for(int i=0; i<lenAnos; i++){
        retornar[i] = 0;
    }
    char buffer[200];
    for (int i=0; i<lenAnos; i++){
        while(fgets(buffer, 200, file)!=NULL){
            if (obtenerAno(buffer)==anos[i]){                
                retornar[i] = retornar[i]+1;
            }
        }
        fseek(file, 0, SEEK_SET);
    }
    fclose(file);
    return retornar;
}

/*
Entradas: 
	nameFile: nombre del archivo de salida donde se escribirá
	h: resultados calculados por un hijo
	ano: año en donde se hicieron los calculos en el hijo
Salidas: NONE
Descripción: función utilizada para escribir los datos calculados por un hijo en el archivo de salida 
*/
void escribir(char* nameFile, hijo h, int ano){
	FILE* file = fopen(nameFile, "a");
	if(file == NULL){
		printf("No se pudo abrir el archivo\n");
		exit(1);
	}
	fprintf(file, "Año: %d\n", ano);
	fprintf(file, "Juego mas caro: %s %.2f\n", h.nombreMayor, h.mayor);
	fprintf(file, "Juego mas barato: %s %.2f\n", h.nombreMenor, h.menor);
	fprintf(file, "Promedio de precios: %.2f\n", h.promedio);
	fprintf(file, "Windows: %.2f Mac: %.2f Linux: %.2f\n", h.win*100, h.mac*100, h.lin*100);
	
	fprintf(file, "Juegos gratis:\n");
	for(int i=0; i<h.lenGratis;i++){
		fprintf(file, "%s\n", h.gratis[i]);
	}
	fprintf(file, "\n");
	fclose(file);
}

/*
Entradas: 
	nameFile: nombre del archivo de salida donde se escribirá
	h: resultados calculados por un hijo
	ano: año en donde se hicieron los calculos en el hijo
Salidas: NONE
Descripción: función utilizada para escribir los datos calculados por un hijo en el archivo de salida e imprime
	los resultados en pantalla 
*/
void escribirEimprimir(char* nameFile, hijo h, int ano){
	FILE* file = fopen(nameFile, "a");
	if(file == NULL){
		printf("No se pudo abrir el archivo\n");
		exit(1);
	}
	fprintf(file, "Año: %d\n", ano);
	fprintf(file, "Juego mas caro: %s %.2f\n", h.nombreMayor, h.mayor);
	fprintf(file, "Juego mas barato: %s %.2f\n", h.nombreMenor, h.menor);
	fprintf(file, "Promedio de precios: %.2f\n", h.promedio);
	fprintf(file, "Windows: %.2f Mac: %.2f Linux: %.2f\n", h.win*100, h.mac*100, h.lin*100);
	
	fprintf(file, "Juegos gratis:\n");
	for(int i=0; i<h.lenGratis;i++){
		fprintf(file, "%s\n", h.gratis[i]);
	}
	fprintf(file, "\n");
	
	printf("Año: %d\n", ano);
	printf("Juego mas caro: %s %.2f\n", h.nombreMayor, h.mayor);
	printf("Juego mas barato: %s %.2f\n", h.nombreMenor, h.menor);
	printf("Promedio de precios: %.2f\n", h.promedio);
	printf("Windows: %.2f Mac: %.2f Linux: %.2f\n", h.win*100, h.mac*100, h.lin*100);
	
	printf("Juegos gratis:\n");
	for(int i=0; i<h.lenGratis;i++){
		printf("%s\n", h.gratis[i]);
	}
	printf("\n");
	
	fclose(file);
}
