#include "padre.h"

#define LECTURA 0
#define ESCRITURA 1

int main(int argc, char **argv){
	//SE REGISTRAN LOS PARAMETROS DE ENTRADA
    arg *opciones = registrarArgumentos(argc, argv);
    
    //SE CREA EL ARCHIVO DE SALIDA
 	FILE* file = fopen(opciones->outputFile, "w");
	if(file == NULL){
	    printf("No se pudo abrir el archivo\n");
	    exit(1);
	}
 	fclose(file);
    
    //SE CALCULAN LOS AÑOS QUE EXISTEN EN EL ARCHIVO
    int lenAnos = 0;
    int* anos = buscarAnos(opciones->inputFile, &lenAnos);
	
	//SE CREAN LOS PIPES Y EL PID A UTILIZAR
	int pipefd[2];
    int pipedf[2];
    pipe(pipedf);
   	pipe(pipefd);  
    int pid;
	
	//SE EJECUTAN TANTOS HIJOS COMO AÑOS QUE HAY
    for (int i = 0; i < lenAnos; ++i){
        pid = fork();
        if (pid < 0) {
            perror("Error al crear subproceso");
            exit(1);

        }
        //SE EJECUTA EL PROCESO HIJO
        if (pid == 0){			
            fflush(stdout);
			close(pipedf[LECTURA]);
            dup2(pipedf[ESCRITURA],STDOUT_FILENO);
            close(pipefd[ESCRITURA]);
            dup2(pipefd[LECTURA],STDIN_FILENO);
            char iteraciones[10];
            sprintf(iteraciones, "%d", lenAnos);
			execl("./hijo", "hijo", iteraciones, (char*)NULL);
            break;
		//SE EJECUTA EL PROCESO PADRE
        }else{
			int lenIni = 0;
			int* punteros = buscarPunteros(opciones->inputFile, &lenIni);						
			crarArchivo(punteros, lenIni, anos, lenAnos, opciones->inputFile);
			int* lenPorAno = buscarLenAnos(anos, lenAnos);
			free(punteros);
			lenIni = 0;
			punteros = buscarPunteros("intermedio.txt", &lenIni);			
			//SE ESCRIBEN LOS DATOS QUE DEBE ANALIZAR EL HIJO
			int inicio=0, final=0;
			for(int o=0; o<=i; o++){		
				for(int j=0; j<o; j++){
					inicio = lenPorAno[j];
				}
				final = final + lenPorAno[o];
			}
			entrada ent;	
			ent.inicio = punteros[inicio];
			ent.fin = punteros[final];
			ent.precio = opciones->precio;
			ent.cantidad = lenPorAno[i];
			ent.ciclos = lenAnos;
			char ciclos[50];
			sprintf(ciclos, "%d", lenAnos);
			write(pipefd[ESCRITURA], &ent, sizeof(entrada));
			
			//SE LEEN LOS RESULTADOS OBTENIDOS POR EL HIJO
			hijo resultados;
			read(pipedf[LECTURA], &resultados, sizeof(hijo));
			if(opciones->flag == 1){
				if(opciones->ano <= anos[i]){
					escribirEimprimir(opciones->outputFile, resultados, anos[i]);
				}
			}else{
				if(opciones->ano <= anos[i]){
					escribir(opciones->outputFile, resultados, anos[i]);
				}
			}
		}
    } 
    return 0;
}

