#include "arbolesADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "manejoArch.h"

#define MAX_LIN 256 // Cantidad max de caracteres a leer cuando se usa fgets.

#define ARG_QTY 3

#define SEPARADOR ";"

void mensajeError (int codigo) {
    switch (codigo) {
        case MAL_ARGS:
            fprintf(stderr,"Cantidad de Argumentos Invalida, lea README.\n");
            break;
        case ERROR_ABERTURA:
            fprintf(stderr,"Los archivos no pueden ser abiertos.\n");
            break;
        case SIN_MEMORIA:
            fprintf(stderr,"Asginacion de memoria invalida.\n");
            break;
        case ERROR_CREANDO:
            fprintf(stderr,"Los archivos no pueden ser creados.n");
            break;
    }
}

int chequearArgs(int args){
    if (args!=ARG_QTY){
        mensajeError(MAL_ARGS);
        return MAL_ARGS;
    }
    return 0;
}

int abrirArchivos(FILE ** archivoArboles, FILE ** archivoBarrios, const char * argv[]){
    *archivoArboles = fopen(argv[1],"r");
    *archivoBarrios = fopen(argv[2],"r");
    if (archivoBarrios==NULL||archivoArboles==NULL){
        mensajeError(ERROR_ABERTURA);
        return ERROR_ABERTURA;
    }
    return 0;
}

static int createFile(FILE ** f, const char * fileName){
    *f = fopen(fileName,"w");
    if (*f==NULL){
        mensajeError(ERROR_CREANDO);
        return ERROR_CREANDO;
    }
    return 0;
}


int leerBarrios(FILE * archivoBarrios, arbolesADT adt){
    char lineaEntera[MAX_LIN];
    char * leer = NULL;
    char * nombreBarrio = NULL;
    long barrioPob;
    fgets(lineaEntera,MAX_LIN,archivoBarrios);
    while (fgets(lineaEntera,MAX_LIN,archivoBarrios)!=NULL){
        leer = strtok(lineaEntera,SEPARADOR);
        nombreBarrio=leer; 
        leer = strtok(NULL,SEPARADOR);
        barrioPob = atol(leer); 
        int ok = agregaBarrio(adt,nombreBarrio,barrioPob);
        if (!ok){
            mensajeError(SIN_MEMORIA);
            return SIN_MEMORIA;
        }
    }
    fclose(archivoBarrios); 
    return 0;
}

int leerArboles(FILE * archivoArboles, arbolesADT adt, int maxCol, int barrioCol, int calleCol, int arbolNomCol, int diamCol){
 
    char lineaEntera[MAX_LIN];
    char * leer;
    char * barrio;
    char * calle;
    char * arbol;
    double diam;

    fgets(lineaEntera,MAX_LIN,archivoArboles);
    while ( fgets(lineaEntera,MAX_LIN,archivoArboles)!=NULL ){
        leer=strtok(lineaEntera,SEPARADOR);
        for (int i=1;i<=maxCol; i++,leer=strtok(NULL,SEPARADOR)){
           
            if (i==barrioCol){
                barrio=leer;
            }
            if (i==calleCol){
                calle=leer;
            }
            if (i==arbolNomCol){
                arbol=leer;
            }
            if (i==diamCol){
                diam = strtod(leer,NULL); 
            }
        }
        int ok = agregaArbol(adt,barrio,calle,arbol,diam);
        if (!ok){
            mensajeError(SIN_MEMORIA);
            return SIN_MEMORIA;
        }
    }
    fclose(archivoArboles); 
    return 0;
}

 static int query1(arbolesADT adt, int * auxDim){
     int error = 0;
     calleArbolB * vec1 = resolQ1(adt, auxDim);
      if (vec1==NULL){
        mensajeError(SIN_MEMORIA);
        return SIN_MEMORIA;
    }
    FILE * Q1File;
    error = createFile(&Q1File,"query1.csv");
    if (error){
        return error;
    }
    fputs(HEADERS_QUERY1,Q1File);

    for (int i=0;i<*auxDim;i++){
      fprintf(Q1File,"%s;%g\n", vec1[i].nombre, vec1[i].dato);
    }
    fclose(Q1File);
    return 0;

 }

 static int query2(arbolesADT adt, int * auxDim){
     int error = 0;
     calleArbolC * vec1 = resolQ2(adt, auxDim);
      if (vec1==NULL){
        mensajeError(SIN_MEMORIA);
        return SIN_MEMORIA;
    }
    FILE * Q2File;
    error = createFile(&Q2File,"query2.csv");
    if (error){
        return error;
    }
    fputs(HEADERS_QUERY2,Q2File);

    for (int i=0;i<*auxDim;i++){
      fprintf(Q2File,"%s;%s;%g\n", vec1[i].nombre, vec1[i].nombre2, vec1[i].dato);
    }
    fclose(Q2File);
    return 0;

 }

 static int query3(arbolesADT adt, TQ3 ** auxVec, int * auxDim){

    int error=0;
    TQ3 * vec3 = resolQ3(adt,auxDim);

    if (vec3==NULL){
        mensajeError(SIN_MEMORIA);
        return SIN_MEMORIA;
    }

    FILE * Q3File;
    error = createFile(&Q3File,"query3.csv");
    if (error){
        return error;
    }

    fputs(HEADERS_QUERY3,Q3File);

    for (int i=0;i<*auxDim;i++){
      char * nombreCalle="Sin arboles";
      if (vec3[i].cantArb>0)
        nombreCalle=vec3[i].popCalle.nombre;
      fprintf(Q3File,"%s;%s;%d\n", vec3[i].barrio, nombreCalle, vec3[i].popCalle.dato);
    }

    fclose(Q3File);
    return 0;
}

static int query4(arbolesADT adt){

    int dim;
    TQ4 * vec4 = resolQ4(adt,&dim);
    if (vec4==NULL){
        mensajeError(SIN_MEMORIA);
        return SIN_MEMORIA;
    }

    FILE * Q4File;
    int error = createFile(&Q4File,"query4.csv");
    if (error){
        return error;
    }
    fputs(HEADERS_QUERY4,Q4File);

    for (int i=0;i<dim;i++){
        fprintf(Q4File,"%s;%.2f;%.2f\n", vec4[i].arbol, vec4[i].dMin, vec4[i].dMax);
    }
    free(vec4);
    fclose(Q4File);
    return 0;

}

int resolverQuerys (arbolesADT adt) {
  int error;
  error = query4(adt);
  if (error)
      return error;

  TQ3 * auxVec;
  int auxDim;

    error = query3(adt,&auxVec,&auxDim);
  if (error)
      return error;

    error = query1(adt, &auxDim);
 if (error)
    return error;

    error = query2(adt, &auxDim);
 if (error)
    return error;

  printf("Los archivos fueron creados con exito.!\n");
  return 0;
}
