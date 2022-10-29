#include "hijo.h"

/*
Entradas: 
	buffer: string con todos los datos de un juego
Salidas: precio del juego como entero
Descripción: funcion utilizada para retornar el precio de un juego
*/
float obtenerPrecio(char* buffer){
	int nComas = 0;
    int i=0;
    char numerico[10];
    while(nComas < 3){
        if(buffer[i]==','){
            nComas++;
        }
        i++;
    }
    int j=0;
    while(buffer[i] != ','){
    	numerico[j] = buffer[i];
    	i++;
    	j++;
    }
    numerico[j] = '\0';
    return atof(numerico);
}

/*
Entradas: 
	buffer: string con todos los datos de un juego
Salidas: nombre del juego como entero
Descripción: funcion utilizada para retornar el nombre de un juego
*/
char* obtenerNombre(char* buffer){
	int nComas = 0;
    int i=0;
    char* nombre = (char*)malloc(sizeof(char)*50) ;
    while(nComas < 1){
        if(buffer[i]==','){
            nComas++;
        }
        i++;
    }
    int j=0;
    while(buffer[i] != ','){
    	nombre[j] = buffer[i];
    	i++;
    	j++;
    }
    nombre[j] = '\0';
    return nombre;
}

/*
Entradas: 
	buffer: string con todos los datos de un juego
Salidas: entero que señala si es gratis(1) o no(0)
Descripción: funcion utilizada para verificar si un juego es gratis
*/
int obtenerGratis(char* buffer){
	int nComas = 0;
    int i=0;
    char nombre[50];
    while(nComas < 6){
        if(buffer[i]==','){
            nComas++;
        }
        i++;
    }    
    int j=0;
    while(buffer[i] != ','){
    	nombre[j] = buffer[i];
    	i++;
    	j++;
    }
    nombre[j] = '\0';
    if(strcmp(nombre, "False") == 0){
    	return 0;
    }
    return 1;
}

/*
Entradas: 
	buffer: string con todos los datos de un juego
Salidas: entero que señala si es está disponible para window(1) o no(0)
Descripción: funcion utilizada para verificar si un juego está disponible para window
*/
float obtenerWin(char* buffer){
	int nComas = 0;
    int i=0;
    char nombre[50];
    while(nComas < 7){
        if(buffer[i]==','){
            nComas++;
        }
        i++;
    }
    int j=0;
    while(buffer[i] != ','){
    	nombre[j] = buffer[i];
    	i++;
    	j++;
    }
    nombre[j] = '\0';
    if(strcmp(nombre, "Yes") == 0){
    	return 1;
    }
    return 0;
}

/*
Entradas: 
	buffer: string con todos los datos de un juego
Salidas: entero que señala si es está disponible para mac(1) o no(0)
Descripción: funcion utilizada para verificar si un juego está disponible para mac
*/
float obtenerMac(char* buffer){
	int nComas = 0;
    int i=0;
    char nombre[50];
    while(nComas < 8){
        if(buffer[i]==','){
            nComas++;
        }
        i++;
    }
    int j=0;
    while(buffer[i] != ','){
    	nombre[j] = buffer[i];
    	i++;
    	j++;
    }
    nombre[j] = '\0';
    if(strcmp(nombre, "Yes") == 0){
    	return 1;
    }
    return 0;
}

/*
Entradas: 
	buffer: string con todos los datos de un juego
Salidas: entero que señala si es está disponible para linux(1) o no(0)
Descripción: funcion utilizada para verificar si un juego está disponible para linux
*/
float obtenerLin(char* buffer){
	int nComas = 0;
    int i=0;
    char nombre[50];
    while(nComas < 9){
        if(buffer[i]==','){
            nComas++;
        }
        i++;
    }
    int j=0;
    while(buffer[i] != '\n'){
    	nombre[j] = buffer[i];
    	i++;
    	j++;
    }
    nombre[j] = '\0';
    if(strcmp(nombre, "Yes") == 0){
    	return 1;
    }
    return 0;
}

/*
Entradas: 
	argc: cantidad de elementos que se ingresan
	argv: lista con los elementos que se ingresan
Salidas: retorna al padre todos los datos buscados por año en un struct
Descripción: función hija utilizada para calcular todos los datos buscados por año
*/
int main(int argc, char **argv){
	FILE* file = fopen("intermedio.txt", "r");
	if(file == NULL){
		printf("No se pudo abrir el archivo\n");
		exit(1);
	}
	for(int o=0; o<atoi(argv[1]); o++){
		fseek(file, 0, SEEK_SET);
		entrada ent;
		read(STDIN_FILENO, &ent, sizeof(entrada));
		
		hijo retornar;
		retornar.mayor = 0;
		retornar.menor = 1000;
		retornar.promedio = 0;
		retornar.lenGratis = 0;
		retornar.win = 0;
		retornar.mac = 0;
		retornar.lin = 0;	
		fseek(file, ent.inicio, SEEK_SET);
		
		float precio;
		char* nombre;
		int gratis;
		int contador = 0;			
		char buffer[200];
		
		for(int i=0;i<ent.cantidad;i++){	
			fgets(buffer, 200, file);
			
			int aux = ftell(file);
			precio = obtenerPrecio(buffer);
			fseek(file, aux, SEEK_SET);
			
			if(precio >= ent.precio){

			   	nombre = obtenerNombre(buffer);
				fseek(file, aux, SEEK_SET);
				
				gratis = obtenerGratis(buffer);
				fseek(file, aux, SEEK_SET);	
				
				retornar.win = retornar.win + obtenerWin(buffer);
				fseek(file, aux, SEEK_SET);
				
				retornar.mac = retornar.mac + obtenerMac(buffer);
				fseek(file, aux, SEEK_SET);
				
				retornar.lin = retornar.lin + obtenerLin(buffer);
				fseek(file, aux, SEEK_SET);
				

				retornar.promedio = retornar.promedio + precio;
						
				if(precio > retornar.mayor){
					retornar.mayor = precio;
					strcpy(retornar.nombreMayor, nombre);
					fseek(file, aux, SEEK_SET);
				}
				if(precio < retornar.menor){
					retornar.menor = precio;
					strcpy(retornar.nombreMenor, nombre);
					fseek(file, aux, SEEK_SET);
				}
				if(gratis){
					strcpy(retornar.gratis[retornar.lenGratis], nombre);
					fseek(file, aux, SEEK_SET);
					
					retornar.lenGratis = retornar.lenGratis + 1;
				}
				contador = contador+1;
			}
		}
		retornar.promedio = retornar.promedio/contador;
		retornar.win = retornar.win/contador;
		retornar.mac = retornar.mac/contador;
		retornar.lin = retornar.lin/contador;		
		
		write(STDOUT_FILENO, &retornar, sizeof(hijo));
	}
	fclose(file);
	return 0;
}

